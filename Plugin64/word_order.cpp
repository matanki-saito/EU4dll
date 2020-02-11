#include "pch.h"
#include "plugin_64.h"

namespace WordOrder {
	extern "C" {
		void wordOrderProc2();

		uintptr_t wordOrderProc1CallAddress;
		uintptr_t wordOrderProc2ReturnAddress;
	}

	DllError wordOrderProc1Injector(RunOptions options){
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
			// mov     [rsp+arg_10], rbx
			BytePattern::temp_instance().find_pattern("48 89 5C 24 18 55 41 56 41 57 48 83 EC 20 4D 8B F0");
			if (BytePattern::temp_instance().has_size(1, "std::basic_string<char>#insert‚ðƒtƒbƒN")) {
				wordOrderProc1CallAddress = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.unmatch.wordOrderProc1Injector = true;
			}
			break;
		default:
			e.version.wordOrderProc1Injector = true;
		}

		return e;
	}

	DllError wordOrderProc2Injector(RunOptions options) {
		DllError e = {};

		if (!options.reversingWordsBattleOfArea) return e;

		switch (options.version) {
		case v1_29_4_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 13 70 EB FF");
			if (BytePattern::temp_instance().has_size(1, "Battle of area‚ð‹t“]‚³‚¹‚é")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				wordOrderProc2ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, wordOrderProc2, true);
			}
			else {
				e.unmatch.wordOrderProc2Injector = true;
			}
			break;
		default:
			e.version.wordOrderProc2Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= wordOrderProc1Injector(options);
		result |= wordOrderProc2Injector(options);

		return result;
	}
}