#include "pch.h"
#include "plugin_64.h"

namespace ListFieldAdjustment {
	extern "C" {
		void listFieldAdjustmentProc1();
		void listFieldAdjustmentProc2();
		void listFieldAdjustmentProc3();
		uintptr_t listFieldAdjustmentProc1ReturnAddress;
		uintptr_t listFieldAdjustmentProc2ReturnAddress;
		uintptr_t listFieldAdjustmentProc3ReturnAddress;
	}

	DllError listFieldAdjustmentProc1Injector(RunOptions options) {
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
			// mov     r8, [rbp+0B0h+var_118]
			BytePattern::temp_instance().find_pattern("4C 8B 45 98 F3 41 0F 10 B0 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"フォント読み出し")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				listFieldAdjustmentProc1ReturnAddress = address + 0x19;

				Injector::MakeJMP(address, listFieldAdjustmentProc1, true);
			}
			else {
				e.unmatch.listFieldAdjustmentProc1Injector = true;
			}
			break;
		default:
			e.version.listFieldAdjustmentProc1Injector = true;
		}

		return e;
	}

	DllError listFieldAdjustmentProc2Injector(RunOptions options) {
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
			// inc     ebx
			BytePattern::temp_instance().find_pattern("FF C3 4C 8B 4F 10 0F B6 95 F8 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"カウントを進める")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jge     loc_xxxxx
				listFieldAdjustmentProc2ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, listFieldAdjustmentProc2, true);
			}
			else {
				e.unmatch.listFieldAdjustmentProc2Injector = true;
			}
			break;
		default:
			e.version.listFieldAdjustmentProc2Injector = true;
		}

		return e;
	}

	DllError listFieldAdjustmentProc3Injector(RunOptions options) {
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
			// mov     rcx, [rax+rcx*8]
			BytePattern::temp_instance().find_pattern("48 8B 0C C8 44 8B 0C 91 45 33 C0 48 8D 54 24 20");
			if (BytePattern::temp_instance().has_size(2, u8"文字列切り取り処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call sub_xxxxx
				listFieldAdjustmentProc3ReturnAddress = address + 0x13 ;

				Injector::MakeJMP(address, listFieldAdjustmentProc3, true);
			}
			else {
				e.unmatch.listFieldAdjustmentProc3Injector = true;
			}
			break;
		default:
			e.version.listFieldAdjustmentProc3Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= listFieldAdjustmentProc1Injector(options);
		result |= listFieldAdjustmentProc2Injector(options);
		result |= listFieldAdjustmentProc3Injector(options);

		return result;
	}

}