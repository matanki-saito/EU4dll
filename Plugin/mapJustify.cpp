#include "stdinc.h"
#include "byte_pattern.h"

namespace MapJustify {

	/*-----------------------------------------------*/

	uintptr_t map1_v125_end;
	uintptr_t map1_v125_end2;
	__declspec(naked) void map1_v125_start()
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

			push map1_v125_end;
			ret;

		r_2:
			mov ecx, 3;
			cmp byte ptr[ebp - 0xAC], 0x10;
			lea eax, [ebp - 0xC0];
			cmovnb eax, [ebp - 0xC0];
			mov ax, [eax + esi + 1];
			mov word ptr[ebp - 0x10 + 1], ax;
			add esi, 2;

			push map1_v125_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t map2_v125_end;
	uintptr_t map2_v125_end2;
	__declspec(naked) void map2_v125_start()
	{
		__asm {
			cmp esi, edi;
			jz s_4_jmp;
			push 0xFFFFFFFF;
			push 0;
			lea eax, [ebp - 0x128];

			push map2_v125_end;
			ret;

		s_4_jmp:
			push map2_v125_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t map1_2_hook(EU4Version version) {
		std::string desc = "map justify 1";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			byte_pattern::temp_instance().find_pattern("8D 4D F0 8D 51 01 8A 01 41");
			if (byte_pattern::temp_instance().has_size(1, desc) || byte_pattern::temp_instance().has_size(2, desc)) {
				// lea ecx,[ebp-0x10]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map1_v125_start);
				// mov al,[ecx]
				map1_v125_end = byte_pattern::temp_instance().get_first().address(0x6);
				// push ecx
				map1_v125_end2 = byte_pattern::temp_instance().get_first().address(0xF);

				// push 0FFFFFFFFh
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x1F), map2_v125_start);
				// push eax
				map2_v125_end = byte_pattern::temp_instance().get_first().address(0x29);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	errno_t map2_end2_hook(EU4Version version) {
		std::string desc = "map justify 2";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			byte_pattern::temp_instance().find_pattern("8B 45 AC 8D 55 BC 6A 01");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov eax,[ebp-0x54]
				map2_v125_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t map3_v125_end;
	uintptr_t map3_v125_end2;
	__declspec(naked) void map3_v125_start()
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
			movzx eax, byte ptr[ecx + eax];
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

			push map3_v125_end;
			ret;

		loc_15D8053_jmp:
			push map3_v125_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t map3_hook(EU4Version version) {
		std::string desc = "map justify 3";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 04 82 85 C0 74");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte ptr [eax+ecx]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map3_v125_start);
				// cmp word ptr [eax+6], 0
				map3_v125_end = byte_pattern::temp_instance().get_first().address(0xB);
				// inc ecx
				map3_v125_end2 = byte_pattern::temp_instance().get_first().address(0x13);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("map font justify");

		result |= map1_2_hook(version);
		result |= map2_end2_hook(version);
		result |= map3_hook(version);

		return result;
	}
}