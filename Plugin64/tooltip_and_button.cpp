#include "pch.h"
#include "plugin_64.h"

namespace TooltipAndButton {
	extern "C" {
		void tooltipAndButtonProc1();
		void tooltipAndButtonProc2();
		void tooltipAndButtonProc3();
		uintptr_t tooltipAndButtonProc1ReturnAddress;
		uintptr_t tooltipAndButtonProc1CallAddress;
		uintptr_t tooltipAndButtonProc2ReturnAddress;
		uintptr_t tooltipAndButtonProc3ReturnAddress;
	}

	DllError tooltipAndButtonProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// r8d, byte ptr [rax + rcx]
			BytePattern::temp_instance().find_pattern("44 0F B6 04 08 BA 01 00 00 00");
			if (BytePattern::temp_instance().has_size(1, "処理ループ１の文字コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				tooltipAndButtonProc1CallAddress = Injector::GetBranchDestination(address + 0x0E).as_int();
				
				// nop
				tooltipAndButtonProc1ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, tooltipAndButtonProc1, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc1Injector = true;
			}
		default:
			e.version.tooltipAndButtonProc1Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// mov edx, ebx
			BytePattern::temp_instance().find_pattern("8B D3 0F B6 04 10 49 8B 0C C7");
			if (BytePattern::temp_instance().has_size(1, "処理ループ１の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test rcx,rcx
				tooltipAndButtonProc2ReturnAddress = address + 0x11;

				Injector::MakeJMP(address, tooltipAndButtonProc2, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc2Injector = true;
			}
		default:
			e.version.tooltipAndButtonProc2Injector = true;
		}

		return e;
	}

	DllError tooltipAndButtonProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// mov ecx, ebx
			BytePattern::temp_instance().find_pattern("8B CB F3 45 0F 10 97 48 08 00 00");
			if (BytePattern::temp_instance().has_size(1, "処理ループ２の文字取得")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test r11, r11
				tooltipAndButtonProc3ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, tooltipAndButtonProc3, true);
			}
			else {
				e.unmatch.tooltipAndButtonProc3Injector = true;
			}
		default:
			e.version.tooltipAndButtonProc3Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= tooltipAndButtonProc1Injector(options);
		result |= tooltipAndButtonProc2Injector(options);
		//result |= tooltipAndButtonProc3Injector(options);

		return result;
	}
}