#include "pch.h"
#include "plugin_64.h"

namespace EventDialog {
	extern "C" {
		void eventDialogProc1();
		uintptr_t eventDialogProc1ReturnAddress;
	}

	DllError eventDialog1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// 
			BytePattern::temp_instance().find_pattern("");
			if (BytePattern::temp_instance().has_size(1, "ÉJÉEÉìÉgèàóù")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// 
				eventDialogProc1ReturnAddress = address + 0;

				Injector::MakeJMP(address, eventDialogProc1, true);
			}
			else {
				e.unmatch.eventDialog1Injector = true;
			}
			break;
		default:
			e.version.eventDialog1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		//result |= eventDialog1Injector(options);

		return result;
	}
}