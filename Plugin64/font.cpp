#include "pch.h"
#include "plugin_64.h"

namespace Font {

	extern "C" {
		void fontBufferHeapZeroClear();
		uintptr_t fontBufferHeapZeroClearReturnAddress;
		uintptr_t fontBufferHeapZeroClearHeepAllocJmpAddress;
		uintptr_t fontBufferHeapZeroClearHeapJmpAddress;
	}

	DllError fontBufferHeapZeroClearInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
			// mov rcx,cs:hHeap
			BytePattern::temp_instance().find_pattern("48 8B 0D ? ? ? ? 4C 8B C3 33 D2");
			if (BytePattern::temp_instance().has_size(1, "Font buffer heap zero clear")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				
				// mov rcx, {cs:hHeap}
				fontBufferHeapZeroClearHeapJmpAddress = Injector::GetBranchDestination(address + 0x0).as_int();
				// call {{cs:HeapAlloc}}
				fontBufferHeapZeroClearHeepAllocJmpAddress = Injector::GetBranchDestination(address + 0xC).as_int();
				// jz short loc_xxxxx
				fontBufferHeapZeroClearReturnAddress = address + 0x15;

				Injector::MakeJMP(address, fontBufferHeapZeroClear, true);
			} else {
				e.unmatch.fontBufferHeapZeroClearInjector = true;
			}
			break;
		default:
			e.version.fontBufferHeapZeroClearInjector = true;
		}

		return e;
	}

	DllError fontBufferClear1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
			BytePattern::temp_instance().find_pattern("BA 88 3D 00 00 48 8B CF");
			if (BytePattern::temp_instance().has_size(1, "Font buffer clear")) {
				// mov edx, 3D68h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.unmatch.fontBufferClearInjector = true;
			}
			break;
		default:
			e.version.fontBufferClearInjector = true;
		}

		return e;
	}

	DllError fontBufferClear2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
			BytePattern::temp_instance().find_pattern("BA 88 3D 00 00 48 8B 4D 28");
			if (BytePattern::temp_instance().has_size(1, "Font buffer clear")) {
				// mov edx, 3D68h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else {
				e.unmatch.fontBufferClearInjector = true;
			}
			break;
		default:
			e.version.fontBufferClearInjector = true;
		}

		return e;
	}

	DllError fontBufferExpansionInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
			BytePattern::temp_instance().find_pattern("B9 88 3D 00 00");
			if (BytePattern::temp_instance().has_size(1, "Font buffer expansion")) {
				// mov ecx, 3D68h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			} else {
				e.unmatch.fontBufferExpansionInjector = true;
			}
			break;
		default:
			e.version.fontBufferExpansionInjector = true;
		}
		
		return e;
	}

	DllError fontSizeLimitInjector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_0_0:
		case v1_29_1_0:
		case v1_29_2_0:
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
			BytePattern::temp_instance().find_pattern("41 81 FE 00 00 00 01");
			if (BytePattern::temp_instance().has_size(1, u8"Font size limit")) {
				// cmp r14d, 1000000h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x6), 0x04, true);
			} else {
				e.unmatch.fontSizeLimitInjector = true;
			}
			break;
		default:
			e.version.fontSizeLimitInjector = true;
		}

		return e;
	}

	/*-----------------------------------------------*/

	DllError Init(RunOptions options) {
		DllError result = {};

		BytePattern::LoggingInfo(u8"font etc fix");

		/* ヒープゼロフラグの修正 */
		result |= fontBufferHeapZeroClearInjector(options);

		/* フォントバッファクリア1 */
		result |= fontBufferClear1Injector(options);

		/* フォントバッファクリア2 */
		result |= fontBufferClear2Injector(options);

		/* フォントバッファ拡張 */
		result |= fontBufferExpansionInjector(options);

		/* フォントサイズの拡張 */
		result |= fontSizeLimitInjector(options);

		return result;
	}
}