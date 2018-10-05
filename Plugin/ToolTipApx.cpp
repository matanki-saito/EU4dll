#include "stdinc.h"
#include "byte_pattern.h"

namespace ToolTipApx {
	/*-----------------------------------------------*/

	uintptr_t lineBreak_v125_end;
	uintptr_t lineBreak_v125_end2;
	__declspec(naked) void lineBreak_v125_start()
	{
		__asm {
			cmp byte ptr[esi + edx], ESCAPE_SEQ_1;
			jz i_10;
			cmp byte ptr[esi + edx], ESCAPE_SEQ_2;
			jz i_11;
			cmp byte ptr[esi + edx], ESCAPE_SEQ_3;
			jz i_12;
			cmp byte ptr[esi + edx], ESCAPE_SEQ_4;
			jz i_13;
			jmp i_2;

		i_10:
			movzx eax, word ptr[esi + edx + 1];
			jmp i_1x;

		i_11:
			movzx eax, word ptr[esi + edx + 1];
			sub eax, SHIFT_2;
			jmp i_1x;

		i_12:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_3;
			jmp i_1x;

		i_13:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_4;
			jmp i_1x;

		i_2:
			mov dl, [esi + edx];
			movzx eax, dl;
			jmp i_5;

		i_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;

			ja i_4;
			mov eax, NOT_DEF;

		i_4:
			add esi, 3;
			cmp esi, ebx;
			ja i_6;
			sub esi, 1;

		i_5:
			lea ecx, [edi + 0xB4];

			push lineBreak_v125_end;
			ret;

		i_6:
			mov eax, [esp + 0x98 - 0x8C];

			push lineBreak_v125_end2;
			ret;

		}
	}

	/*-----------------------------------------------*/

	errno_t lineBreak_hook(EU4Version version) {
		std::string desc = "line break";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("8A 14 16 8D 8F");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				// dl,[esi+edx]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), lineBreak_v125_start);
				// mov edi, [ecx+eax*4]
				lineBreak_v125_end = byte_pattern::temp_instance().get_first().address(0xC);
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("66 0F 6E C0 0F 5B C0 0F 2F C8 76 04 F3 0F");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				// movd xmm0,eax
				lineBreak_v125_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;

			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("tooltip plus");

		// â¸çsèàóùÇÃèCê≥
		result |= lineBreak_hook(version);

		return result;
	}


}