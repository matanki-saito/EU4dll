#include "pch.h"
#include "plugin_64.h"

namespace MapView {
	extern "C" {
		void mapViewProc1();
		uintptr_t mapViewProc1ReturnAddress;
	}

	DllError mapViewProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_1_0:
			// movzx   eax, byte ptr [rbx+rax]
			BytePattern::temp_instance().find_pattern("0F B6 04 03 4D 8B 9C C7 00 01 00 00");
			if (BytePattern::temp_instance().has_size(1, "ˆ—ƒ‹[ƒv‚Q‚Ì•¶šæ“¾ˆ—")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// movss   dword ptr [rbp+88h], xmm3
				mapViewProc1ReturnAddress = address + 0x13;

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

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= mapViewProc1Injector(options);

		return result;
	}
}