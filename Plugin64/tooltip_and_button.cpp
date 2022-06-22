#include "pch.h"
#include "plugin_64.h"

namespace TooltipAndButton {
	extern "C" {
		void tooltipAndButtonProc1();
		void tooltipAndButtonProc1V133();
		void tooltipAndButtonProc2();
		void tooltipAndButtonProc2V133();
		void tooltipAndButtonProc3();
		void tooltipAndButtonProc4();
		void tooltipAndButtonProc4V133();
		void tooltipAndButtonProc5();
		void tooltipAndButtonProc5V130();
		void tooltipAndButtonProc7();
		void tooltipAndButtonProc7V133();
		void tooltipAndButtonProc8();
		void tooltipAndButtonProc9();
		void tooltipAndButtonProc10();

		uintptr_t tooltipAndButtonProc1ReturnAddress;
		uintptr_t tooltipAndButtonProc1CallAddress;
		uintptr_t tooltipAndButtonProc2ReturnAddress;
		uintptr_t tooltipAndButtonProc3ReturnAddress;
		uintptr_t tooltipAndButtonProc4ReturnAddress1;
		uintptr_t tooltipAndButtonProc4ReturnAddress2;
		uintptr_t tooltipAndButtonProc5ReturnAddress1;
		uintptr_t tooltipAndButtonProc5ReturnAddress2;
		uintptr_t tooltipAndButtonProc7ReturnAddress1;
		uintptr_t tooltipAndButtonProc7ReturnAddress2;
		uintptr_t tooltipAndButtonProc8ReturnAddress1;
		uintptr_t tooltipAndButtonProc9ReturnAddress1;
		uintptr_t tooltipAndButtonProc9ReturnAddress2;
		uintptr_t tooltipAndButtonProc10ReturnAddress1;
		uintptr_t tooltipAndButtonProc10ReturnAddress2;
	}

