#include "pch.h"
#include "plugin_64.h"

namespace FileSave {
	extern "C" {
		void fileSaveProc1();
		uintptr_t fileSaveProc1ReturnAddress;
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

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= fileSaveProc1Injector(options);

		return result;
	}
}