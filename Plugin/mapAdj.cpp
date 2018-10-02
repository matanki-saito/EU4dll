#include "stdinc.h"
#include "byte_pattern.h"

namespace Test {

	/*-----------------------------------------------*/

	// v1.25.X
	// v1.26.X
	uintptr_t map1_v125_end;
	__declspec(naked) void map1_v125_start()
	{
		__asm {
			cmp byte ptr[ecx + eax], ESCAPE_SEQ_1;
			jz j_10;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_2;
			jz j_11;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_3;
			jz j_12;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_4;
			jz j_13;

			jmp j_01;

		j_10:
			add eax, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1;
			movzx eax, word ptr[ecx + eax - 1];
			jmp j_1x;

		j_11:
			add eax, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1Ç≈ÇÊÇ¢
			movzx eax, word ptr[ecx + eax - 1];
			sub eax, SHIFT_2;
			jmp j_1x;

		j_12:
			add eax, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1Ç≈ÇÊÇ¢
			movzx eax, word ptr[ecx + eax - 1];
			add eax, SHIFT_3;
			jmp j_1x;

		j_13:
			add eax, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1Ç≈ÇÊÇ¢
			movzx eax, word ptr[ecx + eax - 1];
			add eax, SHIFT_4;
			jmp j_1x;

		j_01:
			mov al, [ecx + eax];
			mov[ebp - 1], al;
			movzx eax, al;
			jmp j_2;

		j_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja j_2;
			mov eax, NOT_DEF;

		j_2:
			movss xmm0, dword ptr[edx + 0x428];

			push map1_v125_end;
			ret;
		}
	}

