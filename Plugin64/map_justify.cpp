#include "pch.h"
#include "plugin_64.h"

namespace MapJustify {
	extern "C" {
		void mapJustifyProc1();
		uintptr_t mapJustifyProc1ReturnAddress1;
		uintptr_t mapJustifyProc1ReturnAddress2;
	}

	DllError mapJustifyProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// 
			BytePattern::temp_instance().find_pattern("F2 0F 10 5D 68 FF C2 F2 0F 10 65 20");
			if (BytePattern::temp_instance().has_size(1, "文字取得処理リターン先２")) {
				mapJustifyProc1ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.unmatch.mapJustifyProc1Injector = true;
			}

			// movzx   esi, byte ptr [rax+r13]
			BytePattern::temp_instance().find_pattern("42 0F B6 34 28 F3 44 0F 10 89 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, "文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// cmp     word ptr [rdi+6], 0
				mapJustifyProc1ReturnAddress1 = address + 0x1B;

				Injector::MakeJMP(address, mapJustifyProc1, true);
			}
			else {
				e.unmatch.mapJustifyProc1Injector = true;
			}
			break;
		default:
			e.version.mapJustifyProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapJustifyProc1Injector(options);

		return result;
	}
}