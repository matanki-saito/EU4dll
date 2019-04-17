#include "stdinc.h"
#include "byte_pattern.h"

namespace FileSave {

	/*-----------------------------------------------*/

	uintptr_t loadgame_showTitle_end_v1283;
	__declspec(naked) void loadgame_showTitle_start_v1283() {
		__asm {
			// ここから処理

			lea eax, [ebp - 0x2C];
			push eax;
			call utf8ToEscapedStr;
			add esp, 4;

			// もともとあったもの
			mov edx, [esi + 0x6C];
			lea ecx, [esi + 0x6C];
			lea eax, [ebp - 0x2C];
			push eax;

			push loadgame_showTitle_end_v1283;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t loadgame_showTitle_hook(RunOptions* options) {
		std::string desc = "show title";

		switch (options->version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			return NOERROR;
		case v1_28_3:
			// push 1
			byte_pattern::temp_instance().find_pattern("8B 56 6C 8D 4E 6C 8D 45 D4 50 FF 52 40");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// edx, [esi+6Ch]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), loadgame_showTitle_start_v1283);
				// call dword ptr[edx+40h]
				loadgame_showTitle_end_v1283 = byte_pattern::temp_instance().get_first().address(0xA);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions* options) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("show file name");

		/* タイトルを表示できるようにする */
		result |= loadgame_showTitle_hook(options);

		return result;
	}
}