	// v1.27.X
	uintptr_t map1_v127_end;
	__declspec(naked) void map1_v127_start()
	{
		__asm {
			cmp byte ptr[eax + edx], ESCAPE_SEQ_1;
			jz j_10;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_2;
			jz j_11;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_3;
			jz j_12;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_4;
			jz j_13;

			jmp j_01;

		j_10:
			add edx, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1;
			movzx eax, word ptr[eax + edx - 1];
			jmp j_1x;

		j_11:
			add edx, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1Ç≈ÇÊÇ¢
			movzx eax, word ptr[eax + edx - 1];
			sub eax, SHIFT_2;
			jmp j_1x;

		j_12:
			add edx, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1Ç≈ÇÊÇ¢
			movzx eax, word ptr[eax + edx - 1];
			add eax, SHIFT_3;
			jmp j_1x;

		j_13:
			add edx, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1Ç≈ÇÊÇ¢
			movzx eax, word ptr[eax + edx - 1];
			add eax, SHIFT_4;
			jmp j_1x;

		j_01:
			mov al, [eax + edx];
			mov[ebp - 1], al;
			movzx eax, al;
			jmp j_2;

		j_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja j_2;
			mov eax, NOT_DEF;

		j_2:
			movss xmm0, dword ptr[ecx + 0x428];

			push map1_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	// v1.25.X
	uintptr_t map2_v125_end;
	uintptr_t map2_v125_end2;
	__declspec(naked) void map2_v125_start()
	{
		__asm {
			test eax, eax;
			jz aa_3;

			push map2_v125_end;
			ret;

		aa_3:
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jz aa_4;

			push map2_v125_end2;
			ret;

		aa_4:
			mov eax, [ebp - 0x1C];
			add eax, 2;
			mov[ebp - 0x1C], eax;
			xor eax, eax;

			push map2_v125_end2;
			ret;
		}
	}

	// v1.27.X
	uintptr_t map2_v127_end;
	uintptr_t map2_v127_end2;
	__declspec(naked) void map2_v127_start()
	{
		__asm {
			test eax, eax;
			jz aa_3;

			push map2_v127_end;
			ret;

		aa_3:
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jz aa_4;

			push map2_v127_end2;
			ret;

		aa_4:
			add edx, 2;
			mov[ebp - 0x28], edx;

			push map2_v127_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t map1_2_hook() {
		// v1.27.X
		byte_pattern::temp_instance().find_pattern("8A 04 10 F3 0F");
		if (byte_pattern::temp_instance().has_size(1)) {
			// mov al,[eax+edx]
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map1_v127_start);
			// movss dword ptr [ebp-5Ch],xmm0
			map1_v127_end = byte_pattern::temp_instance().get_first().address(0x11);
			// test eax,eax
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x1C), map2_v127_start);
			// cmp word ptr [eax+6],0
			map2_v127_end = byte_pattern::temp_instance().get_first().address(0x24);
		}
		else {
			// v1.25.X
			// v1.26.X
			byte_pattern::temp_instance().find_pattern("8A 04 01 F3 0F");
			if (byte_pattern::temp_instance().has_size(1)) {
				// mov al,[ecx+eax]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map1_v125_start);
				// movss dword ptr [ebp-2Ch],xmm0
				map1_v125_end = byte_pattern::temp_instance().get_first().address(0x11);
				// test eax,eax
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x1C), map2_v125_start);
				// cmp word ptr [eax+6],0
				map1_v125_end = byte_pattern::temp_instance().get_first().address(0x24);
			}
			else {
				return 1;
			}
		}
	}
	errno_t map2_end_hook() {
		// v1.27.X
		byte_pattern::temp_instance().find_pattern("F2 0F 10 65 C8 42 F2 0F");
		if (byte_pattern::temp_instance().has_size(1)) {
			// mov eax. [ebp-1Ch]
			map2_v127_end2 = byte_pattern::temp_instance().get_first().address();
		}
		else {
			// v1.26.X
			byte_pattern::temp_instance().find_pattern("8B 45 E4 8B 4D 9C 40 89");
			if (byte_pattern::temp_instance().has_size(1)) {
				// mov eax. [ebp-1Ch]
				map2_v125_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else {
				// v1.25.X
				byte_pattern::temp_instance().find_pattern("8B 45 E4 8B 8D 1C FF FF");
				if (byte_pattern::temp_instance().has_size(1)) {
					// TODO
					map2_v125_end2 = byte_pattern::temp_instance().get_first().address();
				}
				else {
					return 1;
				}
			}
		}

		return 0;
	}

	/*-----------------------------------------------*/

	uintptr_t map3_v125_end;
	__declspec(naked) void map3_v125_start()
	{
		__asm {
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jnz k_a_2;
			cmp dword ptr[ebp - 0x24], 3;
			ja k_a_2;
			mov eax, [ebp - 0x1C];
			add eax, 2;
			mov[ebp - 0x1C], eax;
			mov eax, [ebp - 0x24];
			add eax, 2;
			mov[ebp - 0x24], eax;
			mov byte ptr[ebp - 1], 5;

		k_a_2:
			movd xmm2, dword ptr[ebp - 0x1C];
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jz k_4;
			mov eax, [ebp - 0x24];
			jmp k_3;

		k_4:
			mov eax, [ebp - 0x1C];
			add eax, 2;
			mov[ebp - 0x1C], eax;
			mov eax, [ebp - 0x24];
			sub eax, 2;

		k_3:
			push map3_v125_end;
			ret;
		}
	}

	uintptr_t map3_v126_end;
	__declspec(naked) void map3_v126_start()
	{
		__asm {
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jnz k_a_2;
			cmp dword ptr[ebp - 0x24], 3;
			ja k_a_2;
			mov eax, [ebp - 0x1C];
			add eax, 2;
			mov[ebp - 0x1C], eax;
			mov eax, [ebp - 0x24];
			add eax, 2;
			mov[ebp - 0x24], eax;
			mov byte ptr[ebp - 1], 5;

		k_a_2:
			movd xmm1, dword ptr[ebp - 0x1C];
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jz k_4;
			mov eax, [ebp - 0x24];
			jmp k_3;

		k_4:
			mov eax, [ebp - 0x1C];
			add eax, 2;
			mov[ebp - 0x1C], eax;
			mov eax, [ebp - 0x24];
			sub eax, 2;

		k_3:
			push map3_v126_end;
			ret;
		}
	}

	uintptr_t map3_v127_end;
	__declspec(naked) void map3_v127_start()
	{
		__asm {
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jnz k_a_2;
			cmp dword ptr[ebp - 0x24], 3;
			ja k_a_2;
			add edx, 2;
			mov[ebp - 0x28], edx;
			mov eax, [ebp - 0x24];
			add eax, 2;
			mov[ebp - 0x24], eax;
			mov byte ptr[ebp - 1], 5;

		k_a_2:
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jz k_4;
			mov eax, [ebp - 0x24];
			jmp k_3;

		k_4:
			add edx, 2;
			mov[ebp - 0x28], edx;
			mov eax, [ebp - 0x24];
			sub eax, 2;

		k_3:
			dec eax;
			movd xmm7, edx;

			push map3_v127_end;
			ret;
		}
	}

	// àÍï∂éöï\é¶ÇÃí≤êÆ
	errno_t map3_hook() {
		// v1.27.X
		byte_pattern::temp_instance().find_pattern("8B 45 DC 48 66 0F 6E FA");
		if (byte_pattern::temp_instance().has_size(1)) {
			// mov eax,[ebp-24h]
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map3_v127_start);
			// cvtdq2ps xmm7,xmm7
			map3_v127_end = byte_pattern::temp_instance().get_first().address(0x8);
		}
		else {
			// v1.26.X
			byte_pattern::temp_instance().find_pattern("8B 45 DC 66 0F 6E 4D E4");
			if (byte_pattern::temp_instance().has_size(1)) {
				// mov eax,[ebp-24h]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map3_v126_start);
				// dec eax
				map3_v126_end = byte_pattern::temp_instance().get_first().address(0x8);
			}
			else {
				// 1.25.X
				byte_pattern::temp_instance().find_pattern("8B 45 DC 66 0F 6E 55");
				if (byte_pattern::temp_instance().has_size(1)) {
					// TODO
					injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map3_v125_start);
				}
				else {
					return 1;
				}

				byte_pattern::temp_instance().find_pattern("48 0F 5B D2 F3 0F 11 45");
				if (byte_pattern::temp_instance().has_size(1)) {
					// TODO
					map3_v125_end = byte_pattern::temp_instance().get_first().address();
				}
				else {
					return 1;
				}
			}
		}
	}

	/*-----------------------------------------------*/

	errno_t InitAndPatchMapAdj() {
		errno_t result = 0;

		result |= map1_2_hook();
		result |= map2_end_hook();
		result |= map3_hook();

		return result;
	}
}