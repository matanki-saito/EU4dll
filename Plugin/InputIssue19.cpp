#include "stdinc.h"
#include "byte_pattern.h"

namespace InputIssue19 {

	/*-----------------------------------------------*/

	uintptr_t sub_135FBC0_v125;
	errno_t func_hook(EU4Version version) {
		std::string desc = "func hook";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			// 1.25.1.0, 1.26.0.0, 1.27.0.0
			byte_pattern::temp_instance().find_pattern("55 8B EC 83 EC 40 56 8B 75 0C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				sub_135FBC0_v125 = byte_pattern::temp_instance().get_first().address(0x0);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_19_keydown_v125_end;
	__declspec(naked) void issue_19_keydown_v125_start() {
		__asm {
			cmp ebx, 229;
			jz issue_19_keydown_x; // skip

			push esi;
			push 1;
			call sub_135FBC0_v125;
			add esp, 8;

		issue_19_keydown_x:
			push issue_19_keydown_v125_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t keydown_hook(EU4Version version) {
		std::string desc = "keydown";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			// 1.25.1.0, 1.26.0.0, 1.27.0.0
			byte_pattern::temp_instance().find_pattern("83 C4 08 33 C0 E9 82 F8 FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xE), issue_19_keydown_v125_start);
				issue_19_keydown_v125_end = byte_pattern::temp_instance().get_first().address(0xE + 0xB);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_19_keypress_v125_end;
	__declspec(naked) void issue_19_keypress_v125_start() {
		__asm {
			cmp ebx, 229;
			jz issue_19_keypress_x; // skip

			push esi;
			push 1;
			call sub_135FBC0_v125;
			add esp, 8;

		issue_19_keypress_x:
			push issue_19_keypress_v125_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t keypress_hook(EU4Version version) {
		std::string desc = "keypress";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			// 1.25.1.0, 1.26.0.0, 1.27.0.0
			byte_pattern::temp_instance().find_pattern("83 FE 46 75 11 80 78 46 00 75");
			if (byte_pattern::temp_instance().has_size(1, "")) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xB), issue_19_keypress_v125_start);
				issue_19_keypress_v125_end = byte_pattern::temp_instance().get_first().address(0xB + 0xB);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("input issue19 fix");

		result |= func_hook(version);
		result |= keydown_hook(version);
		result |= keypress_hook(version);

		return result;
	}
}