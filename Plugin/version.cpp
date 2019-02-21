#include "stdinc.h"
#include "byte_pattern.h"

namespace Misc {
	
	typedef struct _A{
		byte ascii1;
		byte ascii2;
		byte dot;
		byte ascii3;

		int calVer() {
			return (ascii1 - 0x30) * 100 + (ascii2 - 0x30)*10 + (ascii3 - 0x30);
		}
	} A;

	EU4Version getVersion(){
		// EU4 v1.??.?
		// これだと出たばっかりの時の1.28.0.0の・ようなものには対応できないので別途対応する必要あり
		byte_pattern::temp_instance().find_pattern("45 55 34 20 76 31 2E ? ? 2E ?");
		if (byte_pattern::temp_instance().count() > 0) {
			// ??を取得する
			A minor = injector::ReadMemory<A>(byte_pattern::temp_instance().get_first().address(0x7), true);

			EU4Version version;

			switch (minor.calVer()) {
			case 250:
				version = v1_25_X;
				break;
			case 260:
				version = v1_26_X;
				break;
			case 270:
				version = v1_27_X;
				break;
			case 280:
				version = v1_28_X;
				break;
			case 283:
				version = v1_28_3;
				break;
			default:
				version = UNKNOWN;
				break;
;;			}

			byte_pattern::temp_instance().debug_output2(Misc::versionString(version));

			return version;
		}
		else return UNKNOWN;
	}

	std::string versionString(EU4Version version) {
		switch (version) {
		case v1_25_X:
			return "v1_25_X";
		case v1_26_X:
			return "v1_26_X";
		case v1_27_X:
			return "v1_27_X";
		case v1_28_X:
			return "v1_28_X";
		case v1_28_3:
			return "v1_28_3";
		default:
			return "UNKNOWN";
		}
	}
}