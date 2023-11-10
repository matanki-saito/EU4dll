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
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
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
		case v1_36_0_0:
			// d w mw w y
			BytePattern::temp_instance().find_pattern("64 20 77 20 6D");
			if (BytePattern::temp_instance().has_size(1, u8"右上の表記を変更")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				Injector::WriteMemory<DateFormat>(address, isoFormat,true);
			}
			else {
				e.date.unmatchdDateProc1Injector = true;
			}
			break;
		default:
			e.date.versionDateProc1Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= dateProc1Injector(options);

		return result;
	}
}