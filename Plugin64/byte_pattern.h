//Core code from Hooking.Patterns
//https://github.com/ThirteenAG/Hooking.Patterns

#pragma once

class memory_pointer
{
	union
	{
		void* Pointer;
		std::uintptr_t Address;
	};

public:
	memory_pointer()
		:Pointer{}
	{

	}

	memory_pointer(void* p)
		: Pointer(p)
	{
	}

	memory_pointer(std::uintptr_t i)
		: Address(i)
	{
	}

	std::uintptr_t address(std::ptrdiff_t offset = 0) const
	{
		return (this->Address + offset);
	}

	template<typename T = void>
	T * pointer(std::ptrdiff_t offset = 0) const
	{
		return reinterpret_cast<T*>(this->address(offset));
	}

	operator std::uintptr_t() const
	{
		return this->address();
	}
};

class BytePattern
{
	std::vector<std::pair<std::uintptr_t, std::uintptr_t>> _ranges;
	std::vector<std::uint8_t> _pattern;
	std::vector<std::uint8_t> _mask;
	std::vector<memory_pointer> _results;
	std::string _literal;

	std::ptrdiff_t _bmbc[256];

	static std::ofstream& log_stream();

	std::pair<uint8_t, uint8_t> parse_sub_pattern(boost::string_view sub);
	void transform_pattern(boost::string_view literal);
	void get_module_ranges(memory_pointer module);

	void bm_preprocess();
	void bm_search();

	void debug_output() const;


public:
	void debug_output2(const std::string message) const;
	static void start_log(const wchar_t* module_name);
	static void shutdown_log();

	static BytePattern& temp_instance();

	BytePattern();

	BytePattern& set_pattern(boost::string_view pattern_literal);

	BytePattern& set_module();
	BytePattern& set_module(memory_pointer module);
	BytePattern& set_range(memory_pointer beg, memory_pointer end);
	BytePattern& search();

	BytePattern& find_pattern(boost::string_view pattern_literal);

	memory_pointer get(std::size_t index) const;
	memory_pointer get_first() const;
	memory_pointer get_second() const;

	std::size_t count() const;
	bool has_size(std::size_t expected, std::string version) const;
	bool empty() const;
	void clear();

	template <typename Fn>
	void for_each_result(Fn Pr) const
	{
		for (auto& result : this->_results)
		{
			Pr(result);
		}
	}
};