#include "pch.h"
#include "plugin_64.h"

namespace Debug {

	extern "C" {
		void debugProc1();
		uintptr_t debugProc1ReturnAddress;
	}

	errno_t debugProc1Injector(RunOptions options) {
		switch (options.version) {
		case v1_29_0_0:
		case v1_29_1_0:
			// hook main thread head
			// push rdi; push r12; ...
			BytePattern::temp_instance().find_pattern("40 57 41 54 41 55 41 56 41 57 B8 F0 17 00 00");
			if (BytePattern::temp_instance().has_size(1, "debug")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				debugProc1ReturnAddress = address + 15;

				Injector::MakeJMP(address, debugProc1, true);
			}
			else return 1;
			return NOERROR;
		}
		return 1;
	}

	errno_t Init(RunOptions options) {
		errno_t result = 0;
		result |= debugProc1Injector(options);
		return result;
	}
}