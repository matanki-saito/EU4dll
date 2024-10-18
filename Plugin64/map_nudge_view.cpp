#include "pch.h"
#include "plugin_64.h"

namespace MapNudgeView {
	extern "C" {
		void mapNudgeViewProc1();
		void mapNudgeViewProc1V130();
		void mapNudgeViewProc1V136();
		void mapNudgeViewProc1V137();
		uintptr_t mapNudgeViewProc1ReturnAddress;
	}

	DllError mapNudgeViewProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			//  movzx   eax, byte ptr [rax+rcx]
			BytePattern::temp_instance().find_pattern("0F B6 04 08 49 8B 94 C4 00 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"nudge view")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      short loc_xxxxx
				mapNudgeViewProc1ReturnAddress = address + 0xF;

				Injector::MakeJMP(address, mapNudgeViewProc1, true);
			}
			else {
				e.mapNudge.unmatchdMapNudgeViewProc1Injector = true;
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
		case v1_34_2_0:
		case v1_35_1_0:
			//  movzx   eax, byte ptr [rax+rcx]
			BytePattern::temp_instance().find_pattern("0F B6 04 08 49 8B 94 C4 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"nudge view")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      short loc_xxxxx
				mapNudgeViewProc1ReturnAddress = address + 0xF;

				Injector::MakeJMP(address, mapNudgeViewProc1V130, true);
			}
			else {
				e.mapNudge.unmatchdMapNudgeViewProc1Injector = true;
			}
			break;
		case v1_36_0_0:
			//  movzx   eax, byte ptr [rax+rcx]
			BytePattern::temp_instance().find_pattern("0F B6 04 08 49 8B 94 C7 20 01 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"nudge view")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      short loc_xxxxx
				mapNudgeViewProc1ReturnAddress = address + 0xF;

				Injector::MakeJMP(address, mapNudgeViewProc1V136, true);
			}
			else {
				e.mapNudge.unmatchdMapNudgeViewProc1Injector = true;
			}
			break;
		case v1_37_0_0:
			// movzx   eax, byte ptr [rcx+rax]
			BytePattern::temp_instance().find_pattern("0F B6 04 01 49 8B 94 C4 20 01 00 00 48 85 D2");
			if (BytePattern::temp_instance().has_size(1, u8"nudge view")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      short loc_xxxxx
				mapNudgeViewProc1ReturnAddress = address + 0xF;

				Injector::MakeJMP(address, mapNudgeViewProc1V137, true);
			}
			else {
				e.mapNudge.unmatchdMapNudgeViewProc1Injector = true;
			}
			break;
		default:
			e.mapNudge.versionMapNudgeViewProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapNudgeViewProc1Injector(options);

		return result;
	}
}