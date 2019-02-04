#include "stdinc.h"
#include "byte_pattern.h"

/*  menubar date format fix */
/*  issue66 : https://github.com/matanki-saito/EU4dll/issues/66 */
/*  issue73 : https://github.com/matanki-saito/EU4dll/issues/73 */
namespace DateFormat {

	/*-----------------------------------------------*/

	errno_t menubar_dateFix_hook(EU4Version version) {
		std::string desc = "menu bar date fix";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("64 20 77 20 6D");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// d w mw w y
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x79, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x0F, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(4), 0x6D, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(5), 0x77, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(6), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(7), 0x64, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(8), 0x20, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(9), 0x0E, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(10), 0x00, true);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/
	
	uintptr_t issue66_copyBuff1_v127_start;
	uintptr_t issue66_copyBuff2_v127_start;

	/*-----------------------------------------------*/

	errno_t copyBuffFunc_hook(EU4Version version) {
		std::string desc = "copyBuffFunc";

		switch (version) {
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("83 EC 20 56 FF 75 0C 8B F1 FF 75 08");
			/* 2つとも取得する */
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// sub esp,20h
				issue66_copyBuff1_v127_start = byte_pattern::temp_instance().get_first().address(-0x18);
				// sub esp,20h
				issue66_copyBuff2_v127_start = byte_pattern::temp_instance().get_first().address(-0x18);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_27_X:
		case v1_28_X:
			byte_pattern::temp_instance().find_pattern("83 EC 20 56 FF 75 0C 8B D1 C7 45");
			/* 2つとも取得する */
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				// sub esp,20h
				issue66_copyBuff1_v127_start = byte_pattern::temp_instance().get_first().address(-0x18);
				// sub esp,20h
				issue66_copyBuff2_v127_start = byte_pattern::temp_instance().get_first().address(-0x18);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_26_X:
		case v1_25_X:
			/* 対応しない */
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue66_createBuff_v127_start;

	/*-----------------------------------------------*/

	errno_t createBuffFunc_hook(EU4Version version) {
		std::string desc = "createBuffFunc";

		switch (version) {
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("83 EC 28 56 8B F1 89 75 EC 57 C7 46 10");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// sub esp,28h
				issue66_createBuff_v127_start = byte_pattern::temp_instance().get_first().address(-0x18);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_27_X:
		case v1_28_X:
		
			byte_pattern::temp_instance().find_pattern("83 EC 28 56 8B F1 89 75 EC 57 C7 46");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// sub esp,28h
				issue66_createBuff_v127_start = byte_pattern::temp_instance().get_first().address(-0x18);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_26_X:
		case v1_25_X:
			/* 対応しない */
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue66_copyText_v127_start;

	/*-----------------------------------------------*/

	errno_t copyText_hook(EU4Version version) {
		std::string desc = "copyText";

		switch (version) {
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("55 8B EC 53 8B 5D 08 56 8B F1 85 DB 74 57");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				// push ebp
				issue66_copyText_v127_start = byte_pattern::temp_instance().get(1).address();
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_26_X:
		case v1_25_X:
			/* 対応しない */
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	union T {
		char text[0x10];
		char* p;
	};

	typedef struct V {
		union T t;
		int len;
		int len2;
	} Vs;

	V *year;
	V *day;
	V *month;

	uintptr_t issue66_YMD_v127_end;
	__declspec(naked) void issue66_YMD_v127_start() {
		__asm {

			// 日をテキストバッファに変換
			push    edi;
			lea     ecx, dword ptr [ebp - 0xA0 ];
			mov     byte ptr[ebp - 0x4], 3;
			call    issue66_createBuff_v127_start;

			// テキストバッファにyearを結合する
			mov     byte ptr[ebp - 0x4], 4;
			push    year;
			lea     ecx, dword ptr [ebp - 0x88];
			push    ecx;
			mov     ecx, esi;
			call    issue66_copyBuff2_v127_start;

			//バッファに月を結合する
			lea     ecx, dword ptr [ebp - 0xB8];
			mov     byte ptr[ebp - 0x4], 5;
			push    ecx;
			lea     ecx, dword ptr [ebp - 0x70];
			push    ecx;
			mov     ecx, eax;
			call    issue66_copyBuff1_v127_start;

			// バッファに日を結合する
			lea ecx,    dword ptr[ebp - 0xA0];
			push ecx;
			lea     ecx, dword ptr [ebp - 0x40];
			mov     byte ptr[ebp - 0x4], 7;
			push    ecx;
			mov     ecx, eax;
			call    issue66_copyBuff2_v127_start;

			// バッファに「日」を結合する
			push    day;
			lea     ecx, dword ptr[ebp - 0x58];
			mov     byte ptr[ebp - 0x4], 6;
			push    ecx;
			mov     ecx, eax;
			call    issue66_copyBuff1_v127_start;

			push issue66_YMD_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fixD_MC_Y_hook(EU4Version version) {
		std::string desc = "fix D M, Y format";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("57 8D 8D 60 FF FF FF C6 45 FC 03");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// push edi
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue66_YMD_v127_start);

				// push 0xFFFFFFFF
				issue66_YMD_v127_end = byte_pattern::temp_instance().get_first().address(0x60);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_26_X:
		case v1_25_X:
			/* 対応しない */
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue66_YM_v127_end;
	__declspec(naked) void issue66_YM_v127_start() {
		__asm {
			mov     esi, eax

			push    year;
			lea     ecx, dword ptr[ebp - 0x30];
			mov     byte ptr[ebp - 0x4], 3;
			push    ecx;
			mov     ecx, esi;
			call    issue66_copyBuff2_v127_start;

			lea     eax,dword ptr[ebp - 0x60];
			push eax;
			lea     eax, dword ptr [ebp - 0x48];
			mov     byte ptr[ebp - 0x4], 2;
			push    eax;
			lea     ecx, dword ptr[ebp - 0x30];
			call    issue66_copyBuff1_v127_start;

			push issue66_YM_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fixMC_Y_hook(EU4Version version) {
		std::string desc = "fix M, Y format";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("8B F0 8D 4D EC 6A 00 8D 45 A0");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov esi,eax
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x20), issue66_YM_v127_start);

				// push 0xFFFFFFFF
				issue66_YM_v127_end = byte_pattern::temp_instance().get_first().address(0x20 + 0x27);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_26_X:
		case v1_25_X:
			/* 対応しない */
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue66_YSM_v127_end;
	__declspec(naked) void issue66_YSM_v127_start() {
		__asm {
			mov     byte ptr[ebp - 0x4], 2;
			push    year;
			lea     eax, dword ptr[ebp - 0x44];
			push    eax;
			mov ecx, esi;
			call    issue66_copyBuff2_v127_start;

			lea  ecx , dword ptr[ebp - 0x5C];
			push ecx;
			mov     esi, dword ptr [ebp + 0x8]; // arg_0
			mov     ecx, eax;
			push    esi;
			mov     byte ptr[ebp - 0x4], 3;
			call    issue66_copyBuff2_v127_start;

			push issue66_YSM_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fixM_Y_hook(EU4Version version) {
		std::string desc = "fix M Y format";

		switch (version) {
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("8D 45 D4 C6 45 FC 02 50 8D 55 A4");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea eax, [ebp+var_2C]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue66_YSM_v127_start);

				// mov eax, [ebp+var_30]
				issue66_YSM_v127_end = byte_pattern::temp_instance().get_first().address(0x27);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("8D 45 D4 C6 45 FC 02 50 8D 45 BC 50 8D 4D A4");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// lea eax, [ebp+var_2C]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue66_YSM_v127_start);

				// mov eax, [ebp+var_30]
				issue66_YSM_v127_end = byte_pattern::temp_instance().get_first().address(0x24);
			}
			else return EU4_ERROR1;
			return NOERROR;
		case v1_26_X:
		case v1_25_X:
			/* 対応しない */
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t issue66_copy_func;

	/*-----------------------------------------------*/

	uintptr_t issue66_YYYYdMMdDD_1_v127_end;
	__declspec(naked) void issue66_YYYYdMMdDD_1_v127_start() {
		__asm {
			push 0xFFFFFFFF;
			push 0;
			push year;

			push issue66_YYYYdMMdDD_1_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t issue66_YYYYdMMdDD_2_v127_end;
	__declspec(naked) void issue66_YYYYdMMdDD_2_v127_start() {
		__asm {
			push 0xFFFFFFFF;
			push 0;
			push month;

			push issue66_YYYYdMMdDD_2_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	uintptr_t issue66_YYYYdMMdDD_3_v127_end;
	__declspec(naked) void issue66_YYYYdMMdDD_3_v127_start() {
		__asm {
			push 0xFFFFFFFF;
			push 0;
			push day;
			mov  ecx, edi;
			call issue66_copy_func;
			mov     ecx, [ebp - 0x1C]

			push issue66_YYYYdMMdDD_3_v127_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fixYYYYdMMdDD_hook(EU4Version version) {
		std::string desc = "fix YYYY.MM.DD format";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
			byte_pattern::temp_instance().find_pattern("8B CF E8 DE 37 C2 FF 53 8D 4D D0");
			if (byte_pattern::temp_instance().has_size(1, desc + " Year")) {
				// push 0xFFFFFFFF
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x9), issue66_YYYYdMMdDD_1_v127_start);

				// mov ecx,edi
				issue66_YYYYdMMdDD_1_v127_end = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("8B CF E8 97 37 C2 FF FF 75 E8 8D 4D D0");
			if (byte_pattern::temp_instance().has_size(1, desc + " Month")) {
				// push 0xFFFFFFFF
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x9), issue66_YYYYdMMdDD_2_v127_start);

				// mov ecx,edi
				issue66_YYYYdMMdDD_2_v127_end = byte_pattern::temp_instance().get_first().address();

				// mov ecx,[ebp+var_1C]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x25), issue66_YYYYdMMdDD_3_v127_start);

				// cmp ecx,10h
				issue66_YYYYdMMdDD_3_v127_end = byte_pattern::temp_instance().get_first().address(0x2B);

			}
			else return EU4_ERROR1;

			// コピーする関数を取得する
			byte_pattern::temp_instance().find_pattern("57 8B 43 10 3B C1 0F 82 C0 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc + " copy func")) {
				// push edi
				issue66_copy_func = byte_pattern::temp_instance().get_first().address(-0xD);
			}
			else return EU4_ERROR1;

			return NOERROR;
		case v1_26_X:
		case v1_25_X:
			/* 対応しない */
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("issue66");

		// 「日」を初期化
		day = new V();
		day->t.text[0] = 0xE;
		day->t.text[1] = '\0';
		day->len = 1;
		day->len2 = 0xF;

		// 「年」を初期化
		year = new V();
		year->t.text[0] = 0xF;
		year->t.text[1] = '\0';
		year->len = 1;
		year->len2 = 0xF;

		// 「月」を初期化
		month = new V();
		month->t.text[0] = 7; //BEL
		month->t.text[1] = '\0';
		month->len = 1;
		month->len2 = 0xF;

		/* 日付の表記の順番を入れ替える */
		result |= menubar_dateFix_hook(version);

		/* コピーバッファ関数をフック */
		result |= copyBuffFunc_hook(version);

		/* バッファ作成関数をフック */
		result |= createBuffFunc_hook(version);

		/* コピーテキスト作成関数をフック */
		result |= copyText_hook(version);

		/* M, Y → Y年M */
		result |= fixMC_Y_hook(version);

		/* D M, Y → Y年MD日*/
		result |= fixD_MC_Y_hook(version);

		/* M Y → Y年M */
		result |= fixM_Y_hook(version);

		/* YYYY.MM.DD → YYYY年MM月DD日 */
		/* 不具合があってコメントアウト：https://github.com/matanki-saito/EU4dll/issues/76 */
		//result |= fixYYYYdMMdDD_hook(version);

		return result;
	}
}