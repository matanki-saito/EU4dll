#include "pch.h"
#include "plugin_64.h"
#include "escape_tool.h"

namespace MapAdjustment {
	extern "C" {
		void mapAdjustmentProc1();
		void mapAdjustmentProc2();
		void mapAdjustmentProc2V130();
		void mapAdjustmentProc3();
		void mapAdjustmentProc3V130();
		void mapAdjustmentProc4();
		void mapAdjustmentProc4V130();
		void mapAdjustmentProc5();
		uintptr_t mapAdjustmentProc1ReturnAddress;
		uintptr_t mapAdjustmentProc1CallAddress;
		uintptr_t mapAdjustmentProc2ReturnAddress;
		uintptr_t mapAdjustmentProc3ReturnAddress1;
		uintptr_t mapAdjustmentProc3ReturnAddress2;
		uintptr_t mapAdjustmentProc4ReturnAddress;
		uintptr_t mapAdjustmentProc5ReturnAddress;
		uintptr_t mapAdjustmentProc5SeparatorAddress;
	}

	// これはwin32のときはmiscにあったが統合した。
	// この処理はwin32のときは独立したprocであったが、win64ではinline展開されている。
	DllError mapAdjustmentProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			// movsx ecx, byte ptr [rdi + rbx]
			BytePattern::temp_instance().find_pattern("0F BE 0C 1F E8 ? ? ? ? 88 04 1F 41 FF");
			if (BytePattern::temp_instance().has_size(1, u8"マップ文字の大文字化キャンセル")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				mapAdjustmentProc1CallAddress = Injector::GetBranchDestination(address + 0x04).as_int();

				// cmp byte ptr [rdi + r14] , 0
				mapAdjustmentProc1ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, mapAdjustmentProc1, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc1Injector = true;
			}
			break;
		case v1_30_5_0:
		case v1_30_4_0:
		case v1_30_3_0:
		case v1_30_2_0:
		case v1_30_1_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			// movsx ecx, byte ptr [rdi + rbx]
			BytePattern::temp_instance().find_pattern("0F BE 0C 1F E8 ? ? ? ? 88 04 1F 41 FF");
			if (BytePattern::temp_instance().has_size(2, u8"マップ文字の大文字化キャンセル")) {
				uintptr_t address = BytePattern::temp_instance().get_second().address();

				// call {sub_xxxxx}
				mapAdjustmentProc1CallAddress = Injector::GetBranchDestination(address + 0x04).as_int();

				// cmp byte ptr [rdi + r14] , 0
				mapAdjustmentProc1ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, mapAdjustmentProc1, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc1Injector = true;
			}
			break;
		default:
			e.mapAdjustment.versionMapAdjustmentProc1Injector = true;
		}

		return e;
	}

	DllError mapAdjustmentProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			// lea     rax, [rbp+1F0h+var_1F0]
			BytePattern::temp_instance().find_pattern("48 8D 45 00 49 83 C8 FF 90 49 FF C0");
			if (BytePattern::temp_instance().has_size(2, u8"文字チェック修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// lea     rdx, [rbp+1F0h+var_1F0]
				mapAdjustmentProc2ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mapAdjustmentProc2, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc2Injector = true;
			}
			break;
		case v1_30_5_0:
		case v1_30_4_0:
		case v1_30_3_0:
		case v1_30_2_0:
		case v1_30_1_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
			// lea     rax, [rbp+200h+var_200]
			BytePattern::temp_instance().find_pattern("48 8D 45 00 49 83 C8 FF 90 49 FF C0");
			if (BytePattern::temp_instance().has_size(1, u8"文字チェック修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// lea     rdx, [rbp+200h+var_200]
				mapAdjustmentProc2ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mapAdjustmentProc2V130, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc2Injector = true;
			}
			break;
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			// lea     rax, [rbp+200h+var_200]
			BytePattern::temp_instance().find_pattern("48 8D 45 00 49 83 C8 FF 90 49 FF C0");
			if (BytePattern::temp_instance().has_size(1, u8"文字チェック修正") ||
				BytePattern::temp_instance().has_size(2, u8"文字チェック修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// lea     rdx, [rbp+200h+var_200]
				mapAdjustmentProc2ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mapAdjustmentProc2V130, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc2Injector = true;
			}
			break;
		default:
			e.mapAdjustment.versionMapAdjustmentProc2Injector = true;
		}

		return e;
	}

	DllError mapAdjustmentProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			// r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8D 95 C0 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"文字チェックの後のコピー処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call    sub_xxxxx
				mapAdjustmentProc3ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, mapAdjustmentProc3, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc3Injector = true;
			}

			// mov     rcx, [r12+30h]
			BytePattern::temp_instance().find_pattern("49 8B 4C 24 30 48 8B 01 C6 44 24 30 01");
			if (BytePattern::temp_instance().has_size(2, u8"文字チェックの後のコピー処理の戻り先２")) {
				mapAdjustmentProc3ReturnAddress2 = BytePattern::temp_instance().get_second().address();
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc3Injector = true;
			}
			break;
		case v1_30_5_0:
		case v1_30_4_0:
		case v1_30_3_0:
		case v1_30_2_0:
		case v1_30_1_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			// r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8D 95 D0 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"文字チェックの後のコピー処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call    sub_xxxxx
				mapAdjustmentProc3ReturnAddress1 = address + 0x12;

				Injector::MakeJMP(address, mapAdjustmentProc3V130, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc3Injector = true;
			}

			// mov     rcx, [r12+30h]
			BytePattern::temp_instance().find_pattern("49 8B 4C 24 30 48 8B 01 C6 44 24 30 01");
			if (BytePattern::temp_instance().has_size(2, u8"文字チェックの後のコピー処理の戻り先２")) {
				mapAdjustmentProc3ReturnAddress2 = BytePattern::temp_instance().get_second().address();
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc3Injector = true;
			}
			break;
		default:
			e.mapAdjustment.versionMapAdjustmentProc3Injector = true;
		}

		return e;
	}

	DllError mapAdjustmentProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			//  lea     rax, [rbp+1F0h+var_160]
			BytePattern::temp_instance().find_pattern("48 8D 85 90 00 00 00 49 83 F8 10");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// mov     rdx, [r15+rax*8]
				mapAdjustmentProc4ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mapAdjustmentProc4, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc4Injector = true;
			}
			break;
		case v1_30_5_0:
		case v1_30_4_0:
		case v1_30_3_0:
		case v1_30_2_0:
		case v1_30_1_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			//  lea     rax, [rbp+200h+var_160]
			BytePattern::temp_instance().find_pattern("48 8D 85 A0 00 00 00 49 83 F8 10");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// mov     rdx, [r15+rax*8]
				mapAdjustmentProc4ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, mapAdjustmentProc4V130, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc4Injector = true;
			}
			break;
		default:
			e.mapAdjustment.versionMapAdjustmentProc4Injector = true;
		}

		return e;
	}

	char* mapAdjustmentProc5InjectorSeparateBuffer;

	DllError mapAdjustmentProc5Injector(RunOptions options) {
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
			// lea r8, asc_xxxxx
			BytePattern::temp_instance().find_pattern("4C 8D 05 ? ? ? ? 48 8D 55 78 48 8D 8D 40 01");
			if (BytePattern::temp_instance().has_size(1, u8"区切り記号の変更（ISSUE-164）")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				wchar_t x[2] = { 0 };
				x[0] = options.separateCharacterCodePoint;
				x[1] = 0;
				char* escapedChar = NULL;
				convertWideTextToEscapedText(x, &escapedChar);
				size_t len = strlen(escapedChar);
				size_t lenWithNull = len + 1;
				mapAdjustmentProc5InjectorSeparateBuffer = new char[lenWithNull]();
				memcpy(mapAdjustmentProc5InjectorSeparateBuffer, escapedChar, len);

				mapAdjustmentProc5SeparatorAddress = (uintptr_t)mapAdjustmentProc5InjectorSeparateBuffer;

				// call sub_xxxxx
				mapAdjustmentProc5ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, mapAdjustmentProc5, true);
			}
			else {
				e.mapAdjustment.unmatchdMapAdjustmentProc5Injector = true;
			}
			break;
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			// localization/tmm_l_english.ymlのENCLAVE_NAME_FORMATで対応された
			break;

		default:
			e.mapAdjustment.versionMapAdjustmentProc5Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapAdjustmentProc1Injector(options);
		result |= mapAdjustmentProc2Injector(options);
		result |= mapAdjustmentProc3Injector(options);
		result |= mapAdjustmentProc4Injector(options);
		result |= mapAdjustmentProc5Injector(options);

		return result;
	}
}