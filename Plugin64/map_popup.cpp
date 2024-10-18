﻿#include "pch.h"
#include "plugin_64.h"

namespace MapPopup {
	extern "C" {
		void mapPopupProc1();
		void mapPopupProc1V137();
		void mapPopupProc2();
		void mapPopupProc2V130();
		void mapPopupProc2V137();
		void mapPopupProc3();
		void mapPopupProc3V130();
		void mapPopupProc3V137();
		uintptr_t mapPopupProc1ReturnAddress;
		uintptr_t mapPopupProc1CallAddress;
		uintptr_t mapPopupProc1CallAddressA;
		uintptr_t mapPopupProc1CallAddressB;
		uintptr_t mapPopupProc2ReturnAddress;
		uintptr_t mapPopupProc3ReturnAddress;
	}

	DllError mapPopupProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
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
			// movzx   r8d, byte ptr [rdi+rax]
			BytePattern::temp_instance().find_pattern("44 0F B6 04 07 BA 01 00 00 00 48 8D 4D D0");
			if (BytePattern::temp_instance().has_size(1, u8"ループ１の文字列コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				mapPopupProc1CallAddress = Injector::GetBranchDestination(address + 14).as_int();

				Injector::MakeJMP(address, mapPopupProc1, true);

				// nop
				mapPopupProc1ReturnAddress = address + 19;
			}
			else {
				e.mapPopup.unmatchdMapPopupProc1Injector = true;
			}
			break;
		case v1_37_0_0:
			// lea     rcx, [rbp+370h+var_320]
			BytePattern::temp_instance().find_pattern("48 8D 4D 50 E8 ? ? ? ? 90 44 0F B6 C3 BA 01 00 00 00 48 8D 4D 50");
			if (BytePattern::temp_instance().has_size(3, u8"ループ１の文字列コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				
				// call xxxx
				mapPopupProc1CallAddressA = Injector::GetBranchDestination(address + 0x4).as_int();

				// call xxxx
				mapPopupProc1CallAddressB = Injector::GetBranchDestination(address + 0x17).as_int();

				Injector::MakeJMP(address, mapPopupProc1V137, true);

				// nop
				mapPopupProc1ReturnAddress = address + 0x1C;
			}
			else {
				e.mapPopup.unmatchdMapPopupProc1Injector = true;
			}
			break;
		default:
			e.mapPopup.versionMapPopupProc1Injector = true;
		}

		return e;
	}

	DllError mapPopupProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			//  movzx   eax, byte ptr [rax+rdi]
			BytePattern::temp_instance().find_pattern("0F B6 04 38 4D 8B B4 C7 00 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ１の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::MakeJMP(address, mapPopupProc2, true);

				// jz xxxxx
				mapPopupProc2ReturnAddress = address + 15;
			}
			else {
				e.mapPopup.unmatchdMapPopupProc2Injector = true;
			}
			break;
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
			//  movzx   eax, byte ptr [rax+rdi]
			BytePattern::temp_instance().find_pattern("0F B6 04 38 4D 8B B4 C7 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ１の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::MakeJMP(address, mapPopupProc2V130, true);

				// jz xxxxx
				mapPopupProc2ReturnAddress = address + 15;
			}
			else {
				e.mapPopup.unmatchdMapPopupProc2Injector = true;
			}
			break;
		case v1_37_0_0:
			//  
			BytePattern::temp_instance().find_pattern("0F B6 04 07 4D 8B A4 C7 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ１の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::MakeJMP(address, mapPopupProc2V137, true);

				// jz xxxxx
				mapPopupProc2ReturnAddress = address + 0xF;
			}
			else {
				e.mapPopup.unmatchdMapPopupProc2Injector = true;
			}
			break;
		default:
			e.mapPopup.versionMapPopupProc2Injector = true;
		}

		return e;
	}

	DllError mapPopupProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			//  movzx   eax, byte ptr [rbx+rax]
			BytePattern::temp_instance().find_pattern("0F B6 04 03 4D 8B 9C C7 00 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ２の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::MakeJMP(address, mapPopupProc3, true);

				//  movss   dword ptr [rbp+88h], xmm3
				mapPopupProc3ReturnAddress = address + 0x13;
			}
			else {
				e.mapPopup.unmatchdMapPopupProc3Injector = true;
			}
			break;
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
			//  movzx   eax, byte ptr [rbx+rax]
			BytePattern::temp_instance().find_pattern("0F B6 04 03 4D 8B 9C C7 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ２の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::MakeJMP(address, mapPopupProc3V130, true);

				//  movss   dword ptr [rbp+88h], xmm3
				mapPopupProc3ReturnAddress = address + 0x13;
			}
			else {
				e.mapPopup.unmatchdMapPopupProc3Injector = true;
			}
			break;
		case v1_37_0_0:
			// movzx   eax, byte ptr [rsi+rax]
			BytePattern::temp_instance().find_pattern("0F B6 04 06 4D 8B AC C7 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"ループ２の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::MakeJMP(address, mapPopupProc3V137, true);

				// jnz	xxxxx
				mapPopupProc3ReturnAddress = address + 0xF;
			}
			else {
				e.mapPopup.unmatchdMapPopupProc3Injector = true;
			}
			break;
		default:
			e.mapPopup.versionMapPopupProc3Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapPopupProc1Injector(options);
		result |= mapPopupProc2Injector(options);
		result |= mapPopupProc3Injector(options);

		return result;
	}
}