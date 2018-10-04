#include "stdinc.h"
#include "byte_pattern.h"

namespace Font {

	/*-----------------------------------------------*/

	errno_t heepZero_hook(EU4Version version) {
		std::string desc = "heep zero";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("59 85 C0 74 15 56 6A 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// push 0
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x7), 0x08, true);
				return NOERROR;
			}
			else return EU4_ERROR1;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t bufferClear_hook(EU4Version version) {
		
		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			/* ランチャー */
			byte_pattern::temp_instance().find_pattern("68 20 28 00 00 8B 45");
			if (byte_pattern::temp_instance().has_size(1,"buffer clear launcher 1")) {
				// push 2820h
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
			}
			else return EU4_ERROR1;

			/* ランチャー */
			byte_pattern::temp_instance().find_pattern("68 20 28 00 00 56 E8");
			if (byte_pattern::temp_instance().has_size(1, "buffer clear launcher 2")) {
				// push 2820h
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
			}
			else return EU4_ERROR1;

			/* 本体 */
			byte_pattern::temp_instance().find_pattern("68 50 28 00 00 8B 45");
			if (byte_pattern::temp_instance().has_size(1, "buffer clear main 1")) {
				// push 2850h
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
			}
			else return EU4_ERROR1;

			/* 本体 */
			byte_pattern::temp_instance().find_pattern("68 50 28 00 00 56 E8");
			if (byte_pattern::temp_instance().has_size(1, "buffer clear main 2")) {
				// push 2850h
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
			}
			else return EU4_ERROR1;

			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t fontSize_hook(EU4Version version) {
		std::string desc = "buffer clear";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("81 FE 00 00 00 01");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// cmp esi, 10000000h
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x5), 0x04, true);
				return NOERROR;
			}
			else return EU4_ERROR1;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t bufferExp_hook(EU4Version version) {

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
			/* ランチャー */
			byte_pattern::temp_instance().find_pattern("68 20 28 00 00 E8 ? ? ? ? 83");
			if (byte_pattern::temp_instance().has_size(1, "buffer exp launcher")) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
			}
			else return EU4_ERROR1;

			/* 本体 */
			byte_pattern::temp_instance().find_pattern("68 50 28 00 00 E8 ? ? ? ? 83");
			if (byte_pattern::temp_instance().has_size(1, "buffer main launcher")) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
			}
			else return EU4_ERROR1;

			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("font etc fix");

		/* ヒープゼロフラグの修正 */
		result |= heepZero_hook(version);
		/* フォントバッファクリア */
		result |= bufferClear_hook(version);
		/* フォントバッファ拡張 */
		result |= bufferExp_hook(version);
		/* フォントサイズの拡張 */
		result |= fontSize_hook(version);

		return result;
	}
}