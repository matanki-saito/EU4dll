#include "stdinc.h"
#include "byte_pattern.h"

using namespace std;

namespace Test {

















	uintptr_t q_2_1;
	__declspec(naked) void q_1()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz q_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz q_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz q_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz q_13;
			movzx eax, byte ptr[eax + edi];
			jmp q_4;

		q_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp q_1x;

		q_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp q_1x;

		q_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp q_1x;

		q_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;
			
		q_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja q_3;
			mov eax, NOT_DEF;

		q_3:
			add edi, 2;

		q_4:
			mov ecx, [ebp - 0x28];
			mov[ebp - 0x31A], ax;
			movzx eax, ax;

			mov ecx, [ecx + eax * 4];

			push q_2_1;
			ret;
		}
	}

	uintptr_t bb_3;
	uintptr_t bb_2;
	__declspec(naked) void bb_1()
	{
		__asm {
			lahf;
			test ah, 0x44;
			jnp bb_3_jmp;

			cmp word ptr [ebp - 0x31A], 0xFF;
			jb bb_2_jmp;

		bb_3_jmp:
			push bb_3;
			ret;

		bb_2_jmp:
			push bb_2;
			ret;
		}
	}













	




	uintptr_t issue_12_end;
	__declspec(naked) void issue_12_start() {
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
			mov eax,dword ptr [esi + eax * 4 + 0xB4];
			
			push issue_12_end;
			ret;
		}
	}

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


	void InitAndPatch() {





		//
		///* sub_199B240 : イベントダイアログ調整？ */
		//byte_pattern::temp_instance().find_pattern("81 EC 0C 03 00 00 8B");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x2), 0x0E, true);
		//}
		//byte_pattern::temp_instance().find_pattern("0F B6 04 38 8B 4D D8 8B 0C");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), q_1);
		//	//q_2_1 = byte_pattern::temp_instance().get_first().address(0xA);
		//}
		//byte_pattern::temp_instance().find_pattern("9F F6 C4 44 7A 58 66");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), bb_1);
		//	//bb_3 = byte_pattern::temp_instance().get_first().address(0x6);
		//}
		//byte_pattern::temp_instance().find_pattern("8B 45 14 8B 4D D4 8B 55");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//bb_2 = byte_pattern::temp_instance().get_first().address();
		//}
		//














		///* issue-12 nudgeモード修正 */
		//// 1.25.1.0, 1.26.0.0
		//byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 84 86 B4 00 00 00");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_12_start);
		//	//issue_12_end = byte_pattern::temp_instance().get_first().address(0xB);
		//}

		///* issue-19 */
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("83 C4 08 33 C0 E9 82 F8 FF FF");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xE), issue_19_keydown_start);
		//	issue_19_keydown_end = byte_pattern::temp_instance().get_first().address(0xE + 0xB);
		//}
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("55 8B EC 83 EC 40 56 8B 75 0C");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	sub_135FBC0 = byte_pattern::temp_instance().get_first().address(0x0);
		//}
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("83 FE 46 75 11 80 78 46 00 75");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xB), issue_19_keypress_start);
		//	issue_19_keypress_end = byte_pattern::temp_instance().get_first().address(0xB + 0xB);
		//}
	}
}
