﻿#include "pch.h"
#include "plugin_64.h"

namespace MainText {
	extern "C" {
		void mainTextProc1();
		void mainTextProc1V137();
		void mainTextProc2();
		void mainTextProc2V131();
		void mainTextProc2V137();
		void mainTextProc3();
		void mainTextProc4();
		void mainTextProc4V137();
		uintptr_t mainTextProc1ReturnAddress;
		uintptr_t mainTextProc2ReturnAddress;
		uintptr_t mainTextProc2BufferAddress;
		uintptr_t mainTextProc3ReturnAddress1;
		uintptr_t mainTextProc3ReturnAddress2;
		uintptr_t mainTextProc4ReturnAddress;
	}

	DllError mainTextProc1Injector(RunOptions options) {
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
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// movsxd rax, edi
			BytePattern::temp_instance().find_pattern("48 63 C7 0F B6 04 18 F3 41 0F 10 9F 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ２の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// movss dword ptr [rpb+108h], xmm3
				mainTextProc1ReturnAddress = address + 0x1B;

				Injector::MakeJMP(address, mainTextProc1, true);
			}
			else {
				e.mainText.unmatchdMainTextProc1Injector = true;
			}
			break;
		case v1_37_0_0:
			// movzx   r8d, byte ptr [rcx+r9]
			BytePattern::temp_instance().find_pattern("46 0F B6 04 09");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ２の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// mov     [rbp+2340h+var_2308], rdx
				mainTextProc1ReturnAddress = address + 0x16;

				Injector::MakeJMP(address, mainTextProc1V137, true);
			}
			else {
				e.mainText.unmatchdMainTextProc1Injector = true;
			}
			break;
		default:
			e.mainText.versionMainTextProc1Injector = true;
		}

		return e;
	}

	DllError mainTextProc2Injector(RunOptions options) {
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
			// movsxd rdx, edi
			BytePattern::temp_instance().find_pattern("48 63 D7 49 63 CE 4C 8B 54 24 78");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１のカウント処理修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp byte ptr [rbp+7B0h],0
				mainTextProc2ReturnAddress = address + 0x1E;

				// lea r9, {unk_XXXXX}
				mainTextProc2BufferAddress = Injector::GetBranchDestination(address + 0x10).as_int();

				Injector::MakeJMP(address, mainTextProc2, true);
			}
			else {
				e.mainText.unmatchdMainTextProc2Injector = true;
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
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// movsxd rdx, edi
			BytePattern::temp_instance().find_pattern("48 63 D7 49 63 CE 4C 8B 55 80");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１のカウント処理修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp byte ptr [rbp+750h+arg_50],0
				mainTextProc2ReturnAddress = address + 0x1D;

				// lea r9, {unk_XXXXX}
				mainTextProc2BufferAddress = Injector::GetBranchDestination(address + 0x0F).as_int();

				Injector::MakeJMP(address, mainTextProc2V131, true);
			}
			else {
				e.mainText.unmatchdMainTextProc2Injector = true;
			}
			break;
		case v1_37_0_0:
			// movsxd  r9, edi
			BytePattern::temp_instance().find_pattern("4C 63 CF 48 8B 55 F8 4C 03 CA 48 63 CE");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１のカウント処理修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp byte ptr [rbp+750h+arg_50],0
				mainTextProc2ReturnAddress = address + 0x1E;

				// lea r11, {unk_XXXXX}
				mainTextProc2BufferAddress = Injector::GetBranchDestination(address + 0x11).as_int();

				Injector::MakeJMP(address, mainTextProc2V137, true);
			}
			else {
				e.mainText.unmatchdMainTextProc2Injector = true;
			}
			break;
		default:
			e.mainText.versionMainTextProc2Injector = true;
		}

		return e;
	}

	DllError mainTextProc3Injector(RunOptions options) {
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
			// cmp cs:byte_xxxxx, 0
			BytePattern::temp_instance().find_pattern("80 3D ? ? ? ? 00 0F 84 97 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理の戻り先２取得")) {
				mainTextProc3ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.mainText.unmatchdMainTextProc3Injector = true;
			}

			// cmp word ptr [rcx+6],0
			BytePattern::temp_instance().find_pattern("66 83 79 06 00 0F 85 15 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理を修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtdq2ps xmm1,xmm1
				mainTextProc3ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, mainTextProc3, true);
			}
			else {
				e.mainText.unmatchdMainTextProc3Injector = true;
			}
			break;
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
			// cmp cs:byte_xxxxx, 0
			BytePattern::temp_instance().find_pattern("80 3D ? ? ? ? 00 0F 84 97 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理の戻り先２取得")) {
				mainTextProc3ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.mainText.unmatchdMainTextProc3Injector = true;
			}

			// cmp word ptr [rcx+6],0
			BytePattern::temp_instance().find_pattern("66 83 79 06 00 0F 85 16 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理を修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtdq2ps xmm1,xmm1
				mainTextProc3ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, mainTextProc3, true);
			}
			else {
				e.mainText.unmatchdMainTextProc3Injector = true;
			}
			break;
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// cmp cs:byte_xxxxx, 0
			BytePattern::temp_instance().find_pattern("80 3D ? ? ? ? 00 0F 84 9A 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理の戻り先２取得")) {
				mainTextProc3ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.mainText.unmatchdMainTextProc3Injector = true;
			}

			// cmp word ptr [rcx+6],0
			BytePattern::temp_instance().find_pattern("66 83 79 06 00 0F 85 16 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理を修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtdq2ps xmm1,xmm1
				mainTextProc3ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, mainTextProc3, true);
			}
			else {
				e.mainText.unmatchdMainTextProc3Injector = true;
			}
			break;
		case v1_37_0_0:
			// cmp cs:byte_xxxxx, 0
			BytePattern::temp_instance().find_pattern("80 3D ? ? ? ? 00 0F 84 5F 01");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理の戻り先２取得")) {
				mainTextProc3ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.mainText.unmatchdMainTextProc3Injector = true;
			}

			// cmp word ptr [rcx+6],0
			BytePattern::temp_instance().find_pattern("66 83 79 06 00 0F 85");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の改行処理を修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtdq2ps xmm1,xmm1
				mainTextProc3ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, mainTextProc3, true);
			}
			else {
				e.mainText.unmatchdMainTextProc3Injector = true;
			}
			break;
		default:
			e.mainText.versionMainTextProc3Injector = true;
		}

		return e;
	}

	DllError mainTextProc4Injector(RunOptions options) {
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
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// movzx eax, byte ptr [rdx+r10]
			BytePattern::temp_instance().find_pattern("42 0F B6 04 12 49 8B 0C C7");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				mainTextProc4ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, mainTextProc4, true);
			}
			else {
				e.mainText.unmatchdMainTextProc4Injector = true;
			}
			break;
		case v1_37_0_0:
			// movzx   eax, byte ptr [r9]
			BytePattern::temp_instance().find_pattern("41 0F B6 01 49 8B 8C C6 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"テキスト処理ループ１の文字取得修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				mainTextProc4ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mainTextProc4V137, true);
			}
			else {
				e.mainText.unmatchdMainTextProc4Injector = true;
			}
			break;
		default:
			e.mainText.versionMainTextProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mainTextProc1Injector(options);
		result |= mainTextProc2Injector(options);
		result |= mainTextProc3Injector(options);
		result |= mainTextProc4Injector(options);

		return result;
	}
}