	DllError tooltipAndButtonProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_33_3_0:
			// r8d, byte ptr [rax + rcx]
			BytePattern::temp_instance().find_pattern("44 0F B6 04 08 BA 01 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				tooltipAndButtonProc1CallAddress = Injector::GetBranchDestination(address + 0x0F).as_int();

				// nop
				tooltipAndButtonProc1ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, tooltipAndButtonProc1V133, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc1Injector = true;
			}
			break;
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
			// r8d, byte ptr [rax + rcx]
			BytePattern::temp_instance().find_pattern("44 0F B6 04 08 BA 01 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				tooltipAndButtonProc1CallAddress = Injector::GetBranchDestination(address + 0x0E).as_int();
				
				// nop
				tooltipAndButtonProc1ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, tooltipAndButtonProc1, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc1Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc1Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_33_3_0:
			// mov edx, ebx
			BytePattern::temp_instance().find_pattern("8B D3 0F B6 04 10 49 8B 0C C7");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test rcx,rcx
				tooltipAndButtonProc2ReturnAddress = address + 0xE;

				Injector::MakeJMP(address, tooltipAndButtonProc2V133, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc2Injector = true;
			}
			break;
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
			// mov edx, ebx
			BytePattern::temp_instance().find_pattern("8B D3 0F B6 04 10 49 8B 0C C7");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test rcx,rcx
				tooltipAndButtonProc2ReturnAddress = address + 0x11;

				Injector::MakeJMP(address, tooltipAndButtonProc2, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc2Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc2Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			// mov ecx, ebx
			BytePattern::temp_instance().find_pattern("8B CB F3 45 0F 10 97 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ２の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test r11, r11
				tooltipAndButtonProc3ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, tooltipAndButtonProc3, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc3Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc3Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
			// cmp word ptr [rcx + 6], 0
			BytePattern::temp_instance().find_pattern("66 83 79 06 00 0F 85 05 03 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz {loc_xxxxx} / inc ebx
				tooltipAndButtonProc4ReturnAddress1 = Injector::GetBranchDestination(address + 0x5).as_int();

				// jz loc_xxxxx
				tooltipAndButtonProc4ReturnAddress2 = address + 15;

				Injector::MakeJMP(address, tooltipAndButtonProc4, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc4Injector = true;
			}
			break;
		case v1_33_0_0:
		case v1_32_0_1:
			// cmp word ptr [rcx + 6], 0
			BytePattern::temp_instance().find_pattern("66 83 79 06 00 0F 85 11 03 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz {loc_xxxxx} / inc ebx
				tooltipAndButtonProc4ReturnAddress1 = Injector::GetBranchDestination(address + 0x5).as_int();

				// jz loc_xxxxx
				tooltipAndButtonProc4ReturnAddress2 = address + 15;

				Injector::MakeJMP(address, tooltipAndButtonProc4, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc4Injector = true;
			}
			break;
		case v1_33_3_0:
			// cmp word ptr [rcx + 6], 0
			BytePattern::temp_instance().find_pattern("66 83 79 06 00 0F 85 03 03 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jnz {loc_xxxxx} / inc ebx
				tooltipAndButtonProc4ReturnAddress1 = Injector::GetBranchDestination(address + 0x5).as_int();

				// jz loc_xxxxx
				tooltipAndButtonProc4ReturnAddress2 = address + 15;

				Injector::MakeJMP(address, tooltipAndButtonProc4V133, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc4Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc4Injector = true;
		}

		return e;
	}

	// これはwin32のときはToolTipApxにあったが統合した。proc1～4とは別のprocにinjectしている
	DllError tooltipAndButtonProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			// movaps  xmm7, [rsp+0E8h+var_48]
			BytePattern::temp_instance().find_pattern("0F 28 BC 24 A0 00 00 00 48 8B B4 24 00 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ツールチップの改行処理のリターン先２")) {
				tooltipAndButtonProc5ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc5Injector = true;
			}

			// movzx   edx, byte ptr [rbx+r14]
			BytePattern::temp_instance().find_pattern("42 0F B6 14 33 49 8D 8C 24 00 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ツールチップの改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz short loc_xxxxx
				tooltipAndButtonProc5ReturnAddress1 = address + 0x14;

				Injector::MakeJMP(address, tooltipAndButtonProc5, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc5Injector = true;
			}
			break;
		case v1_30_5_0:
		case v1_30_4_0:
		case v1_30_3_0:
		case v1_30_2_0:
		case v1_30_1_0:
			// movaps  xmm7, [rsp+0E8h+var_48]
			BytePattern::temp_instance().find_pattern("0F 28 BC 24 A0 00 00 00 48 8B B4 24 00 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ツールチップの改行処理のリターン先２")) {
				tooltipAndButtonProc5ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc5Injector = true;
			}

			// movzx   edx, byte ptr [rbx+r14]
			BytePattern::temp_instance().find_pattern("42 0F B6 14 33 49 8D 8C 24 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ツールチップの改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz short loc_xxxxx
				tooltipAndButtonProc5ReturnAddress1 = address + 0x14;

				Injector::MakeJMP(address, tooltipAndButtonProc5V130, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc5Injector = true;
			}
			break;
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			// movaps  xmm8, [rsp+0F8h+var_58]
			BytePattern::temp_instance().find_pattern("44 0F 28 84 24 A0 00 00 00 0F 28 BC 24 B0 00 00 00 48");
			if (BytePattern::temp_instance().has_size(1, u8"ツールチップの改行処理のリターン先２")) {
				tooltipAndButtonProc5ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc5Injector = true;
			}

			// movzx   edx, byte ptr [rbx+r14]
			BytePattern::temp_instance().find_pattern("42 0F B6 14 33 49 8D 8C 24 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ツールチップの改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz short loc_xxxxx
				tooltipAndButtonProc5ReturnAddress1 = address + 0x14;

				Injector::MakeJMP(address, tooltipAndButtonProc5V130, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc5Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc5Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc6Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_33_3_0:
		case v1_33_0_0:
		case v1_32_0_1:
		case v1_31_6_0:
		case v1_31_5_0:
			// inc edx
			BytePattern::temp_instance().find_pattern("A7 52 2D 20 00 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"空白をノーブレークスペースに変換")) {
				Injector::WriteMemory(BytePattern::temp_instance().get_first().address() + 3, 0xA0, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc6Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc6Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc7Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_33_3_0:
			// inc ebx
			BytePattern::temp_instance().find_pattern("FF C3 3B 5D A8 7D 1D E9 79 F7 FF FF E8");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jmp loc_xxxxx
				tooltipAndButtonProc7ReturnAddress1 = Injector::GetBranchDestination(address + 0x7).as_int();

				// mov	edi, dword ptr [rsp+22D0h+var_2290]
				tooltipAndButtonProc7ReturnAddress2 = address + 0x24;

				Injector::MakeJMP(address, tooltipAndButtonProc7V133, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc7Injector = true;
			}
			break;
		case v1_33_0_0:
		case v1_32_0_1:
			// inc ebx
			BytePattern::temp_instance().find_pattern("FF C3 3B 5D 60 7D 1D E9 7D F7 FF FF E8");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jmp loc_xxxxx
				tooltipAndButtonProc7ReturnAddress1 = Injector::GetBranchDestination(address + 0x7).as_int();

				// mov	edi, dword ptr [rbp+6E0h+38h]
				tooltipAndButtonProc7ReturnAddress2 = address + 0x24;

				Injector::MakeJMP(address, tooltipAndButtonProc7, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc7Injector = true;
			}
			break;
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
			// inc edx
			BytePattern::temp_instance().find_pattern("FF C3 3B 5D 60 7D 1D E9 89 F7 FF FF E8");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				tooltipAndButtonProc7ReturnAddress1 = Injector::GetBranchDestination(address + 0x7).as_int();
				tooltipAndButtonProc7ReturnAddress2 = address + 0x24;

				Injector::MakeJMP(address, tooltipAndButtonProc7, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc7Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc7Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc8Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_33_3_0:
			// mov     eax, [rbp+22A0h+var_2294]
			BytePattern::temp_instance().find_pattern("8B 44 24 4C 0F 57 C0 F3 48 0F 2A C0 0F 2F C8");
			if (BytePattern::temp_instance().has_size(2, u8"改行処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jg loc_xxxxx
				tooltipAndButtonProc8ReturnAddress1 = Injector::GetBranchDestination(address + 0xF).as_int();

				Injector::MakeJMP(address, tooltipAndButtonProc8, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc8Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc8Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc9Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_33_3_0:
			// 
			BytePattern::temp_instance().find_pattern("48 8D 44 24 50 48 83 FF 10 48 0F 43 C6 80 3C 10 0A");
			if (BytePattern::temp_instance().has_size(1, u8"文字がないときの改行処理？")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				tooltipAndButtonProc9ReturnAddress1 = address + 0x2A;
				tooltipAndButtonProc9ReturnAddress2 = Injector::GetBranchDestination(address + 0x24).as_int();


				Injector::MakeJMP(address, tooltipAndButtonProc9, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc9Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc9Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc10Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_33_3_0:
			// 
			BytePattern::temp_instance().find_pattern("0F 28 B4 24 C0 00 00 00 48 81 C4 F0 00 00 00 41");
			if (BytePattern::temp_instance().has_size(1, u8"DEBUG")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// retn
				tooltipAndButtonProc10ReturnAddress1 = address + 0x11;

				Injector::MakeJMP(address, tooltipAndButtonProc10, true);
			}
			else {
				e.tooltipAndButton.unmatchdTooltipAndButtonProc9Injector = true;
			}
			break;
		default:
			e.tooltipAndButton.versionTooltipAndButtonProc9Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= tooltipAndButtonProc1Injector(options);
		result |= tooltipAndButtonProc2Injector(options);
		result |= tooltipAndButtonProc3Injector(options);
		result |= tooltipAndButtonProc4Injector(options);
		result |= tooltipAndButtonProc5Injector(options);
		result |= tooltipAndButtonProc6Injector(options);
		result |= tooltipAndButtonProc7Injector(options);
		//result |= tooltipAndButtonProc8Injector(options);
		//result |= tooltipAndButtonProc9Injector(options);
		//result |= tooltipAndButtonProc10Injector(options);

		return result;
	}
}