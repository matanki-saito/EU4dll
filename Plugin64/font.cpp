#include "pch.h"
#include "plugin_64.h"

namespace Font {

	extern "C" {
		void fontBufferHeapZeroClear();
		uintptr_t fontBufferHeapZeroClearReturnAddress;
		uintptr_t fontBufferHeapZeroClearHeepAllocJmpAddress;
		uintptr_t fontBufferHeapZeroClearHeapJmpAddress;
	}

	errno_t fontBufferHeapZeroClearInjector(RunOptions options) {
		switch (options.version) {
		case v1_29_0_0:
		case v1_29_1_0:
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
			}
			else return 1;
			return NOERROR;
		}

		return 1;
	}

	errno_t fontBufferExpansionInjector(RunOptions options) {
		switch (options.version) {
		case v1_29_0_0:
		case v1_29_1_0:
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
		case v1_29_0_0:
		case v1_29_1_0:
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
		result |= fontBufferHeapZeroClearInjector(options);
		/* フォントバッファクリア */
		//result |= bufferClear_hook(options);
		/* フォントバッファ拡張 */
		result |= fontBufferExpansionInjector(options);

		/* フォントサイズの拡張 */
		result |= fontSizeLimitInjector(options);

		return result;
	}
}