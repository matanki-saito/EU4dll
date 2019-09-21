#include "pch.h"
#include "plugin_64.h"

namespace MainText {
	extern "C" {
		void mainTextProc1();
		uintptr_t mainTextProc1ReturnAddress;
	}

	DllError mainTextProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// 
			BytePattern::temp_instance().find_pattern("48 63 C7 0F B6 04 18 F3 41 0F 10 9F 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, "character viewing")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				mainTextProc1ReturnAddress = address + 0x1B;

				Injector::MakeJMP(address, mainTextProc1, true);
			}
			else {
				e.unmatch.mainTextProc1Injector = true;
			}
		default:
			e.version.mainTextProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		// フォント読み出し
		result |= mainTextProc1Injector(options);
		return result;
	}
}