#include "stdinc.h"
#include "byte_pattern.h"

namespace EventDialog {

	/*-----------------------------------------------*/

	errno_t changeStackSize_hook(EU4Version version) {
		std::string desc = "change stack size";

		switch (version) {
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("81 EC 08 03 00 00 8B 45");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// sub esp,308h -(+2)-> 30A -(+C)-> 0x316
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x2), 0x0A, true);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("81 EC 0C 03 00 00 8B");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// sub esp,30Ch -(+2)-> 30E -(+Ch)-> 0x31A
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x2), 0x0E, true);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func1_v125_end;
	__declspec(naked) void func1_v125_start()
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

			push func1_v125_end;
			ret;
		}
	}

	uintptr_t func1_v127_end;
	__declspec(naked) void func1_v127_start()
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
			mov[ebp - 0x316], ax;
			movzx eax, ax;

			mov ecx, [ecx + eax * 4];

			push func1_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_hook(EU4Version version) {
		std::string desc = "func1";

		switch (version) {
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 38 8B 4D D8 8B 0C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte otr [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func1_v127_start);
				//mov eax,[ebp+var_28]
				func1_v127_end = byte_pattern::temp_instance().get_first().address(0xA);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 38 8B 4D D8 8B 0C");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte otr [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func1_v125_start);
				//mov eax,[ebp+var_28]
				func1_v125_end = byte_pattern::temp_instance().get_first().address(0xA);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func2_v125_end;
	uintptr_t func2_v125_end2;
	__declspec(naked) void func2_v125_start()
	{
		__asm {
			lahf;
			test ah, 0x44;
			jnp bb_3_jmp;

			cmp word ptr[ebp - 0x31A], 0xFF;
			jb bb_2_jmp;

		bb_3_jmp:
			push func2_v125_end;
			ret;

		bb_2_jmp:
			push func2_v125_end2;
			ret;
		}
	}

	uintptr_t func2_v127_end;
	uintptr_t func2_v127_end2;
	__declspec(naked) void func2_v127_start()
	{
		__asm {
			lahf;
			test ah, 0x44;
			jnp bb_3_jmp;

			cmp word ptr[ebp - 0x316], 0xFF;
			jb bb_2_jmp;

		bb_3_jmp:
			push func2_v127_end;
			ret;

		bb_2_jmp:
			push func2_v127_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func2_hook(EU4Version version) {
		std::string desc = "func2";

		switch (version) {
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("9F F6 C4 44 7A 58 66");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				// lahf
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func2_v127_start);
				// movd xmm0, [ ebp+var_2C]
				func2_v127_end = byte_pattern::temp_instance().get_first().address(0x6);
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("8B 45 14 8B 4D D4 8B 55");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				// mov eax, [ebp + arc_C]
				func2_v127_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("9F F6 C4 44 7A 58 66");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lahf
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func2_v125_start);
				// movd xmm0, [ ebp+var_2C]
				func2_v125_end = byte_pattern::temp_instance().get_first().address(0x6);
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("8B 45 14 8B 4D D4 8B 55");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov eax, [ebp + arc_C]
				func2_v125_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("event dialog");

		/* スタックサイズ変更 */
		result |= changeStackSize_hook(version);

		/**/
		result |= func1_hook(version);

		/**/
		result |= func2_hook(version);

		return result;
	}
}