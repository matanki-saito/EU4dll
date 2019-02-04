#include "stdinc.h"
#include "byte_pattern.h"

// これはpopup windowではなくて、map上で浮かび上がる文字の部分の修正
namespace PopupCharOnMap {

	/*-----------------------------------------------*/

	uintptr_t func1_v125_end;
	__declspec(naked) void func1_v125_start()
	{
		__asm {
			mov eax, [eax + edi];
			mov[ebp - 0x5C], eax;
			lea ecx, [ebp - 0xAC];

			push func1_v125_end;
			ret;
		}
	}

	uintptr_t func2_v125_end;
	__declspec(naked) void func2_v125_start()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz x_4;
			jmp x_3;

		x_4:
			mov ecx, [ebp - 0x5C];
			mov[eax], ecx;
			lea ecx, [eax];
			mov byte ptr[ecx + 0x10], 3;

		x_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push func2_v125_end;
			ret;
		}
	}

	uintptr_t func1_v127_end;
	__declspec(naked) void func1_v127_start()
	{
		__asm {
			mov eax, [eax + edi];
			mov[ebp - 0x28], eax;
			lea ecx, [ebp - 0xD8];

			push func1_v127_end;
			ret;
		}
	}

	uintptr_t func2_v127_end;
	__declspec(naked) void func2_v127_start()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz x_4;
			jmp x_3;

		x_4:
			mov ecx, [ebp - 0x28];
			mov[eax], ecx;
			lea ecx, [eax];
			mov byte ptr[ecx + 0x10], 3;

		x_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push func2_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_2_hook(EU4Version version) {
		std::string desc = "func1,2";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("8A 04 38 8D 8D 28 FF FF FF 88 45 D8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al,[eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func1_v127_start);
				// push [ebp+var_28]
				func1_v127_end = byte_pattern::temp_instance().get_first().address(0xC);

				// push 0FFFFFFFFh
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), func2_v127_start);
				// lea ecx,[ebp+var_AC]
				func2_v127_end = byte_pattern::temp_instance().get_first().address(0x19);
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("8A 04 38 8D 8D 54");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				// mov al,[eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func1_v125_start);
				// push [ebp+var_5C]
				func1_v125_end = byte_pattern::temp_instance().get_first().address(0xC);

				// push 0FFFFFFFFh
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), func2_v125_start);
				// lea ecx,[ebp+var_7C]
				func2_v125_end = byte_pattern::temp_instance().get_first().address(0x19);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func3_v125_end;
	__declspec(naked) void func3_v125_start()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz y_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz y_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz y_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz y_13;
			jmp y_7;

		y_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp y_1x;

		y_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp y_1x;

		y_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp y_1x;

		y_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;

		y_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja y_4;
			mov eax, NOT_DEF;

		y_4:
			add edi, 2;
			jmp y_6;

		y_7:
			mov al, [eax + edi];
			movzx eax, al;

		y_6:
			push func3_v125_end;
			ret;
		}
	}

	uintptr_t func3_v127_end;
	__declspec(naked) void func3_v127_start()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz y_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz y_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz y_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz y_13;
			jmp y_7;

		y_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp y_1x;

		y_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp y_1x;

		y_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp y_1x;

		y_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;

		y_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja y_4;
			mov eax, NOT_DEF;

		y_4:
			add edi, 2;
			jmp y_6;

		y_7:
			mov al, [eax + edi];
			movzx eax, al;

		y_6:
			mov ecx, [ebp - 0x10];
			add ecx, 0xB4;
			mov[ebp - 0x20], ecx;

			push func3_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func3_hook(EU4Version version) {
		std::string desc = "func 3";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("8A 04 38 8B 4D F0");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al, [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func3_v127_start);
				// mov ecx, [ecx+eax*4]
				func3_v127_end = byte_pattern::temp_instance().get_first().address(0x12);
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("8A 04 38 0F B6");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al, [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func3_v125_start);
				// mov edx, [ebx+eax*4+0xB4]
				func3_v125_end = byte_pattern::temp_instance().get_first().address(0x6);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func4_v125_end;
	__declspec(naked) void func4_v125_start()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz z_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz z_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz z_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz z_13;
			jmp z_5;

		z_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp z_1x;

		z_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp z_1x;

		z_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp z_1x;

		z_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		z_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja z_4;
			mov eax, NOT_DEF;

		z_4:
			add esi, 2;
		z_6:
			mov edx, [edx + eax * 4];

			push func4_v125_end;
			ret;

		z_5:
			movzx eax, byte ptr[eax + esi];
			jmp z_6;
		}
	}

	uintptr_t func4_v127_end;
	__declspec(naked) void func4_v127_start()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz z_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz z_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz z_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz z_13;
			movzx eax, byte ptr[eax + esi];
			jmp z_6;

		z_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp z_1x;

		z_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp z_1x;

		z_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp z_1x;

		z_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		z_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja z_4;
			mov eax, NOT_DEF;

		z_4:
			add esi, 2;
			mov dword ptr[ebp - 0x2C], esi; // ローカル変数更新
		z_6:
			movss [ebp - 0xBC], xmm4;
			mov eax, [ecx + eax * 4 + 0xB4];
			
			push func4_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func4_hook(EU4Version version) {
		std::string desc = "func 4";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 30 F3 0F 11 A5 44 FF FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte ptr [eax+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func4_v127_start);
				// mov [ebp+var_20],eax
				func4_v127_end = byte_pattern::temp_instance().get_first().address(0x13);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 14 82 89 55");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte ptr [eax+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func4_v125_start);
				// mov [ebp+var_34],edx
				func4_v125_end = byte_pattern::temp_instance().get_first().address(0x7);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("popup char on map fix");

		// 
		result |= func1_2_hook(version);
		// 
		result |= func3_hook(version);
		//
		result |= func4_hook(version);

		return result;
	}
}