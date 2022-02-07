#include "pch.h"
#include "plugin_64.h"

namespace MapView {
	extern "C" {
		void mapViewProc1();
		void mapViewProc2();
		void mapViewProc2V130();
		void mapViewProc3();
		uintptr_t mapViewProc1ReturnAddress;
		uintptr_t mapViewProc2ReturnAddress;
		uintptr_t mapViewProc3ReturnAddress;
		uintptr_t mapViewProc3CallAddress;
	}

	DllError mapViewProc1Injector(RunOptions options) {
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
			// movzx   eax, byte ptr [rax+r8]
			BytePattern::temp_instance().find_pattern("42 0F B6 04 00 4C 8B 1C C7 4C 89 5D 38");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ２の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test    r11, r11
				mapViewProc1ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, mapViewProc1, true);
			}
			else {
				e.unmatch.mapViewProc1Injector = true;
			}
			break;
		default:
			e.version.mapViewProc1Injector = true;
		}

		return e;
	}

	DllError mapViewProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			// lea     r9, [r12+100h]
			BytePattern::temp_instance().find_pattern("4D 8D 8C 24 00 01 00 00 42 0F B6 04 38 4D 8B 24 C1");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test    r12, r12
				mapViewProc2ReturnAddress = address + 0x11;

				Injector::MakeJMP(address, mapViewProc2, true);
			}
			else {
				e.unmatch.mapViewProc2Injector = true;
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
			// lea     r9, [r12+120h]
			BytePattern::temp_instance().find_pattern("4D 8D 8C 24 20 01 00 00 42 0F B6 04 38 4D 8B 24 C1");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test    r12, r12
				mapViewProc2ReturnAddress = address + 0x11;

				Injector::MakeJMP(address, mapViewProc2V130, true);
			}
			else {
				e.unmatch.mapViewProc2Injector = true;
			}
			break;
		default:
			e.version.mapViewProc2Injector = true;
		}

		return e;
	}

	DllError mapViewProc3Injector(RunOptions options) {
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
			// movzx   r8d, byte ptr [rax+r15]
			BytePattern::temp_instance().find_pattern("46 0F B6 04 38 BA 01 00 00 00 48 8D 4C 24 40");
			if (BytePattern::temp_instance().has_size(1, u8"処理ループ１の文字コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				mapViewProc3CallAddress = Injector::GetBranchDestination(address + 0x0F).as_int();

				// nop
				mapViewProc3ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, mapViewProc3, true);
			}
			else {
				e.unmatch.mapViewProc3Injector = true;
			}
			break;
		default:
			e.version.mapViewProc3Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapViewProc1Injector(options);
		result |= mapViewProc2Injector(options);
		result |= mapViewProc3Injector(options);

		return result;
	}
}