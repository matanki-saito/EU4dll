#include "pch.h"
#include "plugin_64.h"

namespace MapAdjustment {
	extern "C" {
		void mapAdjustmentProc1();
		uintptr_t mapAdjustmentProc1ReturnAddress;
		uintptr_t mapAdjustmentProc1CallAddress;
	}

	// これはwin32のときはmiscにあったが統合した。
	// この処理はwin32のときは独立したprocであったが、win64ではinline展開されている。
	// この処理の下の方では文字取得（49 8B 14 C7 48 85 D2 74  09 66 83 7A 06 0）があるので
	// 別途そちらも修正する必要がある
	DllError mapAdjustmentProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// movsx ecx, byte ptr [rdi + rbx]
			BytePattern::temp_instance().find_pattern("0F BE 0C 1F E8 72 B6 98 00 88 04 1F");
			if (BytePattern::temp_instance().has_size(1, "マップ文字の大文字化キャンセル")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				mapAdjustmentProc1CallAddress = Injector::GetBranchDestination(address + 0x04).as_int();

				// cmp byte ptr [rdi + r14] , 0
				mapAdjustmentProc1ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, mapAdjustmentProc1, true);
			}
			else {
				e.unmatch.mapAdjustmentProc1Injector = true;
			}
		default:
			e.version.mapAdjustmentProc1Injector = true;
		}

		return e;
	}


	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapAdjustmentProc1Injector(options);

		return result;
	}
}