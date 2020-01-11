#include "pch.h"
#include "plugin_64.h"
#include "escape_tool.h"

// 1.28.3,1.29.3時点でSDLのversionは2.0.4 hg-10001:e12c38730512
namespace Input {
	extern "C" {
		void inputProc1();
		uintptr_t inputProc1ReturnAddress1;
		uintptr_t inputProc1ReturnAddress2;
		uintptr_t inputProc1CallAddress;

		void inputProc2();
		uintptr_t inputProc2ReturnAddress;
	}

	DllError inputProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_3_0:
			// mov     eax, dword ptr	[rbp+120h+var_198+0Ch]
			BytePattern::temp_instance().find_pattern("8B 45 94 32 DB 3C 80 73 05 0F B6 D8 EB 10");
			if (BytePattern::temp_instance().has_size(1, "入力した文字をutf8からエスケープ列へ変換する")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				inputProc1CallAddress = (uintptr_t)utf8ToEscapedStr3;

				// mov     rax, [r13+0]
				inputProc1ReturnAddress1 = address + 0x1E;

				Injector::MakeJMP(address, inputProc1, true);
			}
			else {
				e.unmatch.inputProc1Injector = true;
			}

			// call    qword ptr [rax+18h]
			BytePattern::temp_instance().find_pattern("FF 50 18 E9 5C 01 00 00");
			if (BytePattern::temp_instance().has_size(1, "入力した文字をutf8からエスケープ列へ変換する")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				// jmp     loc_{xxxxx}
				inputProc1ReturnAddress2 = Injector::GetBranchDestination(address + 0x3).as_int();
			}
			else {
				e.unmatch.inputProc1Injector = true;
			}

			break;
		default:
			e.version.inputProc1Injector = true;
		}

		return e;
	}

	DllError inputProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_3_0:
			// mov     rax, [rdi]
			BytePattern::temp_instance().find_pattern("48 8B 07 48 8B CF 85 DB 74 08 FF 90 40 01 00 00");
			if (BytePattern::temp_instance().has_size(1, "バックスペース処理の修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// movzx   r8d, word ptr [rdi+56h]
				inputProc2ReturnAddress = address + 0x18;

				Injector::MakeJMP(address, inputProc2, true);
			}
			else {
				e.unmatch.inputProc2Injector = true;
			}
			break;
		default:
			e.version.inputProc2Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= inputProc1Injector(options);
		result |= inputProc2Injector(options);

		return result;
	}
}