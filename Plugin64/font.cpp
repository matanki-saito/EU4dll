#include "pch.h"
#include "plugin_64.h"

namespace Font {

	extern "C" {
		void fontBufferHeapZeroClear();
		uintptr_t fontBufferHeapZeroClearReturnAddress;
		uintptr_t heapAllocAddress;
	}

	errno_t fontBufferHeapZeroClearInjector(RunOptions options) {
		switch (options.version) {
		case v1_29_0:
			BytePattern::temp_instance().find_pattern("48 8B 0D 73 A8 A6 00");
			if (BytePattern::temp_instance().has_size(1, "Font buffer heap zero clear")) {
				//heapAllocAddress = HeapAlloc;

				//uintptr_t address = BytePattern::temp_instance().get_first().address();

				//fontBufferHeapZeroClearReturnAddress = address + 15;

				//Injector::MakeJMP(address, fontBufferHeapZeroClear, true);
			}
			else return 1;
			return NOERROR;
		}

		return 1;
	}

	errno_t fontBufferExpansionInjector(RunOptions options) {
		switch (options.version) {
		case v1_29_0:
			BytePattern::temp_instance().find_pattern("B9 68 3D 00 00");
			if (BytePattern::temp_instance().has_size(1, "Font buffer expansion")) {
				// mov ecx, 3D68h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x3), 0x10, true);
			}
			else return 1;
			return NOERROR;
		}

		return 1;
	}

	errno_t fontSizeLimitInjector(RunOptions options) {
		switch (options.version) {
		case v1_29_0:
			BytePattern::temp_instance().find_pattern("41 81 FE 00 00 00 01");
			if (BytePattern::temp_instance().has_size(1, "Font size limit")) {
				// cmp r14d, 1000000h
				Injector::WriteMemory<uint8_t>(BytePattern::temp_instance().get_first().address(0x6), 0x04, true);
			}
			else return 1;
			return NOERROR;
		}

		return 1;
	}

	/*-----------------------------------------------*/

	errno_t Init(RunOptions options) {
		errno_t result = 0;

		BytePattern::LoggingInfo("font etc fix");

		/* ヒープゼロフラグの修正 */
		//result |= heepZero_hook(options);
		/* フォントバッファクリア */
		//result |= bufferClear_hook(options);
		/* フォントバッファ拡張 */
		result |= fontBufferExpansionInjector(options);

		/* フォントサイズの拡張 */
		result |= fontSizeLimitInjector(options);

		return result;
	}
}