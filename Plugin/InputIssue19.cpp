#include "stdinc.h"
#include "byte_pattern.h"

namespace InputIssue19 {

	uintptr_t sub_135FBC0;
	uintptr_t issue_19_keydown_end;
	__declspec(naked) void issue_19_keydown_start() {
		__asm {
			cmp ebx, 229;
			jz issue_19_keydown_x; // skip

			push esi;
			push 1;
			call sub_135FBC0;
			add esp, 8;

		issue_19_keydown_x:
			push issue_19_keydown_end;
			ret;
		}
	}

	uintptr_t issue_19_keypress_end;
	__declspec(naked) void issue_19_keypress_start() {
		__asm {
			cmp ebx, 229;
			jz issue_19_keypress_x; // skip

			push esi;
			push 1;
			call sub_135FBC0;
			add esp, 8;

		issue_19_keypress_x:
			push issue_19_keypress_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("input issue19 fix");

		// 1.25.1.0, 1.26.0.0, 1.27.0.0
		byte_pattern::temp_instance().find_pattern("83 C4 08 33 C0 E9 82 F8 FF FF");
		if (byte_pattern::temp_instance().has_size(1,"")) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xE), issue_19_keydown_start);
			issue_19_keydown_end = byte_pattern::temp_instance().get_first().address(0xE + 0xB);
		}
		// 1.25.1.0, 1.26.0.0, 1.27.0.0
		byte_pattern::temp_instance().find_pattern("55 8B EC 83 EC 40 56 8B 75 0C");
		if (byte_pattern::temp_instance().has_size(1,"")) {
			sub_135FBC0 = byte_pattern::temp_instance().get_first().address(0x0);
		}
		// 1.25.1.0, 1.26.0.0, 1.27.0.0
		byte_pattern::temp_instance().find_pattern("83 FE 46 75 11 80 78 46 00 75");
		if (byte_pattern::temp_instance().has_size(1,"")) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xB), issue_19_keypress_start);
			issue_19_keypress_end = byte_pattern::temp_instance().get_first().address(0xB + 0xB);
		}

		return result;
	}
	


}