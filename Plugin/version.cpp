#include "stdinc.h"
#include "byte_pattern.h"

namespace Misc {
	
	typedef struct _A{
		byte ascii1;
		byte ascii2;
		byte dot;
		byte ascii3;

		int calVer() {
			int ver =  (ascii1 - 0x30) * 100 + (ascii2 - 0x30)*10 + (ascii3 - 0x30);
			return ver;
		}
	} A;

	EU4Version getVersion(){
		// Hydra v1.7.1
		byte_pattern::temp_instance().find_pattern("48 79 64 72 61 20 76 31 2E 37 2E 31 00");
		if (byte_pattern::temp_instance().count() > 0) {
			// ??を取得する
			
			auto a = byte_pattern::temp_instance().get_first().address();

			return v1_25_X;
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