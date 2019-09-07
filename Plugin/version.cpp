#include "stdinc.h"
#include "byte_pattern.h"

extern "C" {
	void injectSampleFunc1();
	void injectSampleFunc2();
	uintptr_t injectSampleFunc1ReturnAddress;
	uintptr_t textAddress = (uintptr_t)L"ゲソ娘";
	uintptr_t textAddress2 = (uintptr_t)L"ねこ娘";
}

namespace Misc {

	typedef struct {
		TCHAR text[4];
	} LABEL;

	// Encapsulates the call to static_func
	struct Test
	{
		void operator()(injector::reg_pack& regs)
		{
			OutputDebugString(L"test");
		}
	};

	EU4Version getVersion(){

		// Button 1
		// WriteMemory
		byte_pattern::temp_instance().find_pattern("DC 30 BF 30 F3 30 11 FF");
		if (byte_pattern::temp_instance().count() > 0) {
			// 文字列がある
			uintptr_t address = byte_pattern::temp_instance().get_first().address();
			LABEL label = { L"イカ娘" };
			injector::WriteMemory<LABEL>(address, label,true);
		}

		// Button 2
		// MakeJMP
		byte_pattern::temp_instance().find_pattern("48 81 C1 60 02 00 00 48 8D 15 E2 24 00 00");
		if (byte_pattern::temp_instance().count() > 0) {
			// add rcx,260h
			uintptr_t address = byte_pattern::temp_instance().get_first().address();

			injector::MakeInline<Test>(address, address+14);
		}

		// Button 3
		// MakeJMP
		byte_pattern::temp_instance().find_pattern("48 81 C1 60 02 00 00 48 8D 15 D2 24 00 00");
		if (byte_pattern::temp_instance().count() > 0) {
			// add rcx,260h
			uintptr_t address = byte_pattern::temp_instance().get_first().address();

			injector::MakeCALL (address, injectSampleFunc2, true);
		}

		return UNKNOWN;
	}

	std::string versionString(EU4Version version) {
		switch (version) {
		case v1_25_X:
			return "v1_25_X";
		case v1_26_X:
			return "v1_26_X";
		case v1_27_X:
			return "v1_27_X";
		case v1_28_X:
			return "v1_28_X";
		case v1_28_3:
			return "v1_28_3";
		default:
			return "UNKNOWN";
		}
	}
}