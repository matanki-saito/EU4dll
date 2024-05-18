#include "pch.h"
#include "plugin_64.h"

namespace ListFieldAdjustment {
	extern "C" {
		void listFieldAdjustmentProc1();
		void listFieldAdjustmentProc1V131();
		void listFieldAdjustmentProc1V1315();
		void listFieldAdjustmentProc1V137();
		void listFieldAdjustmentProc2();
		void listFieldAdjustmentProc2V131();
		void listFieldAdjustmentProc2V1315();
		void listFieldAdjustmentProc2V137();
		void listFieldAdjustmentProc3();
		void listFieldAdjustmentProc3V1315();
		void listFieldAdjustmentProc3V137A();
		void listFieldAdjustmentProc3V137B();
		uintptr_t listFieldAdjustmentProc1ReturnAddress;
		uintptr_t listFieldAdjustmentProc2ReturnAddress;
		uintptr_t listFieldAdjustmentProc2V1315ReturnAddress;
		uintptr_t listFieldAdjustmentProc3ReturnAddress;		
		uintptr_t listFieldAdjustmentProc3ReturnAddressA;
		uintptr_t listFieldAdjustmentProc3ReturnAddressB;
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
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc1Injector = true;
			}
			break;
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
			// mov     rcx, [rbp+0C0h+var_128]
			BytePattern::temp_instance().find_pattern("48 8B 4D 98 F3 0F 10 B1 48 08 00 00 41 0F B6 04 04");
			if (BytePattern::temp_instance().has_size(1, u8"フォント読み出し")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				listFieldAdjustmentProc1ReturnAddress = address + 0x18;

				Injector::MakeJMP(address, listFieldAdjustmentProc1V131, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc1Injector = true;
			}
			break;
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// mov     rcx, [rbp+0D0h+var_130]
			BytePattern::temp_instance().find_pattern("48 8B 4D A0 F3 0F 10 B1 48 08 00 00 42 0F B6 04 20");
			if (BytePattern::temp_instance().has_size(1, u8"フォント読み出し")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				listFieldAdjustmentProc1ReturnAddress = address + 0x18;

				Injector::MakeJMP(address, listFieldAdjustmentProc1V1315, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc1Injector = true;
			}
			break;
		case v1_37_0_0:
			// mov     r8, [rbp+100h+var_148]
			BytePattern::temp_instance().find_pattern("4C 8B 45 B8 F3 41 0F 10 B0 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"フォント読み出し")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz loc_xxxxx
				listFieldAdjustmentProc1ReturnAddress = address + 0x18;

				Injector::MakeJMP(address, listFieldAdjustmentProc1V137, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc1Injector = true;
			}
			break;
		default:
			e.listFiledAdjustment.versionListFieldAdjustmentProc1Injector = true;
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
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc2Injector = true;
			}
			break;
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
			// inc     ebx
			BytePattern::temp_instance().find_pattern("FF C3 4C 8B 57 10 0F B6 95 08 01 00 00 41 3B DA");
			if (BytePattern::temp_instance().has_size(1, u8"カウントを進める")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jge     loc_xxxxx
				listFieldAdjustmentProc2ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, listFieldAdjustmentProc2V131, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc2Injector = true;
			}
			break;
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// inc     ebx
			BytePattern::temp_instance().find_pattern("FF C3 4C 8B 4F 10 41 3B D9 0F 8D 20 02 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"カウントを進める")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jge     loc_{xxxxx}
				listFieldAdjustmentProc2V1315ReturnAddress =
					Injector::GetBranchDestination(address + 0x09).as_int();

				// 
				listFieldAdjustmentProc2ReturnAddress = address + 0x0F;

				Injector::MakeJMP(address, listFieldAdjustmentProc2V1315, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc2Injector = true;
			}
			break;
		case v1_37_0_0:
			// inc     ebx
			BytePattern::temp_instance().find_pattern("FF C3 8B F3 8B 4F 10 44 0F B6 8D 48 01 00 00 45 33 D2");
			if (BytePattern::temp_instance().has_size(1, u8"カウントを進める")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jl      loc_xxxxx
				listFieldAdjustmentProc2ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, listFieldAdjustmentProc2V137, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc2Injector = true;
			}
			break;
		default:
			e.listFiledAdjustment.versionListFieldAdjustmentProc2Injector = true;
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
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
			// mov     rcx, [rax+rcx*8]
			BytePattern::temp_instance().find_pattern("48 8B 0C C8 44 8B 0C 91 45 33 C0 48 8D 54 24 20");
			if (BytePattern::temp_instance().has_size(2, u8"文字列切り取り処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call sub_xxxxx
				listFieldAdjustmentProc3ReturnAddress = address + 0x13 ;

				Injector::MakeJMP(address, listFieldAdjustmentProc3, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc3Injector = true;
			}
			break;
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// mov     rcx, [rax+rcx*8]
			BytePattern::temp_instance().find_pattern("48 8B 0C C8 44 8B 0C 91 45 33 C0 48 8D 54 24 28");
			if (BytePattern::temp_instance().has_size(2, u8"文字列切り取り処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call sub_xxxxx
				listFieldAdjustmentProc3ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, listFieldAdjustmentProc3V1315, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc3Injector = true;
			}
			break;
		case v1_37_0_0:
			// mov     rcx, [rax+rcx*8]
			BytePattern::temp_instance().find_pattern("48 8B 0C C8 44 8B 0C 91 45 33 C0 48 8D 55 98");
			if (BytePattern::temp_instance().has_size(2, u8"文字列切り取り処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call sub_xxxxx
				listFieldAdjustmentProc3ReturnAddressA = address + 0x12;

				Injector::MakeJMP(address, listFieldAdjustmentProc3V137A, true);

				address = BytePattern::temp_instance().get_second().address();

				// call sub_xxxxx
				listFieldAdjustmentProc3ReturnAddressB = address + 0x12;

				Injector::MakeJMP(address, listFieldAdjustmentProc3V137B, true);
			}
			else {
				e.listFiledAdjustment.unmatchdListFieldAdjustmentProc3Injector = true;
			}
			break;
		default:
			e.listFiledAdjustment.versionListFieldAdjustmentProc3Injector = true;
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