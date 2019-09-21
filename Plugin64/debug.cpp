#include "pch.h"
#include "plugin_64.h"

namespace Debug {

	extern "C" {
		void debugProc1();
		uintptr_t debugProc1ReturnAddress;
	}

	DllError debugProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// hook main thread head
			// push rdi; push r12; ...
			BytePattern::temp_instance().find_pattern("40 57 41 54 41 55 41 56 41 57 B8 A0 18 00 00");
			if (BytePattern::temp_instance().has_size(1, "debug")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				debugProc1ReturnAddress = address + 15;

				Injector::MakeJMP(address, debugProc1, true);
			} else {
				e.unmatch.debugProc1Injector = true;
			}
		default:
			e.version.debugProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};
		result |= debugProc1Injector(options);
		return result;
	}
}