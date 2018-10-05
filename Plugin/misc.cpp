#include "stdinc.h"
#include "byte_pattern.h"

namespace Misc {
	/*-----------------------------------------------*/

	uintptr_t func1_v125_end;
	uintptr_t func1_v125_end2;
	__declspec(naked) void func1_v125_start()
	{
		__asm {
			movzx eax, byte ptr[edi + esi];
			cmp eax, ESCAPE_SEQ_1;
			jz p_4;
			cmp eax, ESCAPE_SEQ_2;
			jz p_4;
			cmp eax, ESCAPE_SEQ_3;
			jz p_4;
			cmp eax, ESCAPE_SEQ_4;
			jz p_4;

			push eax;

			push func1_v125_end2;
			ret;

		p_4:
			add esi, 3;

			push func1_v125_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t capitalizeCancel_hook(EU4Version version) {
		std::string desc = "capitalize cancel";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("53 57 8B F9 83 7F 14 10 8B 5F 10");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				// movsx eax, byte ptr [edi+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get(1).address(0x24), func1_v125_start);
				// call XXX
				func1_v125_end2 = byte_pattern::temp_instance().get(1).address(0x29);
				// cmp byte ptr [edi + esi], 0
				func1_v125_end = byte_pattern::temp_instance().get(1).address(0x35);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func2_v125_end;
	__declspec(naked) void func2_v125_start()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz u_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz u_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz u_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz u_13;
			movzx eax, byte ptr[eax + esi];
			jmp u_3;

		u_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp u_1x;

		u_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp u_1x;

		u_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp u_1x;

		u_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		u_1x:
			movzx eax, ax;
			add esi, 2;
			cmp eax, NO_FONT;
			ja u_3;
			mov eax, NOT_DEF;

		u_3:
			mov edx, [ebp + 0x14];

			push func2_v125_end;
			ret;
		}
	}

	uintptr_t func2_v126_end;
	__declspec(naked) void func2_v126_start()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz u_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz u_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz u_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz u_13;
			movzx eax, byte ptr[eax + esi];
			jmp u_3;

		u_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp u_1x;

		u_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp u_1x;

		u_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp u_1x;

		u_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		u_1x:
			movzx eax, ax;
			add esi, 2;
			cmp eax, NO_FONT;
			ja u_3;
			mov eax, NOT_DEF;

		u_3:

			mov ecx, [edx + eax * 4];
			test ecx, ecx;

			push func2_v126_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t unknown_hook(EU4Version version) {
		byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 0C 82 85");
		if (byte_pattern::temp_instance().has_size(1, "v1.26.X")) {
			// movzx eax, byte ptr [eax+esi]
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func2_v126_start);
			// jz XXX
			func2_v126_end = byte_pattern::temp_instance().get_first().address(0x9);
		}
		else {
			byte_pattern::temp_instance().find_pattern("8A 04 30 8B 55 14 0F B6");
			if (byte_pattern::temp_instance().has_size(1, "v1.25.X")) {
				// TODO
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func2_v125_start);
				// TODO
				func2_v125_end = byte_pattern::temp_instance().get_first().address(0x9);
			}
			else {
				return 1;
			}
		}

		return 0;
	}

	/*-----------------------------------------------*/

	errno_t dateFix_hook(EU4Version version) {
		std::string desc = "date fix";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("64 20 77 20 6D");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// d w mw w y
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x79, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x0F, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(4), 0x6D, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(5), 0x77, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(6), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(7), 0x64, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(8), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(9), 0x0E, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(10), 0x00, true);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_12_v125_end;
	__declspec(naked) void issue_12_v125_start() {
		__asm {
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_1;
			jz issue_12_10;
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_2;
			jz issue_12_11;
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_3;
			jz issue_12_12;
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_4;
			jz issue_12_13;

			movzx eax, byte ptr[eax + ecx];
			jmp issue_12_y;

		issue_12_10:
			movzx eax, word ptr[eax + ecx + 1];
			jmp issue_12_x;

		issue_12_11:
			movzx eax, word ptr[eax + ecx + 1];
			sub eax, SHIFT_2;
			jmp issue_12_x;

		issue_12_12:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_3;
			jmp issue_12_x;

		issue_12_13:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_4;

		issue_12_x:
			movzx eax, ax;
			add ecx, 2;
			cmp eax, NO_FONT;
			ja issue_12_y;
			mov eax, NOT_DEF;

		issue_12_y:
			mov eax, dword ptr[esi + eax * 4 + 0xB4];

			push issue_12_v125_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t nudge_hook(EU4Version version) {
		std::string desc = "nudge fix (issue12)";

		switch (version) {
		case v1_27_X:
			/* これはわからなくなってしまった */
			return NOERROR;
		case v1_25_X:
		case v1_26_X:		
			byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 84 86 B4 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte ptr [eax+ecx]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_12_v125_start);
				// mov esi, [edi+10h]
				issue_12_v125_end = byte_pattern::temp_instance().get_first().address(0xB);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("misc");

		/* sub_1AFC030 大文字化キャンセル？ */
		result |= capitalizeCancel_hook(version);
		// だいぶ変更されている？ 本当に対応できているか不明。
		// そもそもこの修正がどんな効果をもたらすか忘れてしまった
		//result |= unknown_hook();
		// 日付の表記の順番を入れ替える
		result |= dateFix_hook(version);
		// nudgeモードの修正(issue12)
		result |= nudge_hook(version);

		return result;
	}
}