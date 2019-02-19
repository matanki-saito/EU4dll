#include "stdinc.h"
#include "byte_pattern.h"

namespace MapView {

	/*-----------------------------------------------*/

	uintptr_t map1_v125_end;
	__declspec(naked) void map1_v125_start()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz l_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz l_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz l_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz l_13;

			mov al, [eax + edi];
			lea ecx, [ebp - 0x80];
			mov byte ptr[ebp - 0x38], al;
			jmp l_2;

		l_10:
			movzx eax, word ptr[eax + edi + 1];
			lea ecx, [ebp - 0x38];
			mov byte ptr[ecx], ESCAPE_SEQ_1;
			mov[ecx + 1], ax;
			jmp l_1x;

		l_11:
			movzx eax, word ptr[eax + edi + 1];
			lea ecx, [ebp - 0x38];
			mov byte ptr[ecx], ESCAPE_SEQ_2;
			mov[ecx + 1], ax;
			jmp l_1x;

		l_12:
			movzx eax, word ptr[eax + edi + 1];
			lea ecx, [ebp - 0x38];
			mov byte ptr[ecx], ESCAPE_SEQ_3;
			mov[ecx + 1], ax;
			jmp l_1x;

		l_13:
			movzx eax, word ptr[eax + edi + 1];
			lea ecx, [ebp - 0x38];
			mov byte ptr[ecx], ESCAPE_SEQ_4;
			mov[ecx + 1], ax;

		l_1x:
			lea ecx, [ebp - 0x80];

		l_2:
			push map1_v125_end;
			ret;
		}
	}

	uintptr_t map1_v127_end;
	__declspec(naked) void map1_v127_start()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz l_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz l_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz l_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz l_13;

			mov al, [eax + edi];
			lea ecx, [ebp - 0x58];
			mov byte ptr[ebp - 0x2C], al;
			jmp l_2;

		l_10:
			movzx eax, word ptr[eax + edi + 1];
			lea ecx, [ebp - 0x2C];
			mov byte ptr[ecx], ESCAPE_SEQ_1;
			mov word ptr [ecx + 1], ax;
			jmp l_1x;

		l_11:
			movzx eax, word ptr[eax + edi + 1];
			lea ecx, [ebp - 0x2C];
			mov byte ptr[ecx], ESCAPE_SEQ_2;
			mov word ptr [ecx + 1], ax;
			jmp l_1x;

		l_12:
			movzx eax, word ptr[eax + edi + 1];
			lea ecx, [ebp - 0x2C];
			mov byte ptr[ecx], ESCAPE_SEQ_3;
			mov word ptr [ecx + 1], ax;
			jmp l_1x;

		l_13:
			movzx eax, word ptr[eax + edi + 1];
			lea ecx, [ebp - 0x2C];
			mov byte ptr[ecx], ESCAPE_SEQ_4;
			mov word ptr [ecx + 1], ax;

		l_1x:
			lea ecx, [ebp - 0x58];

		l_2:
			push map1_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t map2_v125_end;
	__declspec(naked) void map2_v125_start()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz m_3;
			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz m_3;
			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz m_3;
			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz m_3;
			jmp m_4;

		m_3:
			mov ecx, [ebp - 0x38];
			mov[eax], ecx;
			mov byte ptr[eax + 0x10], 3;

		m_4:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push map2_v125_end;
			ret;
		}
	}

	uintptr_t map2_v127_end;
	__declspec(naked) void map2_v127_start()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz m_3;
			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz m_3;
			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz m_3;
			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz m_3;
			jmp m_4;

		m_3:
			mov ecx, [ebp - 0x2C];
			mov dword ptr [eax], ecx;
			mov byte ptr[eax + 0x10], 3;

		m_4:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push map2_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t map1_2_hook(EU4Version version){
		std::string desc = "map font view 1";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("8A 04 38 8D 4D A8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al, [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map1_v127_start);
				// push [ebp-0x2C]
				map1_v127_end = byte_pattern::temp_instance().get_first().address(0x9);
				// push 0FFFFFFFFh
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x11), map2_v127_start);
				// lea ecx.[ebp-0xA0]
				map2_v127_end = byte_pattern::temp_instance().get_first().address(0x16);
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_25_X:
		case v1_26_X:

			byte_pattern::temp_instance().find_pattern("8A 04 38 8D 4D 80");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al, [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map1_v125_start);
				// push [ebp-0x38]
				map1_v125_end = byte_pattern::temp_instance().get_first().address(0x9);
				// push 0FFFFFFFFh
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x11), map2_v125_start);
				// lea ecx.[ebp-0x98]
				map2_v125_end = byte_pattern::temp_instance().get_first().address(0x16);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t map3_v125_end;
	__declspec(naked) void map3_v125_start()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz n_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz n_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz n_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz n_13;

			movzx eax, byte ptr[eax + edi];
			jmp n_3;

		n_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp n_1x;

		n_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp n_1x;

		n_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp n_1x;

		n_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;

		n_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja n_4;
			mov eax, NOT_DEF;

		n_4:
			add edi, 2;

		n_3:
			mov ecx, [ebp - 0x1C];

			push map3_v125_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t map3_hook(EU4Version version) {
		std::string desc = "map font view 3";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("8A 04 38 8B 4D E4");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al, [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map3_v125_start);
				// mov edx, [ecx+eax*4 + 0xB4h]
				map3_v125_end = byte_pattern::temp_instance().get_first().address(0x9);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t map4_v125_end;
	__declspec(naked) void map4_v125_start()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz o_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz o_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz o_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz o_13;
			jmp o_3;

		o_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp o_1x;

		o_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp o_1x;

		o_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp o_1x;

		o_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		o_1x:
			add esi, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja o_4;
			mov eax, NOT_DEF;
			jmp o_4;

		o_3:
			movzx eax, byte ptr[eax + esi];

		o_4:
			mov edi, [ebx + eax * 4];

			push map4_v125_end;
			ret;
		}
	}

	uintptr_t map4_v127_end;
	__declspec(naked) void map4_v127_start()
	{
		__asm {
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz o_10;
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz o_11;
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz o_12;
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz o_13;
			jmp o_3;

		o_10:
			movzx eax, word ptr[eax + ebx + 1];
			jmp o_1x;

		o_11:
			movzx eax, word ptr[eax + ebx + 1];
			sub eax, SHIFT_2;
			jmp o_1x;

		o_12:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_3;
			jmp o_1x;

		o_13:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_4;

		o_1x:
			add ebx, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja o_4;
			mov eax, NOT_DEF;
			jmp o_4;

		o_3:
			movzx eax, byte ptr[eax + ebx];

		o_4:
			mov esi, [edi + eax * 4];
			mov [ebp - 0xD0], esi;
			mov [ebp - 0x100], esi;

			push map4_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t map4_hook(EU4Version version) {
		std::string desc = "map font view 4";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 18 8B 34 87 89 B5 30");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax byte ptr [eax+ebx]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map4_v127_start);
				// test esi, esi
				map4_v127_end = byte_pattern::temp_instance().get_first().address(0x13);
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 3C 83");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte ptr [eax+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), map4_v125_start);
				// test edi, edi
				map4_v125_end = byte_pattern::temp_instance().get_first().address(0x7);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("font view");

		result |= map1_2_hook(version);
		result |= map3_hook(version);
		result |= map4_hook(version);

		return result;
	}
}