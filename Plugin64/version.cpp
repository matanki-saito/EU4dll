#include "pch.h"
#include "plugin_64.h"

using namespace std;

namespace Version {
	typedef struct {
		char ascii1;
		char ascii2;
		char dot;
		char ascii3;

		int calVer() {
			int ver = (ascii1 - 0x30) * 100 + (ascii2 - 0x30) * 10 + (ascii3 - 0x30);
			return ver;
		}
	} Pattern;

	string versionString(Eu4Version version) {
		switch (version) {
		case v1_29_0_0:
			return "v1_29_0_0";
		case v1_29_1_0:
			return "v1_29_1_0";
		case v1_29_2_0:
			return "v1_29_2_0";
		case v1_29_3_0:
			return "v1_29_3_0";
		case v1_29_4_0:
			return "v1_29_4_0";
		default:
			return "UNKNOWN";
		}
	}

	void GetVersionFromExe(RunOptions *options) {
		Eu4Version version;
		
		// EU4 v1.??.?
		BytePattern::temp_instance().find_pattern("45 55 34 20 76 31 2E ? ? 2E ?");
		if (BytePattern::temp_instance().count() > 0) {
			// ??を取得する
			Pattern minor = Injector::ReadMemory<Pattern>(BytePattern::temp_instance().get_first().address(0x7), true);

			switch (minor.calVer()) {
			case 290:
				version = v1_29_0_0;
				break;
			case 291:
				version = v1_29_1_0;
				break;
			case 292:
				version = v1_29_2_0;
				break;
			case 293:
				version = v1_29_3_0;
				break;
			case 294:
			case 295:
				version = v1_29_4_0;
				break;
			default:
				version = UNKNOWN;
				break;
				;;
			}

			BytePattern::LoggingInfo(versionString(version));
		}
		else {
			version = UNKNOWN;
		}

		options->version = version;
	}
}