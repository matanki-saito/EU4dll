#include "stdinc.h"
#include "byte_pattern.h"

namespace ButtonAndToolTip {
	/*-----------------------------------------------*/
	
	errno_t stackSize_hook(EU4Version version) {
		std::string desc = "stack size";

		switch (version) {
		
		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("81 EC 58 05 00 00 8B");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				//    | edi  | [ebp-(0x558+0xC+0x8)] =(+2)=> [ebp-(0x55A+0xC+0x8)]
				//    | esi
				//    | Stack (0x558) =(+2)=> (0x55A) : [ebp-(0x55A+0xC)]=[ebp-0x566]
				//    | large fs:0          | (4*3 = 12 = 0xC)
				//    | offset SEH_11C0050  |
				//    | 0FFFFFFFFh          |
				//ebp | ebp
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x5A, true);
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("81 EC 98 05 00 00 8B 55 18");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				//    | edi  |  [ebp-(0x598+0xC+0x8)] =(+2)=> [ebp-(0x59A+0xC+0x8)]
				//    | esi
				//    | Stack (0x598) =(+2)=> (0x59A) : [ebp-(0x59A+0xC)]=[ebp-0x5A6]
				//    | large fs:0          | (4*3 = 12 = 0xC)
				//    | offset SEH_11CACC0  |
				//    | 0FFFFFFFFh          |
				//ebp | ebp
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x9A, true);
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
			push ecx;

			// 1文字目
			mov cl, byte ptr[eax + esi];
			mov byte ptr[ebp - 0xA0], cl;  // lpMem

			// 1文字目をみる
			cmp cl, ESCAPE_SEQ_1;
			jz geso1;
			cmp cl, ESCAPE_SEQ_2;
			jz geso1;
			cmp cl, ESCAPE_SEQ_3;
			jz geso1;
			cmp cl, ESCAPE_SEQ_4;
			jz geso1;
			jmp geso;

		geso1:
			mov cx, word ptr [eax + esi+1];
			mov word ptr[ebp - 0xA0 + 1], cx; // lpMem

		geso:
			pop ecx;

