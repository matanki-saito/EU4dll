#include "stdinc.h"
#include "byte_pattern.h"

namespace FileSave {

	// TODO:このコードはパリピ状態になっているので落ち着いた感じに修正したい

	/*-----------------------------------------------*/

	errno_t fileNameSaftySkip_hook(EU4Version version) {
		std::string desc = "file name safty skip";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			byte_pattern::temp_instance().find_pattern("85 FF 0F 84 EE 00 00 00 53 56");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// test edi,edi
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0xE9, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0xF1, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x00, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x00, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(4), 0x00, true);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t PHYSFS_utf8FromUcs2;

	/*-----------------------------------------------*/

	errno_t PHYSFS_utf8FromUcs2_hook(EU4Version version) {
		std::string desc = "get PHYSFS_utf8FromUcs2 addr";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			// 0: latin1
			// 1: ucs2
			// 2: ucs4
			byte_pattern::temp_instance().find_pattern("55 8B EC 56 8B 75 10 8B C6 57 8B 7D");
			if (byte_pattern::temp_instance().has_size(3, "")) {
				PHYSFS_utf8FromUcs2 = byte_pattern::temp_instance().get(1).address();
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t filenameEncode_v125_end;
	wchar_t fnamew[200] = {};
	char fnameutf8[200] = {};

	void rstTmpMem() {
		memset(fnamew, '\0', sizeof(wchar_t) * 200);
		memset(fnameutf8, '\0', sizeof(char) * 200);
	}

	__declspec(naked) void filenameEncode_v125_start() {
		__asm {

			push edx;

			call rstTmpMem;

			pop edx;
			mov ecx, edx;

			push esi;
			xor esi, esi;

		issue_7_1_loop_start:
			cmp byte ptr[ecx], ESCAPE_SEQ_1;
			jz issue_7_1_10;
			cmp byte ptr[ecx], ESCAPE_SEQ_2;
			jz issue_7_1_11;
			cmp byte ptr[ecx], ESCAPE_SEQ_3;
			jz issue_7_1_12;
			cmp byte ptr[ecx], ESCAPE_SEQ_4;
			jz issue_7_1_13;
			cmp byte ptr[ecx], NULL;
			jz issue_7_1_loop_end;

			movzx eax, byte ptr[ecx];
			jmp issue_7_1_yy;

		issue_7_1_10:
			movzx eax, word ptr[ecx + 1];
			jmp issue_7_1_xx;

		issue_7_1_11:
			movzx eax, word ptr[ecx + 1];
			sub eax, SHIFT_2;
			jmp issue_7_1_xx;

		issue_7_1_12:
			movzx eax, word ptr[ecx + 1];
			add eax, SHIFT_3;
			jmp issue_7_1_xx;

		issue_7_1_13:
			movzx eax, word ptr[ecx + 1];
			add eax, SHIFT_4;

		issue_7_1_xx:
			add ecx, 2;

		issue_7_1_yy:
			mov word ptr[fnamew + esi], ax;
			inc ecx;
			add esi, 2;
			jmp issue_7_1_loop_start;

		issue_7_1_loop_end:
			push 0; // ?
			push 200; // dst-buf-len
			lea eax, fnameutf8; // dst
			push eax;
			lea eax, fnamew; // src
			push eax;
			call PHYSFS_utf8FromUcs2;
			add esp, 0x10;

			lea edx, fnameutf8;

			pop esi;
			mov dword ptr[ebp - 0x34], 0xF;
			mov dword ptr[ebp - 0x38], 0;
			mov byte ptr[ebp - 0x48], 0;

			push filenameEncode_v125_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t filenameEncode_hook(EU4Version version) {

		std::string desc = "file name encode";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			byte_pattern::temp_instance().find_pattern("51 52 8D 4D B8 E8 ? ? ? ? 8D 4D B8 C7");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x29), filenameEncode_v125_start);
				filenameEncode_v125_end = byte_pattern::temp_instance().get_first().address(-0x17);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	inline wchar_t UCS2ToCP1252(int cp) {
		wchar_t result = cp;
		switch (cp) {
		case 0x20AC: result = 0x80; break;
		case 0x201A: result = 0x82; break;
		case 0x0192: result = 0x83; break;
		case 0x201E: result = 0x84; break;
		case 0x2026: result = 0x85; break;
		case 0x2020: result = 0x86; break;
		case 0x2021: result = 0x87; break;
		case 0x02C6: result = 0x88; break;
		case 0x2030: result = 0x89; break;
		case 0x0160: result = 0x8A; break;
		case 0x2039: result = 0x8B; break;
		case 0x0152: result = 0x8C; break;
		case 0x017D: result = 0x8E; break;
		case 0x2018: result = 0x91; break;
		case 0x2019: result = 0x92; break;
		case 0x201C: result = 0x93; break;
		case 0x201D: result = 0x94; break;
		case 0x2022: result = 0x95; break;
		case 0x2013: result = 0x96; break;
		case 0x2014: result = 0x97; break;
		case 0x02DC: result = 0x98; break;
		case 0x2122: result = 0x99; break;
		case 0x0161: result = 0x9A; break;
		case 0x203A: result = 0x9B; break;
		case 0x0153: result = 0x9C; break;
		case 0x017E: result = 0x9E; break;
		case 0x0178: result = 0x9F; break;
		}

		return result;
	}

	errno_t convertWideTextToEscapedText(const wchar_t* from, char** to) {

		errno_t success = 0;
		int toIndex = 0;
		unsigned int size = 0;

		/* */
		if (from == NULL) {
			success = 1;
			goto A;
		}

		/* */
		size = wcslen(from);

		/* 全部エスケープしても３倍を超えることはない。１０はバッファ*/
		*to = (char*)calloc(size * 3 * 2 + 10, sizeof(char));

		if (*to == NULL) {
			success = 2;
			goto A;
		}

		/* */
		toIndex = 0;
		for (unsigned int fromIndex = 0; fromIndex < size; fromIndex++) {
			wchar_t cp = from[fromIndex];

			/* */
			if (UCS2ToCP1252(cp) != cp) {
				(*to)[toIndex++] = (byte)cp;
				continue;
			}

			/* ずらす */
			if (cp > 0x100 && cp < 0xA00) {
				cp = cp + 0xE000;
			}

			/* 上位バイト */
			byte high = (cp >> 8) & 0x000000FF;

			/* 下位バイト */
			byte low = cp & 0x000000FF;

			byte escapeChr = 0x10;

			/* 2byteじゃない */
			if (high == 0) {
				(*to)[toIndex++] = (byte)cp;
				continue;
			}

			/* high byteより決定 */
			switch (high) {
			case 0xA4:case 0xA3:case 0xA7:case 0x24:case 0x5B:case 0x00:case 0x5C:
			case 0x20:case 0x0D:case 0x0A:case 0x22:case 0x7B:case 0x7D:case 0x40:
			case 0x80:case 0x7E:case 0x2F:case 0xBD:case 0x3B:case 0x5D:case 0x5F:
			case 0x3D:case 0x23:
				escapeChr += 2;
				break;
			default:
				break;
			}

			/* low byteより決定 */
			switch (low) {
			case 0xA4:case 0xA3:case 0xA7:case 0x24:case 0x5B:case 0x00:case 0x5C:
			case 0x20:case 0x0D:case 0x0A:case 0x22:case 0x7B:case 0x7D:case 0x40:
			case 0x80:case 0x7E:case 0x2F:case 0xBD:case 0x3B:case 0x5D:case 0x5F:
			case 0x3D:case 0x23:
				escapeChr++;
				break;
			default:
				break;
			}

			switch (escapeChr) {
			case 0x11:
				low += 14;
				break;
			case 0x12:
				high -= 9;
				break;
			case 0x13:
				low += 14;
				high -= 9;
				break;
			case 0x10:
			default:
				break;
			}

			(*to)[toIndex++] = escapeChr;
			(*to)[toIndex++] = low;
			(*to)[toIndex++] = high;
		}

	A:
		return success;
	}

	errno_t convertTextToWideText(const char* from, wchar_t **to) {

		errno_t success = 0;
		unsigned int err = 0;
		unsigned int wideTextSize = 0;

		/* */
		if (from == NULL) {
			success = 1;
			goto A;
		}

		/* */
		wideTextSize = MultiByteToWideChar(
			CP_UTF8,
			NULL,
			from,
			-1,
			NULL,
			NULL);

		if (wideTextSize == NULL) {
			success = GetLastError();
			goto A;
		}

		/* */
		*to = (wchar_t*)calloc(wideTextSize, sizeof(wchar_t));

		if (*to == NULL) {
			success = 3;
			goto A;
		}

		/* */
		err = MultiByteToWideChar(
			CP_UTF8,
			NULL,
			from,
			-1,
			*to,
			wideTextSize);

		if (err == NULL) {
			success = 4;
			goto B;
		}

		goto A;

	B:
		free(*to);
	A:
		return success;
	}

	union T {
		char text[0x10];
		char* p;
	};

	typedef struct V {
		union T t;
		int len;
		int len2;
	} Vs;

	Vs* tmpZV = NULL;
	char*  utf8ToEscapedStr(char *from) {

		if (tmpZV != NULL) {
			if (tmpZV->len > 0x10) {
				free(tmpZV->t.p);
			}
			delete tmpZV;
		}

		tmpZV = new Vs();

		wchar_t *tmp = NULL;
		char *tmp2 = NULL;

		char *src = NULL;

		if (*(from + 0x10) >= 0x10) {
			src = (char*)(*((uintptr_t*)from));
		}
		else {
			src = from;
		}

		//UTF-8 -> wide char (ucs2)
		convertTextToWideText(src, &tmp);

		//wide char (ucs2) -> Escaped Text
		convertWideTextToEscapedText(tmp, &tmp2);

		free(tmp);

		int len = strlen(tmp2);
		tmpZV->len = len;
		tmpZV->len2 = len;

		if (len >= 0x10) {
			tmpZV->t.p = tmp2;
		}
		else {
			memcpy(tmpZV->t.text, tmp2, len);
		}

		return (char*)tmpZV;
	}

	char titleUtf8tmp[200] = {};
	char titleMytmp[200] = {};
	uintptr_t issue_7_2_end;
	__declspec(naked) void issue_7_2_start() {
		__asm {
			lea eax, [ebx + 0x304];

			push ecx;

			push eax;
			call utf8ToEscapedStr;
			add esp, 4;

			pop ecx;

			push eax;
			mov eax, [ecx];


			push issue_7_2_end;
			ret;

		}
	}

	char *save_game_title = "save_game_title";
	uintptr_t issue_7_2_end_126;
	__declspec(naked) void issue_7_2_start_126() {
		__asm {
			push ecx;

			push edi;
			call utf8ToEscapedStr;
			add esp, 4;

			pop ecx;

			push eax;
			push save_game_title;

			mov     eax, dword ptr[ecx];
			call dword ptr[eax + 0x4C];

			push issue_7_2_end_126;
			ret;

		}
	}

	/*-----------------------------------------------*/

	errno_t showTitle_hook(EU4Version version) {

		std::string desc = "show title";

		switch (version) {
		case v1_25_X:
			byte_pattern::temp_instance().find_pattern("8D 83 04 03 00 00 50 8B");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_7_2_start);
				issue_7_2_end = byte_pattern::temp_instance().get_first().address(0x9);
			}
			else return EU4_ERROR1;
			return NOERROR;

		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			byte_pattern::temp_instance().find_pattern("57 68 ? ? ? ? FF 50 4C 8B C8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_7_2_start_126);
				issue_7_2_end_126 = byte_pattern::temp_instance().get_first().address(0x9);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t fileEnumSkip_hook(EU4Version version) {
		std::string desc = "file enum";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
			byte_pattern::temp_instance().find_pattern("74 0E 78 0A 8A 41 01 41");
			if (byte_pattern::temp_instance().has_size(2, desc)) {
				// jz short loc_XXXXX
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(), 0xEB, true);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("file save etc");

		/* ファイル名を安全にしている場所を短絡する jmp [address] */
		result |= fileNameSaftySkip_hook(version);

		/* ファイル名を変換する */
		result |= filenameEncode_hook(version);

		/* 変換関数を探してくる */
		result |= PHYSFS_utf8FromUcs2_hook(version);

		/* タイトルを表示できるようにする */
		result |= showTitle_hook(version);

		/* UTF-8ファイルを列挙できるようにする jz(74) -> jmp(EB) */ 
		result |= fileEnumSkip_hook(version);

		return result;
	}
}