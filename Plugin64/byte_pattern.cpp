//Core code from Hooking.Patterns
//https://github.com/ThirteenAG/Hooking.Patterns

#include "pch.h"
#include "byte_pattern.h"

using namespace std;
using namespace std::filesystem;

memory_pointer BytePattern::get(size_t index) const
{
	return this->_results.at(index);
}

memory_pointer BytePattern::get_first() const
{
	return this->get(0);
}

memory_pointer BytePattern::get_second() const
{
	return this->get(1);
}

void BytePattern::StartLog(const wchar_t* module_name)
{
	ShutdownLog();

	wchar_t exe_path[512];
	wchar_t filename[512];

	swprintf(filename, 512, L"pattern_%s.log", module_name);

	GetModuleFileName(NULL, exe_path, 512);

	log_stream().open(path { exe_path }.parent_path() / filename, ios::trunc);
}

void BytePattern::ShutdownLog()
{
	log_stream().close();
}

BytePattern& BytePattern::temp_instance()
{
	static BytePattern instance;

	return instance;
}

BytePattern::BytePattern()
{
	set_module();
}

BytePattern& BytePattern::set_pattern(boost::string_view pattern_literal)
{
	this->transform_pattern(pattern_literal);
	this->bm_preprocess();

	return *this;
}

BytePattern& BytePattern::set_module()
{
	static HMODULE default_module = GetModuleHandleA(NULL);

	return set_module(default_module);
}

BytePattern& BytePattern::set_module(memory_pointer module)
{
	this->get_module_ranges(module);

	return *this;
}

BytePattern& BytePattern::set_range(memory_pointer beg, memory_pointer end)
{
	this->_ranges.resize(1, make_pair(beg.address(), end.address()));

	return *this;
}

BytePattern& BytePattern::search()
{
	this->bm_search();

	debug_output();

	return *this;
}

BytePattern& BytePattern::find_pattern(boost::string_view pattern_literal)
{
	this->set_pattern(pattern_literal).search();

	return *this;
}

std::ofstream& BytePattern::log_stream()
{
	static ofstream instance;

	return instance;
}

pair<uint8_t, uint8_t> BytePattern::parse_sub_pattern(boost::string_view sub)
{
	auto digit_to_value = [](char character) {
		if ('0' <= character && character <= '9') return (character - '0');
		else if ('A' <= character && character <= 'F') return (character - 'A' + 10);
		else if ('a' <= character && character <= 'f') return (character - 'a' + 10);
		throw invalid_argument("Could not parse pattern."); };

	pair<uint8_t, uint8_t> result;

	if (sub.size() == 1)
	{
		if (sub[0] == '?')
		{
			result.first = 0;
			result.second = 0;
		}
		else
		{
			result.first = digit_to_value(sub[0]);
			result.second = 0xFF;
		}
	}
	else if (sub.size() == 2)
	{
		if (sub[0] == '?' && sub[1] == '?')
		{
			result.first = 0;
			result.second = 0;
		}
		else if (sub[0] == '?')
		{
			result.first = digit_to_value(sub[1]);
			result.second = 0xF;
		}
		else if (sub[1] == '?')
		{
			result.first = (digit_to_value(sub[0]) << 4);
			result.second = 0xF0;
		}
		else
		{
			result.first = ((digit_to_value(sub[0]) << 4) | digit_to_value(sub[1]));
			result.second = 0xFF;
		}
	}
	else
	{
		throw invalid_argument("Could not parse pattern.");
	}

	return result;
}

void BytePattern::transform_pattern(boost::string_view literal)
{
	vector<string> sub_patterns;

	this->clear();
	this->_literal.assign(literal.begin(), literal.end());

	if (literal.empty())
	{
		return;
	}

	boost::algorithm::split(sub_patterns, _literal, boost::is_any_of(" "));

	try
	{
		for (auto sub : sub_patterns)
		{
			auto pat = parse_sub_pattern(sub);

			this->_pattern.push_back(pat.first);
			this->_mask.push_back(pat.second);
		}
	}
	catch (const invalid_argument&)
	{
		this->clear();
	}
}

