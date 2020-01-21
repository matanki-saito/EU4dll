#include "pch.h"
#include "plugin_64.h"

namespace Date {
	extern "C" {
		void dateProc2();
		uintptr_t dateProc2ReturnAddress;
	}

	typedef struct _DateFormat {
		char text[11];
	} DateFormat;

	DllError dateProc1Injector(RunOptions options) {
		DllError e = {};

		// ex) 1444年11月11日
		DateFormat isoFormat = {
			{'y',' ',0x0F,' ','m','w',' ','d',' ',0x0E,0}
		};

		switch (options.version) {
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
			// d w mw w y
			BytePattern::temp_instance().find_pattern("64 20 77 20 6D");
			if (BytePattern::temp_instance().has_size(1, "右上の表記を変更")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::WriteMemory<DateFormat>(address, isoFormat,true);
			}
			else {
				e.unmatch.dateProc1Injector = true;
			}
			break;
		default:
			e.version.dateProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= dateProc1Injector(options);

		return result;
	}
}