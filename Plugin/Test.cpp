#include "stdinc.h"
#include "byte_pattern.h"

using namespace std;

namespace Test {


#define ESCAPE_SEQ_1 0x10
#define ESCAPE_SEQ_2 0x11
#define ESCAPE_SEQ_3 0x12
#define ESCAPE_SEQ_4 0x13

#define LOW_SHIFT 0x0E
#define HIGH_SHIFT 0x9

#define SHIFT_2 LOW_SHIFT
#define SHIFT_3 0x900
#define SHIFT_4 0x8F2

#define NO_FONT 0x98F
#define NOT_DEF 0x2026


	uintptr_t j_3;
	__declspec(naked) void j_1()
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
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1でよい
			movzx eax, word ptr[ecx + eax - 1];
			sub eax, SHIFT_2;
			jmp j_1x;

		j_12:
			add eax, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1でよい
			movzx eax, word ptr[ecx + eax - 1];
			add eax, SHIFT_3;
			jmp j_1x;

		j_13:
			add eax, 2;
			mov byte ptr[ebp - 1], ESCAPE_SEQ_1; // 1でよい
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

			push j_3;
			ret;
		}
	}

	uintptr_t aa_2;
	uintptr_t loc_15D6741;
	__declspec(naked) void aa_1()
	{
		__asm {
			mov[ebp - 0x64], eax;
			test eax, eax;
			jz aa_3;

			push aa_2;
			ret;

		aa_3:
			cmp byte ptr[ebp - 1], ESCAPE_SEQ_1;
			jz aa_4;
			
			push loc_15D6741;
			ret;

		aa_4:
			mov eax, [ebp - 0x1C];
			add eax, 2;
			mov[ebp - 0x1C], eax;
			xor eax, eax;

			push loc_15D6741;
			ret;
		}
	}

	uintptr_t k_2;
	__declspec(naked) void k_a_1()
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
			mov [ebp - 0x1C], eax;
			mov eax, [ebp - 0x24];
			sub eax, 2;

		k_3:
			push k_2;
			ret;
		}
	}

	uintptr_t loc_15D7B98;
	uintptr_t loc_15D7BA1;
	__declspec(naked) void r_1()
	{
		__asm {
			cmp al, ESCAPE_SEQ_1;
			jz r_2;
			cmp al, ESCAPE_SEQ_2;
			jz r_2;
			cmp al, ESCAPE_SEQ_3;
			jz r_2;
			cmp al, ESCAPE_SEQ_4;
			jz r_2;

			lea ecx, [ebp - 0x10];
			lea edx, [ecx + 1];

			push loc_15D7B98;
			ret;

		r_2:
			mov ecx, 3;
			cmp byte ptr[ebp - 0xAC], 0x10;
			lea eax, [ebp - 0xC0];
			cmovnb eax, [ebp - 0xC0];
			mov ax, [eax + esi + 1];
			mov word ptr[ebp - 0x10 + 1], ax;
			add esi, 2;

			push loc_15D7BA1;
			ret;
		}
	}

	uintptr_t s_2;
	uintptr_t s_4;
	__declspec(naked) void s_1()
	{
		__asm {
			cmp esi, edi;
			jz s_4_jmp;
			push 0xFFFFFFFF;
			push 0;
			lea eax, [ebp - 0x128];

			push s_2;
			ret;

		s_4_jmp:
			push s_4;
			ret;
		}
	}

	uintptr_t t_2_3;
	uintptr_t loc_15D8053;
	__declspec(naked) void t_1()
	{
		__asm {
			cmp byte ptr[ecx + eax], ESCAPE_SEQ_1;
			jz t_10;
			cmp byte ptr[ecx + eax], ESCAPE_SEQ_2;
			jz t_11;
			cmp byte ptr[ecx + eax], ESCAPE_SEQ_3;
			jz t_12;
			cmp byte ptr[ecx + eax], ESCAPE_SEQ_4;
			jz t_13;
			movzx eax, byte ptr[eax + eax];
			jmp t_3;

		t_10:
			movzx eax, word ptr[ecx + eax + 1];
			jmp t_1x;

		t_11:
			movzx eax, word ptr[ecx + eax + 1];
			sub eax, SHIFT_2;
			jmp t_1x;

		t_12:
			movzx eax, word ptr[ecx + eax + 1];
			add eax, SHIFT_3;
			jmp t_1x;

		t_13:
			movzx eax, word ptr[ecx + eax + 1];
			add eax, SHIFT_4;
		
		t_1x:
			add ecx, 2;
			cmp eax, NO_FONT;
			ja t_3;
			mov eax, NOT_DEF;

		t_3:
			movzx eax, ax;

			mov eax, [edx + eax * 4];
			test eax, eax;
			jz loc_15D8053_jmp;

			push t_2_3;
			ret;

		loc_15D8053_jmp:
			push loc_15D8053;
			ret;
		}
	}

	void InitAndPatch() {

		/* sub_15D59D0 */
		byte_pattern::temp_instance().find_pattern("8A 04 01 F3 0F");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), j_1);
			j_3 = byte_pattern::temp_instance().get_first().address(0x11);

			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x19), aa_1);
			aa_2 = byte_pattern::temp_instance().get_first().address(0x24);
		}
		byte_pattern::temp_instance().find_pattern("8B 8D 1C FF FF FF 40 89 45 E4");
		if (byte_pattern::temp_instance().has_size(1)) {
			loc_15D6741 = byte_pattern::temp_instance().get_first().address();
		}

		byte_pattern::temp_instance().find_pattern("8B 45 DC 66 0F 6E 55");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), k_a_1);
		}
		byte_pattern::temp_instance().find_pattern("48 0F 5B D2 F3 0F 11 45");
		if (byte_pattern::temp_instance().has_size(1)) {
			k_2 = byte_pattern::temp_instance().get_first().address();
		}

		/* sub_15D6FD0 */
		byte_pattern::temp_instance().find_pattern("8D 4D F0 8D 51 01 8A 01 41");
		if (byte_pattern::temp_instance().has_size(2)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), r_1);
			loc_15D7B98 = byte_pattern::temp_instance().get_first().address(0x6);
			loc_15D7BA1 = byte_pattern::temp_instance().get_first().address(0xF);
			
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x1F),s_1);
			s_2 = byte_pattern::temp_instance().get_first().address(0x29);
		}
		byte_pattern::temp_instance().find_pattern("8B 45 AC 8D 55 BC 6A 01");
		if (byte_pattern::temp_instance().has_size(1)) {
			s_4 = byte_pattern::temp_instance().get_first().address();
		}
		byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 04 82 85 C0 74");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), t_1);
			t_2_3 = byte_pattern::temp_instance().get_first().address(0xB);
			loc_15D8053 = byte_pattern::temp_instance().get_first().address(0x13);
		}

		/* フォントのバッファ拡張 */
		byte_pattern::temp_instance().find_pattern("68 50 28 00 00 56 E8");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		byte_pattern::temp_instance().find_pattern("68 50 28 00 00 E8 ? ? ? ? 83");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}

		byte_pattern::temp_instance().find_pattern("68 20 28 00 00 E8 ? ? ? ? 83");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		byte_pattern::temp_instance().find_pattern("68 20 28 00 00 56 E8");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		

		/* sub_1936F30 入力の修正 */

		/* sub_1974E10 入力の修正 */


		
	}
}