void BytePattern::get_module_ranges(memory_pointer module)
{
	static auto getSection = [](const PIMAGE_NT_HEADERS nt_headers, unsigned section) -> PIMAGE_SECTION_HEADER
	{
		return reinterpret_cast<PIMAGE_SECTION_HEADER>(
			(UCHAR*)nt_headers->OptionalHeader.DataDirectory +
			nt_headers->OptionalHeader.NumberOfRvaAndSizes * sizeof(IMAGE_DATA_DIRECTORY) +
			section * sizeof(IMAGE_SECTION_HEADER));
	};

	_ranges.clear();
	pair<uintptr_t, uintptr_t> range;

	PIMAGE_DOS_HEADER dosHeader = module.pointer<IMAGE_DOS_HEADER>();
	PIMAGE_NT_HEADERS ntHeader = module.pointer<IMAGE_NT_HEADERS>(dosHeader->e_lfanew);

	

	for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; i++)
	{
		auto sec = getSection(ntHeader, i);
		auto secSize = sec->SizeOfRawData != 0 ? sec->SizeOfRawData : sec->Misc.VirtualSize;

		range.first = module.address() + sec->VirtualAddress;

		char buff[512];
		snprintf(buff, sizeof(buff), "%s %d %d", sec->Name, secSize, sec->VirtualAddress);
		std::string buffAsStdStr = buff;

		BytePattern::LoggingInfo(buff);

		if (memcmp((const char*)sec->Name, ".text", 6) == 0 || memcmp((const char*)sec->Name, ".rdata", 7) == 0)
		{
			range.second = range.first + secSize;
			this->_ranges.emplace_back(range);
		}

		if ((i == ntHeader->FileHeader.NumberOfSections - 1) && _ranges.empty())
			this->_ranges.emplace_back(module.address(), module.address() + sec->PointerToRawData + secSize);
	}
}

void BytePattern::clear()
{
	this->_literal.clear();
	this->_pattern.clear();
	this->_mask.clear();
	this->_results.clear();
}

size_t BytePattern::count() const
{
	return this->_results.size();
}

bool BytePattern::has_size(size_t expected, string desc) const
{
	const bool result = (this->_results.size() == expected);

	LoggingInfo(desc + (result ? ":[OK]" : ":[NG]"));

	return result;
}

bool BytePattern::empty() const
{
	return this->_results.empty();
}

void BytePattern::bm_preprocess()
{
	ptrdiff_t index;

	const uint8_t* pbytes = this->_pattern.data();
	const uint8_t* pmask = this->_mask.data();
	size_t pattern_len = this->_pattern.size();

	for (uint32_t bc = 0; bc < 256; ++bc)
	{
		for (index = pattern_len - 1; index >= 0; --index)
		{
			if ((pbytes[index] & pmask[index]) == (bc & pmask[index]))
			{
				break;
			}
		}

		this->_bmbc[bc] = index;
	}
}

void BytePattern::bm_search()
{
	const uint8_t* pbytes = this->_pattern.data();
	const uint8_t* pmask = this->_mask.data();
	size_t pattern_len = this->_pattern.size();

	this->_results.clear();

	if (pattern_len == 0)
	{
		return;
	}

	for (auto& range : this->_ranges)
	{
		uint8_t* range_begin = reinterpret_cast<uint8_t*>(range.first);
		uint8_t* range_end = reinterpret_cast<uint8_t*>(range.second - pattern_len);

		ptrdiff_t index;

		__try
		{
			while (range_begin <= range_end)
			{
				for (index = pattern_len - 1; index >= 0; --index)
				{
					if ((pbytes[index] & pmask[index]) != (range_begin[index] & pmask[index]))
					{
						break;
					}
				}

				if (index == -1)
				{
					this->_results.emplace_back(range_begin);
					range_begin += pattern_len;
				}
				else
				{
					range_begin += max(index - this->_bmbc[range_begin[index]], 1);
				}
			}
		}
		__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
		{

		}
	}
}

void BytePattern::debug_output() const
{
	if (!log_stream().is_open())
		return;

	log_stream() << hex << uppercase;

	log_stream() << "Result(s) of pattern: " << _literal << '\n';

	if (count() > 0)
	{
		for_each_result(
			[this](memory_pointer pointer)
			{
				log_stream() << "0x" << pointer.address() << '\n';
			});
	}
	else
	{
		log_stream() << "None\n";
	}

	log_stream() << "--------------------------------------------------------------------------------------" << endl;
}

void BytePattern::LoggingInfo(const std::string message)
{
	if (!log_stream().is_open())
		return;

	log_stream() << message << "\n";

	log_stream() << "--------------------------------------------------------------------------------------" << '\n' << endl;
}
