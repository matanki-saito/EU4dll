#include "pch.h"
#include "plugin_64.h"

namespace MapJustify {
	extern "C" {
		void mapJustifyProc1();
		void mapJustifyProc1V137();
		void mapJustifyProc2();
		void mapJustifyProc2V137();
		void mapJustifyProc4();
		void mapJustifyProc4V137();
		uintptr_t mapJustifyProc1ReturnAddress1;
		uintptr_t mapJustifyProc1ReturnAddress2;
		uintptr_t mapJustifyProc2ReturnAddress;
		uintptr_t mapJustifyProc4ReturnAddress;
	}

	DllError mapJustifyProc1Injector(RunOptions options) {
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
			// movsd   xmm3, [rbp+1D0h+var_168]
			BytePattern::temp_instance().find_pattern("F2 0F 10 5D 68 FF C2 F2 0F 10 65 20");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理リターン先２")) {
				mapJustifyProc1ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.mapJustify.unmatchdMapJustifyProc1Injector = true;
			}

			// movzx   esi, byte ptr [rax+r13]
			BytePattern::temp_instance().find_pattern("42 0F B6 34 28 F3 44 0F 10 89 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp     word ptr [rdi+6], 0
				mapJustifyProc1ReturnAddress1 = address + 0x1B;

				Injector::MakeJMP(address, mapJustifyProc1, true);
			}
			else {
				e.mapJustify.unmatchdMapJustifyProc1Injector = true;
			}
			break;
		case v1_37_0_0:
			// movzx   eax, byte ptr [rcx+rax]
			BytePattern::temp_instance().find_pattern("0F B6 04 01 88 85 08 08 00 00 F3 44 0F 10 A2 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				mapJustifyProc1ReturnAddress1 = address + 0x1A;

				Injector::MakeJMP(address, mapJustifyProc1V137, true);
			}
			else {
				e.mapJustify.unmatchdMapJustifyProc1Injector = true;
			}
			break;
		default:
			e.mapJustify.versionMapJustifyProc1Injector = true;
		}

		return e;
	}

	DllError mapJustifyProc2Injector(RunOptions options) {
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
			// lea     eax, [r10-1]
			BytePattern::temp_instance().find_pattern("41 8D 42 FF 66 0F 6E F2 66 0F 6E C0");
			if (BytePattern::temp_instance().has_size(1, u8"一文字表示の調整")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtdq2ps xmm6, xmm6
				mapJustifyProc2ReturnAddress = address + 0xF;

				Injector::MakeJMP(address, mapJustifyProc2, true);
			}
			else {
				e.mapJustify.unmatchdMapJustifyProc2Injector = true;
			}
			break;
		case v1_37_0_0:
			// movd    xmm6, esi
			BytePattern::temp_instance().find_pattern("66 0F 6E F6 0F 5B F6 48 8B 85 68 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"一文字表示の調整")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cvtdq2ps xmm1, xmm1
				mapJustifyProc2ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, mapJustifyProc2V137, true);
			}
			else {
				e.mapJustify.unmatchdMapJustifyProc2Injector = true;
			}
			break;
		default:
			e.mapJustify.versionMapJustifyProc2Injector = true;
		}

		return e;
	}

	DllError mapJustifyProc4Injector(RunOptions options) {
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
			// movsd   xmm3, [rbp+1D0h+var_168]
			BytePattern::temp_instance().find_pattern("F2 0F 10 5D 68 FF C2 F2 0F 10 65 20");
			if (BytePattern::temp_instance().has_size(1, u8"カウント処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp     r13, rax
				mapJustifyProc4ReturnAddress = address + 0x1E;

				Injector::MakeJMP(address, mapJustifyProc4, true);
			}
			else {
				e.mapJustify.unmatchdMapJustifyProc4Injector = true;
			}
			break;
		case v1_37_0_0:
			// inc     esi
			BytePattern::temp_instance().find_pattern("FF C6 89 B5 E8 07 00 00 48 FF C1");
			if (BytePattern::temp_instance().has_size(1, u8"カウント処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp     rcx, [rbp+7B0h+var_650]
				mapJustifyProc4ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, mapJustifyProc4V137, true);
			}
			else {
				e.mapJustify.unmatchdMapJustifyProc4Injector = true;
			}
			break;
		default:
			e.mapJustify.versionMapJustifyProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapJustifyProc1Injector(options);
		//result |= mapJustifyProc2Injector(options);
		result |= mapJustifyProc4Injector(options);

		return result;
	}
}