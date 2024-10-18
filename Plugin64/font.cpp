﻿#include "pch.h"
#include "plugin_64.h"

namespace Font {

	extern "C" {
		void fontBufferHeapZeroClear();
		uintptr_t fontBufferHeapZeroClearReturnAddress;
		uintptr_t fontBufferHeapZeroClearHeepAllocJmpAddress;
		uintptr_t fontBufferHeapZeroClearHeapJmpAddress;
	}

	DllError charCodePointLimiterPatchInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
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
			/* 1.33.0.0 betaで初めて確認された */
			break;

		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// cmp     edi, 0FFh
			// 81 FF FF 00 00 00
			BytePattern::temp_instance().find_pattern("81 FF FF 00 00 00 0F 87 2C 01 00 00 83");
			if (BytePattern::temp_instance().has_size(1, "Char Code Point Limiter")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				Injector::WriteMemory<BYTE>(address + 3, 0xFF,true);
			}
			else {
				e.font.unmatchdCharCodePointLimiterPatchInjector = true;
			}
			break;
		case v1_37_0_0:
			// cmp     edi, 0FFh
			// 81 FF FF 00 00 00
			BytePattern::temp_instance().find_pattern("81 FF FF 00 00 00 0F 87 6F 02 00 00 83");
			if (BytePattern::temp_instance().has_size(1, "Char Code Point Limiter")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				Injector::WriteMemory<BYTE>(address + 3, 0xFF, true);
			}
			else {
				e.font.unmatchdCharCodePointLimiterPatchInjector = true;
			}
			break;
		default:
			e.font.versionCharCodePointLimiterPatchInjector = true;
		}

		return e;
	}

	DllError fontBufferHeapZeroClearInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
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
			// mov rcx,cs:hHeap
			BytePattern::temp_instance().find_pattern("48 8B 0D ? ? ? ? 4C 8B C3 33 D2");
			if (BytePattern::temp_instance().has_size(1, "Font buffer heap zero clear")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				
				// mov rcx, {cs:hHeap}
				fontBufferHeapZeroClearHeapJmpAddress = Injector::GetBranchDestination(address + 0x0).as_int();
				// call {{cs:HeapAlloc}}
				fontBufferHeapZeroClearHeepAllocJmpAddress = Injector::GetBranchDestination(address + 0xC).as_int();
				// jz short loc_xxxxx
				fontBufferHeapZeroClearReturnAddress = address + 0x15;

				Injector::MakeJMP(address, fontBufferHeapZeroClear, true);
			} else {
				e.font.unmatchdFontBufferHeapZeroClearInjector = true;
			}
			break;
		case v1_37_0_0:
			// mov rcx,cs:hHeap
			BytePattern::temp_instance().find_pattern("48 8B 0D ? ? ? ? 4C 8B C3 33 D2");
			if (BytePattern::temp_instance().has_size(1, "Font buffer heap zero clear")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// mov rcx, {cs:hHeap}
				fontBufferHeapZeroClearHeapJmpAddress = Injector::GetBranchDestination(address + 0x0).as_int();
				// call {{cs:HeapAlloc}}
				fontBufferHeapZeroClearHeepAllocJmpAddress = Injector::GetBranchDestination(address + 0xC).as_int();
				// jz short loc_xxxxx
				fontBufferHeapZeroClearReturnAddress = address + 0x15;

				Injector::MakeJMP(address, fontBufferHeapZeroClear, true);
			}
			else {
				e.font.unmatchdFontBufferHeapZeroClearInjector = true;
			}
			break;
		default:
			e.font.unmatchdFontBufferHeapZeroClearInjector = true;
		}

		return e;
	}

	DllError fontBufferClear1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
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
			BytePattern::temp_instance().find_pattern("BA 88 3D 00 00 48 8B CF");
			if (BytePattern::temp_instance().has_size(1, "Font buffer clear")) {
				// mov edx, 3D88h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.font.unmatchdFontBufferClear1Injector = true;
			}
			break;
		case v1_37_0_0:
			BytePattern::temp_instance().find_pattern("BA 88 3D 00 00 48 8B 4D");
			if (BytePattern::temp_instance().has_size(1, "Font buffer clear")) {
				// mov edx, 3D88h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.font.unmatchdFontBufferClear1Injector = true;
			}
			break;
		default:
			e.font.versionFontBufferClear1Injector = true;
		}

		return e;
	}

	DllError fontBufferClear2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
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
			BytePattern::temp_instance().find_pattern("BA 88 3D 00 00 48 8B 4D 28");
			if (BytePattern::temp_instance().has_size(1, "Font buffer clear")) {
				// mov edx, 3D88h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.font.unmatchdFontBufferClear2Injector = true;
			}
			break;
		case v1_37_0_0:
			BytePattern::temp_instance().find_pattern("BA 88 3D 00 00 48 8B CB E8");
			if (BytePattern::temp_instance().has_size(1, "Font buffer clear")) {
				// mov edx, 3D88h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.font.unmatchdFontBufferClear2Injector = true;
			}
			break;
		default:
			e.font.versionFontBufferClear2Injector = true;
		}

		return e;
	}

	DllError fontBufferExpansionInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
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
		case v1_37_0_0:
			BytePattern::temp_instance().find_pattern("B9 88 3D 00 00");
			if (BytePattern::temp_instance().has_size(1, "Font buffer expansion")) {
				// mov ecx, 3D88h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			} else {
				e.font.unmatchdFontBufferExpansionInjector = true;
			}
			break;
		default:
			e.font.versionFontBufferExpansionInjector = true;
		}
		
		return e;
	}

	DllError fontSizeLimitInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
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
		case v1_37_0_0:
			BytePattern::temp_instance().find_pattern("41 81 FE 00 00 00 01");
			if (BytePattern::temp_instance().has_size(1, u8"Font size limit")) {
				// cmp r14d, 1000000h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x6), 0x04, true);
			} else {
				e.font.unmatchdFontSizeLimitInjector = true;
			}
			break;
		default:
			e.font.versionFontSizeLimitInjector = true;
		}

		return e;
	}

	/*-----------------------------------------------*/

	DllError Init(RunOptions options) {
		DllError result = {};

		BytePattern::LoggingInfo(u8"font etc fix");

		/* codePointが0xFFまでしか入らないようにしている箇所にパッチを当てる*/
		result |= charCodePointLimiterPatchInjector(options);

		/* ヒープゼロフラグの修正 */
		result |= fontBufferHeapZeroClearInjector(options);

		/* フォントバッファクリア1 */
		result |= fontBufferClear1Injector(options);

		/* フォントバッファクリア2 */
		result |= fontBufferClear2Injector(options);

		/* フォントバッファ拡張 */
		result |= fontBufferExpansionInjector(options);

		/* フォントサイズの拡張 */
		result |= fontSizeLimitInjector(options);

		return result;
	}
}