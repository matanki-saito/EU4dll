#include "pch.h"
#include "plugin_64.h"

namespace Localization {
	extern "C" {
		void localizationProc2();
		void localizationProc2V137();
		void localizationProc3();
		void localizationProc3V130();
		void localizationProc4();
		void localizationProc4V130();
		void localizationProc5();
		void localizationProc5V131();
		void localizationProc5V137();
		void localizationProc6();
		void localizationProc6V137();
		void localizationProc7();
		void localizationProc7V131();
		void localizationProc8();
		void localizationProc8V137();

		uintptr_t localizationProc1CallAddress1;
		uintptr_t localizationProc1CallAddress2;
		uintptr_t localizationProc2CallAddress;
		uintptr_t localizationProc2ReturnAddress;
		uintptr_t localizationProc3ReturnAddress;
		uintptr_t localizationProc4ReturnAddress;
		uintptr_t localizationProc5CallAddress;
		uintptr_t localizationProc5ReturnAddress;
		uintptr_t localizationProc6ReturnAddress;
		uintptr_t localizationProc6CallAddress;
		uintptr_t localizationProc7ReturnAddress;
		uintptr_t localizationProc8CallAddress;
		uintptr_t localizationProc8ReturnAddress;

		uintptr_t localizationProc7CallAddress1;
		uintptr_t localizationProc7CallAddress2;

		uintptr_t generateCString;
		uintptr_t concatCString;
		uintptr_t concat2CString;

		uintptr_t year;
		uintptr_t month;
		uintptr_t day;
	}

	DllError localizationProc1Injector(RunOptions options){
		DllError e = {};

		switch (options.version) {
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			// mov     [rsp+arg_10], rbx
			BytePattern::temp_instance().find_pattern("48 89 5C 24 18 55 41 56 41 57 48 83 EC 20 4D 8B F0");
			if (BytePattern::temp_instance().has_size(1, u8"std::basic_string<char>#insertをフック")) {
				localizationProc1CallAddress1 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.localization.unmatchdLocalizationProc1Injector = true;
			}
			break;
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// mov     [rsp+arg_10], rbx
			BytePattern::temp_instance().find_pattern("48 89 5C 24 18 4C 89 74 24 20 41 57 48 83 EC 20");
			if (BytePattern::temp_instance().has_size(1, u8"std::basic_string<char>#insertをフック")) {
				localizationProc1CallAddress1 = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.localization.unmatchdLocalizationProc1Injector = true;
			}
			break;
		case v1_37_0_0:
			break;
		default:
			e.localization.versionLocalizationProc1Injector = true;
		}

		return e;
	}

	void* localizationProc2Call(ParadoxTextObject* p, const char* src, const size_t size) {
		auto text = std::string(src).substr(1) + p->getString();
		p->setString(&text);

		return p;
	}

	DllError localizationProc2Injector(RunOptions options) {
		DllError e = {};

		if (!options.reversingWordsBattleOfArea) return e;

		switch (options.version) {
		case v1_29_4_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 13 70 EB FF");
			if (BytePattern::temp_instance().has_size(1, u8"Battle of areaを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				localizationProc2ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, localizationProc2, true);
			}
			else {
				e.localization.unmatchdLocalizationProc2Injector = true;
			}
			break;
		case v1_30_5_0:
		case v1_30_4_0:
		case v1_30_3_0:
		case v1_30_2_0:
		case v1_30_1_0:
			// mov     rcx, [rdi+30h]
			BytePattern::temp_instance().find_pattern("48 8B 4F 30 48 83 C1 10 48 8B 01");
			if (BytePattern::temp_instance().has_size(2, u8"Battle of areaを逆転させる")) {
				// nop
				uintptr_t address = BytePattern::temp_instance().get_first().address(0x3B);

				// nop
				localizationProc2ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, localizationProc2, true);
			}
			else {
				e.localization.unmatchdLocalizationProc2Injector = true;
			}
			break;
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// mov     rax, [rdi+30h]
			BytePattern::temp_instance().find_pattern("48 8B 47 30 4C 8B 40 28 49 83 C0 10");
			if (BytePattern::temp_instance().has_size(1, u8"Battle of areaを逆転させる")) {
				// nop
				uintptr_t address = BytePattern::temp_instance().get_first().address(0x1D);

				// nop
				localizationProc2ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, localizationProc2, true);
			}
			else {
				e.localization.unmatchdLocalizationProc2Injector = true;
			}
			break;
		case v1_37_0_0:
			// movdqu  xmmword ptr [rbp+Size], xmm0
			BytePattern::temp_instance().find_pattern("F3 0F 7F 45 E8 ? ? ? ? 49 C7 C0 FF FF FF FF 0F 1F 44 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"Battle of areaを逆転させる")) {
				// lea     rdx, [rbp+Src]
				uintptr_t address = BytePattern::temp_instance().get_first().address(0x48);

				// nop
				localizationProc2ReturnAddress = address + 0x1A;

				localizationProc2CallAddress = (uintptr_t)localizationProc2Call;

				Injector::MakeJMP(address, localizationProc2V137, true);

			}
			else {
				e.localization.unmatchdLocalizationProc2Injector = true;
			}
			break;
		default:
			BytePattern::LoggingInfo(u8"Battle of areaを逆転させる [NG]");
			e.localization.versionLocalizationProc2njector = true;
		}

