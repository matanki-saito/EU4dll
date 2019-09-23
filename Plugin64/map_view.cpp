#include "pch.h"
#include "plugin_64.h"

namespace MapView {
	extern "C" {
		void mapViewProc1();
		void mapViewProc2();
		void mapViewProc3();
		void mapViewProc4();
		uintptr_t mapViewProc1ReturnAddress;
		uintptr_t mapViewProc2ReturnAddress;
		uintptr_t mapViewProc3ReturnAddress;
		uintptr_t mapViewProc3CallAddress;
		uintptr_t mapViewProc4ReturnAddress;
		uintptr_t mapViewProc4CallAddress;
	}

	DllError mapViewProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// movzx   eax, byte ptr [rax+r8]
			BytePattern::temp_instance().find_pattern("42 0F B6 04 00 4C 8B 1C C7 4C 89 5D 38");
			if (BytePattern::temp_instance().has_size(1, "処理ループ２の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test    r11, r11
				mapViewProc1ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, mapViewProc1, true);
			}
			else {
				e.unmatch.mapViewProc1Injector = true;
			}
		default:
			e.version.mapViewProc1Injector = true;
		}

		return e;
	}

	DllError mapViewProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// lea     r9, [r12+100h]
			BytePattern::temp_instance().find_pattern("4D 8D 8C 24 00 01 00 00 42 0F B6 04 38 4D 8B 24 C1");
			if (BytePattern::temp_instance().has_size(1, "処理ループ１の文字取得処理")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// test    r12, r12
				mapViewProc2ReturnAddress = address + 0x11;

				Injector::MakeJMP(address, mapViewProc2, true);
			}
			else {
				e.unmatch.mapViewProc2Injector = true;
			}
		default:
			e.version.mapViewProc2Injector = true;
		}

		return e;
	}

	DllError mapViewProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// movzx   r8d, byte ptr [rax+r15]
			BytePattern::temp_instance().find_pattern("46 0F B6 04 38 BA 01 00 00 00 48 8D 4C 24 40");
			if (BytePattern::temp_instance().has_size(1, "処理ループ１の文字コピー")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				mapViewProc3CallAddress = Injector::GetBranchDestination(address + 0x0F).as_int();

				// nop
				mapViewProc3ReturnAddress = address + 0x14;

				Injector::MakeJMP(address, mapViewProc3, true);
			}
			else {
				e.unmatch.mapViewProc3Injector = true;
			}
		default:
			e.version.mapViewProc3Injector = true;
		}

		return e;
	}

	// これはwin32のときはmiscにあったが統合した。Proc1～3とは別のProcにinjectしている
	// この処理はwin32のときは独立したprocであったが、win64ではinline展開されている。
	// この処理の下の方では文字取得（49 8B 14 C7 48 85 D2 74  09 66 83 7A 06 0）があるので
	// 別途そちらも修正する必要がある
	DllError mapViewProc4Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// movsx ecx, byte ptr [rdi + rbx]
			BytePattern::temp_instance().find_pattern("0F BE 0C 1F E8 72 B6 98 00 88 04 1F");
			if (BytePattern::temp_instance().has_size(1, "マップ文字の大文字化キャンセル")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				mapViewProc4CallAddress = Injector::GetBranchDestination(address + 0x04).as_int();

				// cmp byte ptr [rdi + r14] , 0
				mapViewProc4ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, mapViewProc4, true);
			}
			else {
				e.unmatch.mapViewProc4Injector = true;
			}
		default:
			e.version.mapViewProc4Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapViewProc1Injector(options);
		result |= mapViewProc2Injector(options);
		result |= mapViewProc3Injector(options);
		result |= mapViewProc4Injector(options);

		return result;
	}
}