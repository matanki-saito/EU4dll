#include "pch.h"
#include "plugin_64.h"

using namespace std;

namespace Version {
	typedef struct _Pattern {
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
			return u8"v1_29_0_0";
		case v1_29_1_0:
			return u8"v1_29_1_0";
		case v1_29_2_0:
			return u8"v1_29_2_0";
		case v1_29_3_0:
			return u8"v1_29_3_0";
		case v1_29_4_0:
			return u8"v1_29_4_0";
		case v1_30_1_0:
			return u8"v1_30_1_0";
		case v1_30_2_0:
			return u8"v1_30_2_0";
		case v1_30_3_0:
			return u8"v1_30_3_0";
		case v1_30_4_0:
			return u8"v1_30_4_0";
		case v1_30_5_0:
			return u8"v1_30_5_0";
		case v1_31_1_0:
			return u8"v1_31_1_0";
		case v1_31_2_0:
			return u8"v1_31_2_0";
		case v1_31_3_0:
			return u8"v1_31_3_0";
		case v1_31_4_0:
			return u8"v1_31_4_0";
		case v1_31_5_0:
			return u8"v1_31_5_0";
		case v1_31_6_0:
			return u8"v1_31_6_0";
		case v1_32_0_1:
			return u8"v1_32_0_1";
		case v1_33_0_0:
			return u8"v1_33_0_0";
		case v1_33_3_0:
			return u8"v1_33_3_0";
		case v1_34_2_0:
			return u8"v1_34_2_0";
		default:
			return u8"UNKNOWN";
		}
	}

	void GetVersionFromExe(RunOptions *options) {
		Eu4Version version = UNKNOWN;
		
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
			case 296:
				version = v1_29_4_0;
				break;
			case 301:
				version = v1_30_1_0;
				break;
			case 302:
				version = v1_30_2_0;
				break;
			case 303:
				version = v1_30_3_0;
				break;
			case 330:
				version = v1_33_0_0;
				break;
			case 331:
			case 332:
				version = v1_33_0_0;
				break;
			case 333:
				version = v1_33_3_0;
				break;
			case 342:
			case 343:
			case 344:
				version = v1_34_2_0;
				break;
			}
		}

		// release_v1.??.?
		BytePattern::temp_instance().find_pattern("72 65 6C 65 61 73 65 5F 31 2E ? ? 2E ? 00");
		if (version == UNKNOWN && BytePattern::temp_instance().count() > 0) {
			// ??を取得する
			Pattern minor = Injector::ReadMemory<Pattern>(BytePattern::temp_instance().get_first().address(10), true);

			switch (minor.calVer()) {
			case 322:
			case 321:
				version = v1_32_0_1;
				break;
			case 316:
				version = v1_31_6_0;
				break;
			case 315:
				version = v1_31_5_0;
				break;
			case 314:
				version = v1_31_4_0;
				break;
			case 313:
				version = v1_31_3_0;
				break;
			case 312:
				version = v1_31_2_0;
				break;
			case 311:
				version = v1_31_1_0;
				break;
			case 306:
			case 305:
				version = v1_30_5_0;
				break;
			case 304:
				version = v1_30_4_0;
				break;
			}
		}

		BytePattern::LoggingInfo(versionString(version));

		options->version = version;
	}
}