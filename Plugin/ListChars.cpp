#include "stdinc.h"
#include "byte_pattern.h"

namespace ListChars {

	/*-----------------------------------------------*/

	uintptr_t issue_99_func1_v128_end;
	__declspec(naked) void issue_99_func1_v128_start() {

		__asm {
			cmp byte ptr[esi + edx], ESCAPE_SEQ_1;
			jz j_10;

			cmp byte ptr[esi + edx], ESCAPE_SEQ_2;
			jz j_11;

			cmp byte ptr[esi + edx], ESCAPE_SEQ_3;
			jz j_12;

			cmp byte ptr[esi + edx], ESCAPE_SEQ_4;
			jz j_13;

			jmp j_01;

		j_10:
			movzx eax, word ptr[esi + edx + 1];
			jmp j_1x;

		j_11:
			movzx eax, word ptr[esi + edx + 1];
			sub eax, SHIFT_2;
			jmp j_1x;

		j_12:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_3;
			jmp j_1x;

		j_13:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_4;
			jmp j_1x;

		j_01:
			mov al, byte ptr[eax + edx];
			movzx eax, al;
			jmp j_2;

		j_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja j_2;
			mov eax, NOT_DEF;

		j_2:
			movss xmm0, dword ptr[ecx + 0x428];

			test    eax, eax;

			push issue_99_func1_v128_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_hook(EU4Version version) {
		std::string desc = "func1";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			return NOERROR;

		case v1_28_X:

			// mov     eax, [esi+edx*4]
			byte_pattern::temp_instance().find_pattern("8B 04 96 85 C0 74 48 80 78 0E 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_99_func1_v128_start);
				// jz xxxx
				issue_99_func1_v128_end = byte_pattern::temp_instance().get_first().address(5);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue_99_func2_1_v128_end;
	__declspec(naked) void issue_99_func2_1_v128_start() {

		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz j_10;

			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz j_11;

			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz j_12;

			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz j_13;

			jmp j_01;

		j_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp j_1x;

		j_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp j_1x;

		j_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp j_1x;

		j_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;
			jmp j_1x;

		j_01:
			mov al, byte ptr[eax + edi];
			movzx eax, al;
			jmp j_2;

		j_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja j_2;
			mov eax, NOT_DEF;
		j_2:
			mov edx, [ebp - 0x54];
			movss xmm0, dword ptr[edx + 0x428];

			push issue_99_func2_1_v128_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t issue_99_func2_2_v128_end;
	__declspec(naked) void issue_99_func2_2_v128_start() {

		__asm {

			mov eax, dword ptr [esi + 0x14];
			cmp eax, 0x10;
			jb j_a;
			mov eax, dword ptr [esi];
			jmp j_b;
		j_a:
			mov eax, esi;
		j_b:
			
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz j_1x;

			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz j_1x;

			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz j_1x;

			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz j_1x;

		j_01:
			inc edi;
			jmp j_2;

		j_1x:
			add edi, 3;
		j_2:
			mov eax, dword ptr [esi + 0x10];
			mov dword ptr [ebp - 0x38], edi;
			push issue_99_func2_2_v128_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t issue_99_func2_3_v128_end;
	__declspec(naked) void issue_99_func2_3_v128_start() {

		__asm {
			mov     eax, [eax + edi];
			push [ebp  - 0x60];
			mov     ecx, [ebp - 0x54];
			mov     dword ptr[ebp - 0x64], eax;

			push issue_99_func2_3_v128_end;
			ret;
		}
	}

	/*-----------------------------------------------*/
	
	errno_t func2_hook(EU4Version version) {
		std::string desc = "func2";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			return NOERROR;

		case v1_28_X:
			// フォント読み出し
			// mov     al, [eax+edi]
			byte_pattern::temp_instance().find_pattern("8A 04 38 8B 55 AC 0F B6 C0");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_99_func2_1_v128_start);
				// mov     ebx, [edx+eax*4]
				issue_99_func2_1_v128_end = byte_pattern::temp_instance().get_first().address(0x11);
			}
			else return EU4_ERROR1;

			// 上で2byte進めるとうまくいかないので、処理の最後でカウントを増やす
			// mov     eax, [esi+10h]
			byte_pattern::temp_instance().find_pattern("8B 46 10 47 89 7D C8 89 45 08");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_99_func2_2_v128_start);
				// mov     [ebp+arg_0], eax
				issue_99_func2_2_v128_end = byte_pattern::temp_instance().get_first().address(0x7);
			}
			else return EU4_ERROR1;

			//// func1の引数を変更
			//// mov     al, [eax+edi]
			//byte_pattern::temp_instance().find_pattern("8A 04 38 FF 75 A0 8B 4D AC 88 45 9C");
			//if (byte_pattern::temp_instance().has_size(1, desc)) {
			//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_99_func2_3_v128_start);
			//	// push    [ebp+var_64]
			//	issue_99_func2_3_v128_end = byte_pattern::temp_instance().get_first().address(0xC);
			//}
			//else return EU4_ERROR1;

			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/


	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("issue-99 fix");

		//result |= func1_hook(version);

		result |= func2_hook(version);

		return result;
	}
}