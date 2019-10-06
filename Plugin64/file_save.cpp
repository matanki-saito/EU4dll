#include "pch.h"
#include "plugin_64.h"
#include "escape_tool.h"

namespace FileSave {
	extern "C" {
		void fileSaveProc1();
		void fileSaveProc3();
		uintptr_t fileSaveProc1ReturnAddress;
		uintptr_t fileSaveProc3ReturnAddress;
		uintptr_t fileSaveProc3CallAddress;
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

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= fileSaveProc1Injector(options);
		//result |= fileSaveProc2Injector(options);
		result |= fileSaveProc3Injector(options);

		/* UTF-8ファイルを列挙できない問題は解決された */

		return result;
	}
}