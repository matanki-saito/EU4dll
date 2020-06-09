#include "pch.h"
#include "plugin_64.h"
#include <atlstr.h>

namespace WordOrder {
	extern "C" {
		void wordOrderProc2();
		void wordOrderProc3();
		void wordOrderProc3V130();
		void wordOrderProc4();
		void wordOrderProc4V130();
		void wordOrderProc5();
		void wordOrderProc6();
		void wordOrderProc7();
		void wordOrderProc8();

		uintptr_t wordOrderProc1CallAddress1;
		uintptr_t wordOrderProc1CallAddress2;
		uintptr_t wordOrderProc2ReturnAddress;
		uintptr_t wordOrderProc3ReturnAddress;
		uintptr_t wordOrderProc4ReturnAddress;
		uintptr_t wordOrderProc5ReturnAddress;
		uintptr_t wordOrderProc6ReturnAddress;
		uintptr_t wordOrderProc7ReturnAddress;
		uintptr_t wordOrderProc8ReturnAddress;

		uintptr_t wordOrderProc7CallAddress1;
		uintptr_t wordOrderProc7CallAddress2;

		uintptr_t generateCString;
		uintptr_t concatCString;
		uintptr_t concat2CString;

		uintptr_t year;
		uintptr_t month;
		uintptr_t day;
	}

	DllError wordOrderProc1Injector(RunOptions options){
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
		case v1_30_1_0:
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
		case v1_30_1_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 33 AF E9 FF");
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
		case v1_30_1_0:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 A3 A1 DD FF");
			if (BytePattern::temp_instance().has_size(1, "MDEATH_HEIR_SUCCEEDS heir nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				wordOrderProc3ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, wordOrderProc3V130, true);
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
		case v1_30_1_0:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 46 A1 DD FF");
			if (BytePattern::temp_instance().has_size(1, "MDEATH_REGENCY_RULE heir nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				wordOrderProc4ReturnAddress = address + 0x12;

				// call {xxxxx} std::basic_string<char>#appendをフック。直接はバイナリパターンが多すぎでフックできなかった
				wordOrderProc1CallAddress2 = Injector::GetBranchDestination(address + 0xD).as_int();

				Injector::MakeJMP(address, wordOrderProc4V130, true);
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
		case v1_30_1_0:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8B D0 48 8B CF E8 27 1D");
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

	// 停戦日付など
	DllError wordOrderProc6Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 4F FA B4 FF");
			if (BytePattern::temp_instance().has_size(1, "M, Y → Y年M")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				wordOrderProc6ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, wordOrderProc6, true);
			}
			else {
				e.unmatch.wordOrderProc6Injector = true;
			}
			break;
		case v1_30_1_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 0F 7B AD");
			if (BytePattern::temp_instance().has_size(1, "M, Y → Y年M")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				wordOrderProc6ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, wordOrderProc6, true);
			}
			else {
				e.unmatch.wordOrderProc6Injector = true;
			}
			break;
		default:
			e.version.wordOrderProc6Injector = true;
		}

		return e;
	}

	DllError wordOrderProc7Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 4C 8D 44 24 48 48 8D 54 24 28 48 8D 4D E8 E8 65 9D");
			if (BytePattern::temp_instance().has_size(1, "D M, Y → Y年MD日")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				wordOrderProc7CallAddress1 = Injector::GetBranchDestination(address + 0xF).as_int();
				wordOrderProc7CallAddress2 = Injector::GetBranchDestination(address + 0x20).as_int();

				// nop
				wordOrderProc7ReturnAddress = address + 0x5E;

				Injector::MakeJMP(address, wordOrderProc7, true);
			}
			else {
				e.unmatch.wordOrderProc7Injector = true;
			}
			break;
		case v1_30_1_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 4C 8D 44 24 48 48 8D 54 24 28 48 8D 4D E8 E8 65 6A");
			if (BytePattern::temp_instance().has_size(1, "D M, Y → Y年MD日")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				wordOrderProc7CallAddress1 = Injector::GetBranchDestination(address + 0xF).as_int();
				wordOrderProc7CallAddress2 = Injector::GetBranchDestination(address + 0x20).as_int();

				// nop
				wordOrderProc7ReturnAddress = address + 0x5E;

				Injector::MakeJMP(address, wordOrderProc7, true);
			}
			else {
				e.unmatch.wordOrderProc7Injector = true;
			}
			break;
		default:
			e.version.wordOrderProc7Injector = true;
		}

		return e;
	}

	// 外交官のポップアップなど
	DllError wordOrderProc8Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
			// nop 
			BytePattern::temp_instance().find_pattern("90 4C 8D 45 A7 48 8D 55 0F 48 8D 4D EF E8 31 02");
			if (BytePattern::temp_instance().has_size(1, "M Y → Y年M")) {
				// mov     r8d, 1
				uintptr_t address = BytePattern::temp_instance().get_first().address() - 0x16;
				
				generateCString = Injector::GetBranchDestination(address + 0x11).as_int();
				concatCString = Injector::GetBranchDestination(address + 0x23).as_int();
				concat2CString = Injector::GetBranchDestination(address + 0x33).as_int();

				// nop
				wordOrderProc8ReturnAddress = address + 0x38;

				Injector::MakeJMP(address, wordOrderProc8, true);
			}
			else {
				e.unmatch.wordOrderProc8Injector = true;
			}
			break;
		case v1_30_1_0:
			// nop 
			BytePattern::temp_instance().find_pattern("90 4C 8D 45 A7 48 8D 55 0F 48 8D 4D EF E8 81 E1");
			if (BytePattern::temp_instance().has_size(1, "M Y → Y年M")) {
				// mov     r8d, 1
				uintptr_t address = BytePattern::temp_instance().get_first().address() - 0x16;

				generateCString = Injector::GetBranchDestination(address + 0x11).as_int();
				concatCString = Injector::GetBranchDestination(address + 0x23).as_int();
				concat2CString = Injector::GetBranchDestination(address + 0x33).as_int();

				// nop
				wordOrderProc8ReturnAddress = address + 0x38;

				Injector::MakeJMP(address, wordOrderProc8, true);
			}
			else {
				e.unmatch.wordOrderProc8Injector = true;
			}
			break;
		default:
			e.version.wordOrderProc8Injector = true;
		}

		return e;
	}

	ParadoxTextObject _year;
	ParadoxTextObject _month;
	ParadoxTextObject _day;

	DllError Init(RunOptions options) {
		DllError result = {};

		_day.t.text[0] = 0xE;
		_day.t.text[1] = '\0';
		_day.len = 1;
		_day.len2 = 0xF;

		_year.t.text[0] = 0xF;
		_year.t.text[1] = '\0';
		_year.len = 1;
		_year.len2 = 0xF;

		_month.t.text[0] = 7;
		_month.t.text[1] = '\0';
		_month.len = 1;
		_month.len2 = 0xF;
		
		year = (uintptr_t) &_year;
		month = (uintptr_t)&_month;
		day = (uintptr_t)&_day;

		result |= wordOrderProc1Injector(options);
		result |= wordOrderProc2Injector(options);
		result |= wordOrderProc3Injector(options);
		result |= wordOrderProc4Injector(options);
		result |= wordOrderProc5Injector(options);
		result |= wordOrderProc6Injector(options);
		result |= wordOrderProc7Injector(options);
		result |= wordOrderProc8Injector(options);

		return result;
	}
}