		return e;
	}


	DllError localizationProc3Injector(RunOptions options) {
		DllError e = {};

		std::string pattern;

		switch (options.version) {
		case v1_29_4_0:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8B D0 49 8B CC E8 0B 1F");
			if (BytePattern::temp_instance().has_size(1, u8"MDEATH_HEIR_SUCCEEDS heir nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				localizationProc3ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, localizationProc3, true);
			}
			else {
				e.localization.unmatchdLocalizationProc3Injector = true;
			}
			break;
		case v1_30_1_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 A3 A1 DD FF";
			goto JMP;
		case v1_30_2_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 43 A1 DD FF";
			goto JMP;
		case v1_30_3_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 53 A1 DD FF";
			goto JMP;
		case v1_30_4_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 F3 A1 DD FF";
			goto JMP;
		case v1_30_5_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 D3 9C DD FF";
			goto JMP;
		case v1_31_2_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 D3 58 DC FF";
		JMP:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern(pattern);
			if (BytePattern::temp_instance().has_size(1, u8"MDEATH_HEIR_SUCCEEDS heir nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				localizationProc3ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, localizationProc3V130, true);
			}
			else {
				e.localization.unmatchdLocalizationProc3Injector = true;
			}
			break;
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
		case v1_37_0_0:
			// 処理は不要になった
			break;
		default:
			BytePattern::LoggingInfo(u8"MDEATH_HEIR_SUCCEEDS heir nameを逆転させる [NG]");
			e.localization.versionLocalizationProc3njector = true;
		}

		return e;
	}

	DllError localizationProc4Injector(RunOptions options) {
		DllError e = {};
		std::string pattern;
		int offset = 0;

		switch (options.version) {
		case v1_29_4_0:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern("49 83 C9 FF 45 33 C0 48 8B D0 49 8B CC E8 B8 1E");
			if (BytePattern::temp_instance().has_size(1, u8"MDEATH_REGENCY_RULE heir nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				localizationProc4ReturnAddress = address + 0x12;

				// call {xxxxx} std::basic_string<char>#appendをフック。直接はバイナリパターンが多すぎでフックできなかった
				localizationProc1CallAddress2 = Injector::GetBranchDestination(address + 0xD).as_int();

				// Injector::MakeJMP(address, wordOrderProc4, true);
			}
			else {
				e.localization.unmatchdLocalizationProc4Injector = true;
			}
			break;
		case v1_30_1_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 46 A1 DD FF";
			goto JMP;
		case v1_30_2_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 E6 A0 DD FF";
			goto JMP;
		case v1_30_3_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 F6 A0 DD FF";
			goto JMP;
		case v1_30_4_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 ? A1 DD FF";
			goto JMP;
		case v1_30_5_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 95 9E DD FF";
			goto JMP;
		case v1_31_2_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 F8 5B DC FF";
			goto JMP;
		case v1_31_3_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 08 63 DC FF";
			goto JMP;
		case v1_31_4_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 88 7B DC FF";
			goto JMP;
		case v1_31_5_0:
			// 1.31.5.1
			//pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 D8 5E DC FF";
			// 1.31.5.2
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 88 5E DC FF";
			goto JMP;
		case v1_31_6_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 49 8B CF E8 D8 5D DC FF";
			goto JMP;
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
			offset = 0x3C;
			pattern = "48 8B D8 48 8B 8E 70 19 00 00 48 89 8D A0 00 00 00 45 33 C9 45 33 C0 33 D2 48 8D 8D A0 00 00 00 E8 ? ? ? ? 4C 8B C8 48 89 7C 24 38 48 89 5C 24 28";
			goto JMP;
		case v1_34_2_0:
			offset = 0x3C;
			pattern = "48 8B D8 48 8B 8E 88 18 00 00 48 89 8D A0 00 00 00 45 33 C9 45 33 C0 33 D2 48 8D 8D A0 00 00 00 E8 ? ? ? ? 4C 8B C8";
			goto JMP;
		case v1_35_1_0:
			offset = 0x3C;
			pattern = "48 8B D8 48 8B 8E A8 18 00 00 48 89 8D A0 00 00 00 45 33 C9 45 33 C0 33 D2 48 8D 8D A0 00 00 00 E8 ? ? ? ? 4C 8B C8";
			goto JMP;
		case v1_36_0_0:
			offset = 0x3C;
			pattern = "48 8B D8 48 8B 8E D8 18 00 00 48 89 8D 90 00 00 00 45 33 C9 45 33 C0 33 D2 48 8D 8D 90 00 00 00 E8 ? ? ? ? 4C 8B";

			JMP:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern(pattern);
			if (BytePattern::temp_instance().has_size(1, u8"MDEATH_REGENCY_RULE heir nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address(offset);

				// nop
				localizationProc4ReturnAddress = address + 0x12;

				// call {xxxxx} std::basic_string<char>#appendをフック。直接はバイナリパターンが多すぎでフックできなかった
				localizationProc1CallAddress2 = Injector::GetBranchDestination(address + 0xD).as_int();

				Injector::MakeJMP(address, localizationProc4V130, true);
			}
			else {
				e.localization.unmatchdLocalizationProc4Injector = true;
			}
			break;
		case v1_37_0_0:
			// 処理は不要になった
			break;
		default:
			BytePattern::LoggingInfo(u8"MDEATH_REGENCY_RULE heir nameを逆転させる [NG]");
			e.localization.versionLocalizationProc4Injector = true;
		}

		return e;
	}

	void* localizationProc5Call(ParadoxTextObject* p1, ParadoxTextObject *p2) {
		// p1 = "Reimu", p2 = " ¿Hakurei"
	
		auto first = p1->getString();
		auto second = p2->getString();

		if (second.length() >= 3 && second.at(1) == (char)0xBF) { // 0xBF = 逆疑問符
			auto text = second.substr(2) + first; // "HakureiReimu"
			p1->setString(&text);
		}
		else {
			// default
			auto text = first + second; // "Reimu Hakurei"
			p1->setString(&text);
		}

		return p1;
	}

	DllError localizationProc5Injector(RunOptions options) {
		DllError e = {};
		std::string pattern;
		int offset = 0;

		switch (options.version) {
		case v1_29_4_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CF E8 27 41";
			goto JMP;
		case v1_30_1_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CF E8 27 1D";
			goto JMP;
		case v1_30_2_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CF E8 B7 1D 91 FF";
			goto JMP;
		case v1_30_3_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CF E8 C7 1D 91 FF";
			goto JMP;
		case v1_30_4_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CF E8 ? 1D 91 FF";
			goto JMP;
		case v1_30_5_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CF E8 ? FF 90 FF";
		JMP:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern(pattern);
			if (BytePattern::temp_instance().has_size(1, u8"nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				localizationProc5ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, localizationProc5, true);
			}
			else {
				e.localization.unmatchdLocalizationProc5Injector = true;
			}
			break;
		case v1_31_2_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 83 BA 76 FF";
			goto JMP2;
		case v1_31_3_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 23 C1 76 FF";
			goto JMP2;
		case v1_31_4_0:
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 33 C0 76 FF";
			goto JMP2;
		case v1_31_5_0:
			// 1.31.5.0
			// pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 63 70 76 FF";
			// 1.31.5.1
			//pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 03 6F 76 FF";
			// 1.31.5.2
			pattern = "49 83 C9 FF 45 33 C0 48 8B D0 48 8B CB E8 73 81 76 FF";
			goto JMP2;
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			pattern = "48 8B 4F 68 48 8B 01 FF 50 08 84 C0 74 5F 48 8B 07";
			offset = 0x40;
		JMP2:
			// or      r9, 0FFFFFFFFFFFFFFFFh
			BytePattern::temp_instance().find_pattern(pattern);
			if (BytePattern::temp_instance().has_size(1, u8"nameを逆転させる")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address(offset);

				// nop
				localizationProc5ReturnAddress = address + 0x12;

				Injector::MakeJMP(address, localizationProc5V131, true);
			}
			else {
				e.localization.unmatchdLocalizationProc5Injector = true;
			}
			break;
		case v1_37_0_0:
			// mov     rdx, [rdi+68h]
			BytePattern::temp_instance().find_pattern("48 8B 57 68 48 83 C2 08 48 89 75 B8 48 C7 45 D0 0F 00 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"nameを逆転させる")) {
				// lea     rdx, [rbp+Src]
				uintptr_t address = BytePattern::temp_instance().get_first().address(0x40);

				// mov     [rbp+var_50], 1
				localizationProc5ReturnAddress = address + 0x1A;

				localizationProc5CallAddress = (uintptr_t)localizationProc5Call;

				Injector::MakeJMP(address, localizationProc5V137, true);
			}
			else {
				e.localization.unmatchdLocalizationProc5Injector = true;
			}
			break;
		default:
			e.localization.versionLocalizationProc5Injector = true;
			BytePattern::LoggingInfo(u8"nameを逆転させる [NG]");
		}

		return e;
	}

	void* localizationProc6Call(ParadoxTextObject* p1, ParadoxTextObject* p2, ParadoxTextObject* p3) {
		// p2= '4月 ,' p3 = '1447'

		auto text = p3->getString() + std::string("\x0F") + p2->getString().substr(0,p2->len-2); // 1447 + 年 + 4月

		p1->len = 0;
		p1->len2 = 0;
		p1->setString(&text);

		return p1;
	}

	DllError localizationProc6Injector(RunOptions options) {
		DllError e = {};
		std::string pattern;
		int offset = 0;

		switch (options.version) {
		case v1_29_4_0:
			pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 4F FA B4 FF";
			goto JMP;
		case v1_30_1_0:
			pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 0F 7B AD";
			goto JMP;
		case v1_30_2_0:
			pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 AF 7B AD";
			goto JMP;
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
			pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 ? ? AD";
			goto JMP;
		case v1_31_2_0:
			pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 DF 9C A6";
			goto JMP;
		case v1_31_3_0:
			pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 CF AD A6";
			goto JMP;
		case v1_31_4_0:
			pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 3F AD A6";
			goto JMP;
		case v1_31_5_0:
			// 1.31.5.1
			//pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 7F 61 A6";
			// 1.31.5.2
			pattern = "90 49 83 C9 FF 45 33 C0 48 8B D0 48 8B CE E8 8F 74 A6";
			goto JMP;
		case v1_31_6_0:
		case v1_32_0_1:
			pattern = "4C 8D 05 ? ? ? ? 48 8D 55 DF 48 8D 4D BF E8 ? ? ? ? 90";
			offset = 0x26;
		JMP:
			// nop
			BytePattern::temp_instance().find_pattern(pattern);
			if (BytePattern::temp_instance().has_size(1, u8"M, Y → Y年M")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address(offset);

				// nop
				localizationProc6ReturnAddress = address + 0x13;

				Injector::MakeJMP(address, localizationProc6, true);
			}
			else {
				e.localization.unmatchdLocalizationProc6Injector = true;
			}
			break;
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			break;
		case v1_37_0_0:
			// lea     r8, [rbp+57h+var_78]
			BytePattern::temp_instance().find_pattern("4C 8D 45 DF 48 8D 55 BF 48 8D 4D 1F");
			if (BytePattern::temp_instance().has_size(3, u8"M, Y → Y年M")) {

				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				localizationProc6ReturnAddress = address + 0x11;

				localizationProc6CallAddress = (uintptr_t)localizationProc6Call;

				Injector::MakeJMP(address, localizationProc6V137, true);
			}
			else {
				e.localization.unmatchdLocalizationProc6Injector = true;
			}
			break;
			break;
		default:
			BytePattern::LoggingInfo(u8"M, Y → Y年M [NG]");
			e.localization.versionLocalizationProc6Injector = true;
		}

		return e;
	}

	DllError localizationProc7Injector(RunOptions options) {
		DllError e = {};
		std::string pattern;

		switch (options.version) {
		case v1_29_4_0:
			pattern = "90 4C 8D 44 24 48 48 8D 54 24 28 48 8D 4D E8 E8 65 9D";
			goto JMP;
		case v1_30_1_0:
			pattern = "90 4C 8D 44 24 48 48 8D 54 24 28 48 8D 4D E8 E8 65 6A";
			goto JMP;
		case v1_30_2_0:
			pattern = "90 4C 8D 44 24 48 48 8D 54 24 28 48 8D 4D E8 E8 45 6B";
			goto JMP;
		case v1_30_3_0:
		case v1_30_4_0:
			pattern = "90 4C 8D 44 24 48 48 8D 54 24 28 48 8D 4D E8 E8 ? 6B";
			goto JMP;
		case v1_30_5_0:
			pattern = "90 4C 8D 44 24 48 48 8D 54 24 28 48 8D 4D E8 E8 05 61 B1 FF";
		JMP:
			// nop
			BytePattern::temp_instance().find_pattern(pattern);
			if (BytePattern::temp_instance().has_size(1, u8"D M, Y → Y年MD日")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				localizationProc7CallAddress1 = Injector::GetBranchDestination(address + 0xF).as_int();
				localizationProc7CallAddress2 = Injector::GetBranchDestination(address + 0x20).as_int();

				// nop
				localizationProc7ReturnAddress = address + 0x5E;

				Injector::MakeJMP(address, localizationProc7, true);
			}
			else {
				e.localization.unmatchdLocalizationProc7Injector = true;
			}
			break;
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
		case v1_37_0_0:
			/* 処理は不要になった。tmm_l_english.ymlのLONG_EU3_DATE_STRINGで代用される*/
			break;

		default:
			BytePattern::LoggingInfo(u8"D M, Y → Y年MD日 [NG]");
			e.localization.versionLocalizationProc7Injector = true;
		}

		return e;
	}

	void* localizationProc8Call(ParadoxTextObject* p1, ParadoxTextObject* p2, ParadoxTextObject* p3) {
		// p2= '4月 ' p3 = '1447'

		auto text = p3->getString() + std::string("\x0F") + p2->getString().substr(0, p2->len-1); // 1447 + 年 + 4月

		p1->len = 0;
		p1->len2 = 0;
		p1->setString(&text);

		return p1;
	}

	DllError localizationProc8Injector(RunOptions options) {
		DllError e = {};
		std::string pattern;

		switch (options.version) {
		case v1_29_4_0:
			pattern = "90 4C 8D 45 A7 48 8D 55 0F 48 8D 4D EF E8 31 02";
			goto JMP;
		case v1_30_1_0:
			pattern = "90 4C 8D 45 A7 48 8D 55 0F 48 8D 4D EF E8 81 E1";
			goto JMP;
		case v1_30_2_0:
			pattern = "90 4C 8D 45 A7 48 8D 55 0F 48 8D 4D EF E8 61 E2";
			goto JMP;
		case v1_30_3_0:
		case v1_30_4_0:
			pattern = "90 4C 8D 45 A7 48 8D 55 0F 48 8D 4D EF E8 ? E2";
			goto JMP;
		case v1_30_5_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			pattern = "90 4C 8D 45 A7 48 8D 55 0F 48 8D 4D EF";
			JMP:
			// nop 
			BytePattern::temp_instance().find_pattern(pattern);
			if (BytePattern::temp_instance().has_size(1, u8"M Y → Y年M")) {
				// mov     r8d, 1
				uintptr_t address = BytePattern::temp_instance().get_first().address() - 0x16;

				generateCString = Injector::GetBranchDestination(address + 0x11).as_int();
				concatCString = Injector::GetBranchDestination(address + 0x23).as_int();
				concat2CString = Injector::GetBranchDestination(address + 0x33).as_int();

				// nop
				localizationProc8ReturnAddress = address + 0x38;

				Injector::MakeJMP(address, localizationProc8, true);
			}
			else {
				e.localization.unmatchdLocalizationProc8Injector = true;
			}
			break;
		case v1_37_0_0:
			// nop
			BytePattern::temp_instance().find_pattern("90 4C 8D 44 24 40 48 8B D0 48 8B CF E8 ? ? ? ? 90");
			if (BytePattern::temp_instance().has_size(2, u8"M Y → Y年M")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// nop
				localizationProc8ReturnAddress = address + 0x11;

				localizationProc8CallAddress = (uintptr_t)localizationProc8Call;

				Injector::MakeJMP(address, localizationProc8V137, true);
			}
			else {
				e.localization.unmatchdLocalizationProc8Injector = true;
			}
			break;
		default:
			BytePattern::LoggingInfo(u8"M Y → Y年M [NG]");
			e.localization.versionLocalizationProc8Injector = true;
		}

		return e;
	}

	DllError localizationProc9Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
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
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
			BytePattern::temp_instance().find_pattern("20 2D 20 00 4D 4F 4E 54 48 53 00 00");
			if (BytePattern::temp_instance().has_size(1, u8"Replace space")) {
				intptr_t address = BytePattern::temp_instance().get_first().address();
				Injector::WriteMemory<BYTE>(address+0, 0x20,true);
				Injector::WriteMemory<BYTE>(address+1, 0x2D, true);
				Injector::WriteMemory<BYTE>(address+2, 0x20, true);
			}
			else {
				e.localization.unmatchdLocalizationProc9Injector = true;
			}
			break;
		case v1_36_0_0:
		case v1_37_0_0:
			// 副作用が大きかったのでやめた
			break;
		default:
			BytePattern::LoggingInfo(u8"Replace space [NG]");
			e.localization.versionLocalizationProc9Injector = true;
		}

		return e;
	}

	ParadoxTextObject _year;
	ParadoxTextObject _month;
	ParadoxTextObject _day;

	DllError Init(RunOptions options) {
		DllError result = {};

		_day.t.text[0] = 0xE;
		_day.t.text[1] = '\0';
		_day.len = 1;
		_day.len2 = 0xF;

		_year.t.text[0] = 0xF;
		_year.t.text[1] = '\0';
		_year.len = 1;
		_year.len2 = 0xF;

		_month.t.text[0] = 7;
		_month.t.text[1] = '\0';
		_month.len = 1;
		_month.len2 = 0xF;
		
		year = (uintptr_t) &_year;
		month = (uintptr_t)&_month;
		day = (uintptr_t)&_day;

		// 関数アドレス取得
		result |= localizationProc1Injector(options);

		// Battle of areaを逆転させる
		// 確認方法）敵軍と戦い、結果のポップアップのタイトルを確認する
		result |= localizationProc2Injector(options);

		// MDEATH_HEIR_SUCCEEDS heir nameを逆転させる
		// 確認方法）後継者が成人している状態で君主のツールチップを確認する
		result |= localizationProc3Injector(options);

		// MDEATH_REGENCY_RULE heir nameを逆転させる
		// 確認方法）後継者が成人していない状態で君主のツールチップを確認する
		// ※localizationProc1CallAddress2のhookもこれで実行している
		result |= localizationProc4Injector(options);

		// nameを逆転させる
		// 確認方法）sub modを入れた状態で日本の大名を選択する。大名の名前が逆転しているかを確認する
		result |= localizationProc5Injector(options);

		// 年号の表示がM, YからY年M
		// 確認方法）オスマンで画面上部の停戦アラートのポップアップの年号を確認する
		result |= localizationProc6Injector(options);

		// 年号の表示がD M, YからY年MD日になる
		// 確認方法）スタート画面のセーブデータの日付を見る
		result |= localizationProc7Injector(options);

		// 年号の表示がM YからY年Mになる
		// 確認方法）外交官のポップアップを表示し、年号を確認する
		result |= localizationProc8Injector(options);

		// スペースを変更
		result |= localizationProc9Injector(options);

		return result;
	}
}