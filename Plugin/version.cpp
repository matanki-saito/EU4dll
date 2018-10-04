#include "stdinc.h"
#include "byte_pattern.h"

namespace Misc {
	
	typedef struct _A{
		byte ascii1;
		byte ascii2;

		int calMinorVer() {
			return (ascii1 - 0x30) * 10 + (ascii2 - 0x30);
		}
	} A;

	EU4Version getVersion(){
		// EU4 v1.??.
		byte_pattern::temp_instance().find_pattern("45 55 34 20 76 31 2E ? ? 2E");
		if (byte_pattern::temp_instance().count() > 0) {
			// ??‚ðŽæ“¾‚·‚é
			A minor = injector::ReadMemory<A>(byte_pattern::temp_instance().get_first().address(0x7), true);

			EU4Version version;

			switch (minor.calMinorVer()) {
			case 25:
				version =  v1_25_X;
				break;
			case 26:
				version = v1_26_X;
				break;
			case 27:
				version = v1_27_X;
				break;
			default:
				version = UNKNOWN;
				break;
;;			}

			byte_pattern::temp_instance().debug_output2(Misc::versionString(version));

			return version;
		}
	}

	std::string versionString(EU4Version version) {
		switch (version) {
		case v1_25_X:
			return "v1_25_X";
		case v1_26_X:
			return "v1_26_X";
		case v1_27_X:
			return "v1_27_X";
		default:
			return "UNKNOWN";
		}
	}
}