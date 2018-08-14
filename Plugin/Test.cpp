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
	}
}
