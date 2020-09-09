#include "pch.h"
#include "plugin_64.h"

namespace EventDialog {
	extern "C" {
		void eventDialogProc1();
		void eventDialogProc2();
		void eventDialogProc3();
		void eventDialogProc3V130();
		uintptr_t eventDialogProc1ReturnAddress;
		uintptr_t eventDialogProc2ReturnAddress1;
		uintptr_t eventDialogProc2ReturnAddress2;
		uintptr_t eventDialogProc3ReturnAddress;
	}

	DllError eventDialog1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
			// movzx   eax, byte ptr [rcx+rax]
			BytePattern::temp_instance().find_pattern("0F B6 04 01 49 8B 34 C2 F3 41 0F 10 8A 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz      loc_xxxxx
				eventDialogProc1ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, eventDialogProc1, true);
			}
			else {
				e.unmatch.eventDialog1Injector = true;
			}
			break;
		default:
			e.version.eventDialog1Injector = true;
		}

		return e;
	}

	DllError eventDialog2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
			// mov     rax, [rsp+378h+arg_20]
			BytePattern::temp_instance().find_pattern("48 8B 84 24 A0 03 00 00 8B 00 03 C0");
			if (BytePattern::temp_instance().has_size(1, u8"分岐処理修正戻り先アドレス２")) {
				eventDialogProc2ReturnAddress2 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.unmatch.eventDialog1Injector = true;
			}

			// cvtdq2ps xmm0, xmm0
			BytePattern::temp_instance().find_pattern("0F 5B C0 F3 0F 59 C1 41 0F 2E C0 7A 4D");
			if (BytePattern::temp_instance().has_size(1, u8"分岐処理修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// movd    xmm0, [rsp+378h+arg_8]
				eventDialogProc2ReturnAddress1 = address + 0x0F;

				Injector::MakeJMP(address, eventDialogProc2, true);
			}
			else {
				e.unmatch.eventDialog2Injector = true;
			}
			break;
		default:
			e.version.eventDialog2Injector = true;
		}

		return e;
	}


	DllError eventDialog3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_3_0:
		case v1_29_4_0:
			// inc     edi
			BytePattern::temp_instance().find_pattern("FF C7 3B 7B 10 8B 94 24 90 03 00 00 4C 8D");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				//  mov     r11, 0BFFFFFF43FFFFFFh
				eventDialogProc3ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, eventDialogProc3, true);
			}
			else {
				e.unmatch.eventDialog2Injector = true;
			}
			break;
		case v1_30_4_0:
		case v1_30_3_0:
		case v1_30_2_0:
		case v1_30_1_0:
			// inc     edi
			BytePattern::temp_instance().find_pattern("FF C7 3B 7B 10 8B 94 24 90 03 00 00 4C 8D");
			if (BytePattern::temp_instance().has_size(1, u8"カウントアップ")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				//  mov     r11, 0BFFFFFF43FFFFFFh
				eventDialogProc3ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, eventDialogProc3V130, true);
			}
			else {
				e.unmatch.eventDialog2Injector = true;
			}
			break;
		default:
			e.version.eventDialog2Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= eventDialog1Injector(options);
		result |= eventDialog2Injector(options);
		result |= eventDialog3Injector(options);

		return result;
	}
}