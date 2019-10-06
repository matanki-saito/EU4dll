#include "pch.h"
#include "plugin_64.h"
#include "escape_tool.h"

namespace FileSave {
	extern "C" {
		void fileSaveProc1();
		void fileSaveProc3();
		void fileSaveProc4();
		void fileSaveProc5();
		uintptr_t fileSaveProc1ReturnAddress;
		uintptr_t fileSaveProc3ReturnAddress;
		uintptr_t fileSaveProc3CallAddress;
		uintptr_t fileSaveProc4ReturnAddress;
		uintptr_t fileSaveProc4CallAddress;
		uintptr_t fileSaveProc4MarkerAddress;
		uintptr_t fileSaveProc5ReturnAddress;
		uintptr_t fileSaveProc5CallAddress;
		uintptr_t fileSaveProc5MarkerAddress;
	}

	DllError fileSaveProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_2_0:
			// mov     eax, [rcx+10h]
			BytePattern::temp_instance().find_pattern("8B 41 10 85 C0 0F 84 31 01 00 00");
			if (BytePattern::temp_instance().has_size(1, "ファイル名を安全にしている場所を短絡する")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				fileSaveProc1ReturnAddress = Injector::GetBranchDestination(address + 0x5).as_int();

				Injector::MakeJMP(address, fileSaveProc1, true);
			}
			else {
				e.unmatch.fileSaveProc1Injector = true;
			}
			break;
		default:
			e.version.fileSaveProc1Injector = true;
		}

		return e;
	}

	DllError fileSaveProc2Injector(RunOptions options) {
		DllError e = {};
		// 48 8B D0 48 8D 4D EF E8  69 98 39 FF 90 48 8D 4D EF
		return e;
	}

	DllError fileSaveProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_2_0:
			// mov     eax, [rcx+10h]
			BytePattern::temp_instance().find_pattern("48 8D 15 46 A6 B9 00 FF 90 98 00 00 00");
			if (BytePattern::temp_instance().has_size(1, "ダイアログでのセーブエントリのタイトルを表示できるようにする")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				fileSaveProc3CallAddress = (uintptr_t) utf8ToEscapedStr;

				// call sub_xxxxx
				fileSaveProc3ReturnAddress = address + 0x1A;

				Injector::MakeJMP(address, fileSaveProc3, true);
			}
			else {
				e.unmatch.fileSaveProc3Injector = true;
			}
			break;
		default:
			e.version.fileSaveProc3Injector = true;
		}

		return e;
	}

	DllError fileSaveProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_2_0:
			// lea     r8, [rbp+0]
			BytePattern::temp_instance().find_pattern("4C 8D 45 00 48 8D 15 ? ? ? ? 48 8D 4C 24 70 E8 ? ? ? ? 90");
			if (BytePattern::temp_instance().has_size(1, "ダイアログでのセーブエントリのツールチップを表示できるようにする1")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				fileSaveProc4CallAddress = (uintptr_t)utf8ToEscapedStrFromV;

				// lea rdx, {aZy}
				fileSaveProc4MarkerAddress = Injector::GetBranchDestination(address + 4).as_int();

				// call sub_xxxxx
				fileSaveProc4ReturnAddress = address + 0x10;

				Injector::MakeJMP(address, fileSaveProc4, true);
			}
			else {
				e.unmatch.fileSaveProc4Injector = true;
			}
			break;
		default:
			e.version.fileSaveProc4Injector = true;
		}

		return e;
	}

	DllError fileSaveProc5Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_2_0:
			// lea     r8, [r14+598h]
			BytePattern::temp_instance().find_pattern("4D 8D 86 98 05 00 00 48 8D 15 ? ? ? ? 48 8D 4C 24 50");
			if (BytePattern::temp_instance().has_size(1, "ダイアログでのセーブエントリのツールチップを表示できるようにする2")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				fileSaveProc5CallAddress = (uintptr_t)utf8ToEscapedStrFromV;

				// lea rdx, {aZy}
				fileSaveProc5MarkerAddress = Injector::GetBranchDestination(address + 7).as_int();

				// call sub_xxxxx
				fileSaveProc5ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, fileSaveProc5, true);
			}
			else {
				e.unmatch.fileSaveProc5Injector = true;
			}
			break;
		default:
			e.version.fileSaveProc5Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		/* UTF-8ファイルを列挙できない問題は解決された */

		result |= fileSaveProc1Injector(options);
		//result |= fileSaveProc2Injector(options);
		result |= fileSaveProc3Injector(options);
		// これは使われなくなった？
		//result |= fileSaveProc4Injector(options);
		result |= fileSaveProc5Injector(options);

		return result;
	}
}