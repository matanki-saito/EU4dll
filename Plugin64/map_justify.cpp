#include "pch.h"
#include "plugin_64.h"

namespace MapJustify {
	extern "C" {
		void mapJustifyProc1();
		uintptr_t mapJustifyProc1ReturnAddress;
	}

	DllError mapJustifyProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// 
			BytePattern::temp_instance().find_pattern("");
			if (BytePattern::temp_instance().has_size(1, "")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// 
				mapJustifyProc1ReturnAddress = address + ;

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