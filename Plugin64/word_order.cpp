#include "pch.h"
#include "plugin_64.h"

namespace WordOrder {
	extern "C" {
		void wordOrderProc2();
		void wordOrderProc3();
		void wordOrderProc4();
		void wordOrderProc5();

		uintptr_t wordOrderProc1CallAddress1;
		uintptr_t wordOrderProc1CallAddress2;
		uintptr_t wordOrderProc2ReturnAddress;
		uintptr_t wordOrderProc3ReturnAddress;
		uintptr_t wordOrderProc4ReturnAddress;
		uintptr_t wordOrderProc5ReturnAddress;
	}

	DllError wordOrderProc1Injector(RunOptions options){
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
			// mov     [rsp+arg_10], rbx
			BytePattern::temp_instance().find_pattern("48 89 5C 24 18 55 41 56 41 57 48 83 EC 20 4D 8B F0");
			if (BytePattern::temp_instance().has_size(1, "std::basic_string<char>#insertをフック")) {
				wordOrderProc1CallAddress1 = BytePattern::temp_instance().get_first().address();
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
			if (BytePattern::temp_instance().has_size(1, "Battle of areaを逆転させる")) {
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


	DllError wordOrderProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8B D0 49 8B CC E8 0B 1F");
			if (BytePattern::temp_instance().has_size(1, "MDEATH_HEIR_SUCCEEDS heir nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				wordOrderProc3ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, wordOrderProc3, true);
			}
			else {
				e.unmatch.wordOrderProc3Injector = true;
			}
			break;
		default:
			e.version.wordOrderProc3Injector = true;
		}

		return e;
	}

	DllError wordOrderProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8B D0 49 8B CC E8 B8 1E");
			if (BytePattern::temp_instance().has_size(1, "MDEATH_REGENCY_RULE heir nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				wordOrderProc4ReturnAddress = address + 0x12;

				// call {xxxxx} std::basic_string<char>#appendをフック。直接はバイナリパターンが多すぎでフックできなかった
				wordOrderProc1CallAddress2 = Injector::GetBranchDestination(address + 0xD).as_int();

				Injector::MakeJMP(address, wordOrderProc4, true);
			}
			else {
				e.unmatch.wordOrderProc4Injector = true;
			}
			break;
		default:
			e.version.wordOrderProc4Injector = true;
		}

		return e;
	}

	DllError wordOrderProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8B D0 48 8B CF E8 27 41");
			if (BytePattern::temp_instance().has_size(1, "nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				wordOrderProc5ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, wordOrderProc5, true);
			}
			else {
				e.unmatch.wordOrderProc5Injector = true;
			}
			break;
		default:
			e.version.wordOrderProc5Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= wordOrderProc1Injector(options);
		result |= wordOrderProc2Injector(options);
		result |= wordOrderProc3Injector(options);
		result |= wordOrderProc4Injector(options);
		result |= wordOrderProc5Injector(options);

		return result;
	}
}