			push func1_v125_end;
			ret;
		}
	}

	uintptr_t func2_v125_end;
	__declspec(naked) void func2_v125_start()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz d_3;
			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz d_3;
			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz d_3;
			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz d_3;
			jmp d_4;

		d_3:
			mov ecx, [ebp - 0xA0];
			mov[eax], ecx;
			lea ecx, [eax];
			mov byte ptr[ecx + 0x10], 3;

		d_4:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push func2_v125_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func1_2_hook(EU4Version version) {
		std::string desc = "func1";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("8A 04 30 88 85 60 FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al, [eax+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func1_v125_start);
				// push [ebp+lpMem]
				func1_v125_end = byte_pattern::temp_instance().get_first().address(0x9);
				// push 0xFFFFFFFFh
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), func2_v125_start);
				// lea ecx, [ebp+var_B8]
				func2_v125_end = byte_pattern::temp_instance().get_first().address(0x19);
				return NOERROR;
			}
			else return EU4_ERROR1;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func3_v125_end;
	__declspec(naked) void func3_v125_start()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz e_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz e_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz e_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz e_13;
			jmp e_2;

		e_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp e_3;

		e_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp e_3;

		e_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp e_3;

		e_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			jmp e_3;

		e_2:
			mov al, [eax + esi];
			movzx eax, al;
			jmp e_4;

		e_3:
			movzx eax, ax;
			add esi, 2;
			cmp eax, NO_FONT;
			ja e_4;
			mov eax, NOT_DEF;

		e_4:
			mov word ptr[ebp - 0x564], ax;

			push func3_v125_end;
			ret;
		}
	}

	uintptr_t func3_v127_end;
	__declspec(naked) void func3_v127_start()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz e_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz e_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz e_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz e_13;
			jmp e_2;

		e_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp e_3;

		e_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp e_3;

		e_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp e_3;

		e_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			jmp e_3;

		e_2:
			mov al, [eax + esi];
			movzx eax, al;
			jmp e_4;

		e_3:
			movzx eax, ax;
			add esi, 2;
			cmp eax, NO_FONT;
			ja e_4;
			mov eax, NOT_DEF;

		e_4:
			mov word ptr[ebp - 0x5A6], ax;

			push func3_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func3_hook(EU4Version version) {
		std::string desc = "func3";

		switch (version) {
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("8A 04 30 0F B6 C0 8B 84");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al,[eax+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func3_v127_start);
				// mov eax, [edi+eax*4+0B4h]
				func3_v127_end = byte_pattern::temp_instance().get_first().address(0x6);
				return NOERROR;
			}
			else return EU4_ERROR1;
		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("8A 04 30 0F B6 C0 8B 84");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov al,[eax+esi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func3_v125_start);
				// mov eax, [edi+eax*4+0B4h]
				func3_v125_end = byte_pattern::temp_instance().get_first().address(0x6);
				return NOERROR;
			}
			else return EU4_ERROR1;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func4_v125_end2;
	uintptr_t func4_v125_end;
	__declspec(naked) void func4_v125_start()
	{
		__asm {
			cmp word ptr[eax + 6], 0;
			jz v_3_jmp;

			cmp word ptr[ebp - 0x564], 0xFF;
			ja v_3_jmp;

			push func4_v125_end2;
			ret;

		v_3_jmp:
			push func4_v125_end;
			ret;
		}
	}

	uintptr_t func4_v127_end2;
	uintptr_t func4_v127_end;
	__declspec(naked) void func4_v127_start()
	{
		__asm {
			cmp word ptr[eax + 6], 0;
			jz v_3_jmp;

			cmp word ptr[ebp - 0x5A6], 0xFF;
			ja v_3_jmp;

			push func4_v127_end2;
			ret;

		v_3_jmp:
			push func4_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func4_hook(EU4Version version) {
		std::string desc = "func4";

		switch (version) {
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("66 83 78 06 00 0F 85 17");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				// cmp word ptr [eax+6],0
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func4_v127_start);
				// cmp [ebp+var_34],0
				func4_v127_end = byte_pattern::temp_instance().get_first().address(0xB);
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("46 3B 75 DC 0F 8C DE F7");
			if (byte_pattern::temp_instance().has_size(1, " end2")) {
				// inc esi
				func4_v127_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("66 83 78 06 00 0F 85");
			if (byte_pattern::temp_instance().has_size(1,desc + " start")) {
				// cmp word ptr [eax+6],0
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func4_v125_start);
				// cmp [ebp+var_30],0
				func4_v125_end = byte_pattern::temp_instance().get_first().address(0xB);
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("46 3B 75 DC 0F 8C DD F7");
			if (byte_pattern::temp_instance().has_size(1, " end2")) {
				// inc esi
				func4_v125_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;

			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t func5_v125_end;
	__declspec(naked) void func5_v125_start()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz b_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz b_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz b_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz b_13;
			jmp b_3;

		b_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp b_1x;

		b_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp b_1x;

		b_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp b_1x;

		b_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;
			jmp b_1x;

		b_3:
			movzx eax, byte ptr[eax + edi];
			jmp b_4;

		b_1x:
			movzx eax, ax;
			add edi, 2;
			mov[ebp - 0x1C], edi;
			cmp eax, NO_FONT;
			ja b_4;
			mov eax, NOT_DEF;

		b_4:
			mov eax, [ecx + eax * 4];

			push func5_v125_end;
			ret;
		}
	}

	uintptr_t func5_v127_end;
	__declspec(naked) void func5_v127_start()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz b_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz b_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz b_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz b_13;
			jmp b_3;

		b_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp b_1x;

		b_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp b_1x;

		b_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp b_1x;

		b_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;
			jmp b_1x;

		b_3:
			movzx eax, byte ptr[eax + edi];
			jmp b_4;

		b_1x:
			movzx eax, ax;
			add edi, 2;
			mov[ebp - 0x10], edi;
			cmp eax, NO_FONT;
			ja b_4;
			mov eax, NOT_DEF;

		b_4:
			mov eax, [ecx + eax * 4];

			push func5_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t func5_hook(EU4Version version) {
		std::string desc = "func5";

		switch (version) {
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("0F B6 04 38 8B 04 81");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte ptr [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func5_v127_start);
				// mov [ebp+var_8C],eax
				func5_v127_end = byte_pattern::temp_instance().get_first().address(0x7);
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_25_X:
		case v1_26_X:
			byte_pattern::temp_instance().find_pattern("0F B6 04 38 8B 04 81");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax, byte ptr [eax+edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), func5_v125_start);
				// mov [ebp+var_8C],eax
				func5_v125_end = byte_pattern::temp_instance().get_first().address(0x7);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t stackSizeClear_hook(EU4Version version) {
		std::string desc = "stack size clear";

		switch (version) {
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			// lea esp,[ebp-5ACh] -> 5AE
			byte_pattern::temp_instance().find_pattern("8D A5 54 FA FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x52, true);
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_26_X:
		case v1_25_X:
			// lea esp,[ebp-56Ch] -> 56E
			byte_pattern::temp_instance().find_pattern("8D A5 94 FA FF FF");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x92, true);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}
	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("button and tooltip fix");

		/* スタックサイズ変更 */
		result |= stackSize_hook(version);
		/* */
		result |= func1_2_hook(version);
		/* */
		result |= func3_hook(version);
		/* */
		result |= func4_hook(version);
		/* */
		result |= func5_hook(version);
		/* スタック後始末 */
		result |= stackSizeClear_hook(version);

		return result;
	}
}