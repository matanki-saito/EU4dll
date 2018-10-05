#include "stdinc.h"
#include "byte_pattern.h"

using namespace std;

namespace Test {


	uintptr_t i_7;
	uintptr_t loc_1998C12;
	__declspec(naked) void i_1()
	{
		__asm {
			cmp byte ptr[esi + edx], ESCAPE_SEQ_1;
			jz i_10;
			cmp byte ptr[esi + edx], ESCAPE_SEQ_2;
			jz i_11;
			cmp byte ptr[esi + edx], ESCAPE_SEQ_3;
			jz i_12;
			cmp byte ptr[esi + edx], ESCAPE_SEQ_4;
			jz i_13;
			jmp i_2;

		i_10:
			movzx eax, word ptr[esi + edx + 1];
			jmp i_1x;

		i_11:
			movzx eax, word ptr[esi + edx + 1];
			sub eax, SHIFT_2;
			jmp i_1x;

		i_12:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_3;
			jmp i_1x;

		i_13:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_4;
			jmp i_1x;

		i_2:
			mov dl, [esi + edx];
			movzx eax, dl;
			jmp i_5;

		i_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;

			ja i_4;
			mov eax, NOT_DEF;

		i_4:
			add esi, 3;
			cmp esi, ebx;
			ja i_6;
			sub esi, 1;

		i_5:
			lea ecx, [edi + 0xB4];

			push i_7;
			ret;

		i_6:
			mov eax, [esp + 0x98 - 0x8C];

			push loc_1998C12;
			ret;

		}
	}

	uintptr_t w_2;
	__declspec(naked) void w_1()
	{
		__asm {
			mov eax, [eax + edi];
			mov [ebp - 0x5C], eax;
			lea ecx, [ebp - 0xAC];

			push w_2;
			ret;
		}
	}

	uintptr_t x_2;
	__declspec(naked) void x_1()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz x_4;
			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz x_4;
			jmp x_3;

		x_4:
			mov ecx, [ebp - 0x5C];
			mov[eax], ecx;
			lea ecx, [eax];
			mov byte ptr[ecx + 0x10], 3;

		x_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push x_2;
			ret;
		}
	}

	uintptr_t y_2;
	__declspec(naked) void y_1()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz y_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz y_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz y_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz y_13;
			jmp y_7;

		y_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp y_1x;

		y_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp y_1x;

		y_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp y_1x;

		y_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;

		y_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja y_4;
			mov eax, NOT_DEF;

		y_4:
			add edi, 2;
			jmp y_6;

		y_7:
			mov al, [eax + edi];
			movzx eax, al;

		y_6:
			push y_2;
			ret;
		}
	}

	uintptr_t z_2;
	__declspec(naked) void z_1()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz z_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz z_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz z_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz z_13;
			jmp z_5;
		
		z_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp z_1x;

		z_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax,SHIFT_2;
			jmp z_1x;

		z_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax,SHIFT_3;
			jmp z_1x;

		z_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			
		z_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja z_4;
			mov eax, NOT_DEF;

		z_4:
			add esi, 2;
		z_6:
			mov edx, [edx + eax * 4];

			push z_2;
			ret;

		z_5:
			movzx eax, byte ptr[eax + esi];
			jmp z_6;
		}
	}







	uintptr_t q_2_1;
	__declspec(naked) void q_1()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz q_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz q_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz q_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz q_13;
			movzx eax, byte ptr[eax + edi];
			jmp q_4;

		q_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp q_1x;

		q_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp q_1x;

		q_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp q_1x;

		q_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;
			
		q_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja q_3;
			mov eax, NOT_DEF;

		q_3:
			add edi, 2;

		q_4:
			mov ecx, [ebp - 0x28];
			mov[ebp - 0x31A], ax;
			movzx eax, ax;

			mov ecx, [ecx + eax * 4];

			push q_2_1;
			ret;
		}
	}

	uintptr_t bb_3;
	uintptr_t bb_2;
	__declspec(naked) void bb_1()
	{
		__asm {
			lahf;
			test ah, 0x44;
			jnp bb_3_jmp;

			cmp word ptr [ebp - 0x31A], 0xFF;
			jb bb_2_jmp;

		bb_3_jmp:
			push bb_3;
			ret;

		bb_2_jmp:
			push bb_2;
			ret;
		}
	}













	uintptr_t PHYSFS_utf8FromUcs2;
	uintptr_t issue_7_1_end;
	wchar_t fnamew[200] = {};
	char fnameutf8[200] = {};

	void rstTmpMem() {
		memset(fnamew, '\0', sizeof(wchar_t) * 200);
		memset(fnameutf8, '\0', sizeof(char) * 200);
	}

	__declspec(naked) void issue_7_1_start() {
		__asm {

			push edx;

			call rstTmpMem;

			pop edx;
			mov ecx, edx;

			push esi;
			xor esi, esi;

		issue_7_1_loop_start:
			cmp byte ptr [ecx], ESCAPE_SEQ_1;
			jz issue_7_1_10;
			cmp byte ptr [ecx], ESCAPE_SEQ_2;
			jz issue_7_1_11;
			cmp byte ptr [ecx], ESCAPE_SEQ_3;
			jz issue_7_1_12;
			cmp byte ptr [ecx], ESCAPE_SEQ_4;
			jz issue_7_1_13;
			cmp byte ptr [ecx], NULL;
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
			mov dword ptr [ebp - 0x34],0xF;
			mov dword ptr [ebp - 0x38], 0;
			mov byte ptr[ebp - 0x48], 0;

			push issue_7_1_end;
			ret;
		}
	}



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
				(*to)[toIndex++] = (byte) cp;
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
			memcpy(tmpZV->t.text,tmp2,len);
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

			mov     eax, dword ptr [ecx];
			call dword ptr[eax + 0x4C];

			push issue_7_2_end_126;
			ret;

		}
	}

	uintptr_t kinako_end;
	uintptr_t funcA;
	__declspec(naked) void kinako_start() {
		__asm {
			mov eax, dword ptr fs:0x18;
			mov eax, [eax + 0x30];
			mov byte ptr[eax + 2], 0;
			call funcA;
			
			push kinako_end;
			ret;
		}
	}

	uintptr_t issue_12_end;
	__declspec(naked) void issue_12_start() {
		__asm {
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_1;
			jz issue_12_10;
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_2;
			jz issue_12_11;
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_3;
			jz issue_12_12;
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_4;
			jz issue_12_13;

			movzx eax, byte ptr[eax + ecx];
			jmp issue_12_y;

		issue_12_10:
			movzx eax, word ptr[eax + ecx + 1];
			jmp issue_12_x;

		issue_12_11:
			movzx eax, word ptr[eax + ecx + 1];
			sub eax, SHIFT_2;
			jmp issue_12_x;

		issue_12_12:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_3;
			jmp issue_12_x;

		issue_12_13:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_4;

		issue_12_x:
			movzx eax, ax;
			add ecx, 2;
			cmp eax, NO_FONT;
			ja issue_12_y;
			mov eax, NOT_DEF;

		issue_12_y:
			mov eax,dword ptr [esi + eax * 4 + 0xB4];
			
			push issue_12_end;
			ret;
		}
	}

	uintptr_t sub_135FBC0;
	uintptr_t issue_19_keydown_end;
	__declspec(naked) void issue_19_keydown_start() {
		__asm {
			cmp ebx, 229;
			jz issue_19_keydown_x; // skip
			
			push esi;
			push 1;
			call sub_135FBC0;
			add esp, 8;

		issue_19_keydown_x:
			push issue_19_keydown_end;
			ret;
		}
	}

	uintptr_t issue_19_keypress_end;
	__declspec(naked) void issue_19_keypress_start() {
		__asm {
			cmp ebx, 229;
			jz issue_19_keypress_x; // skip

			push esi;
			push 1;
			call sub_135FBC0;
			add esp, 8;

		issue_19_keypress_x:
			push issue_19_keypress_end;
			ret;
		}
	}


	void InitAndPatch() {




		///* sub_1998A30 : ツールチップの改行 */
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("8A 14 16 8D 8F");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), i_1);
		//	i_7 = byte_pattern::temp_instance().get_first().address(0xC);
		//}
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("66 0F 6E C0 0F 5B C0 0F 2F C8 76 04 F3 0F");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	loc_1998C12 = byte_pattern::temp_instance().get_first().address();
		//}

		///* sub_1999AA0 : ツールチップの改行 */
		//byte_pattern::temp_instance().find_pattern("8A 04 38 8D 8D 54");
		//if (byte_pattern::temp_instance().has_size(2)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), w_1);
		//	//w_2 = byte_pattern::temp_instance().get_first().address(0xC);
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), x_1);
		//	//x_2 = byte_pattern::temp_instance().get_first().address(0x19);
		//}
		//byte_pattern::temp_instance().find_pattern("8A 04 38 0F B6");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), y_1);
		//	//y_2 = byte_pattern::temp_instance().get_first().address(0x6);
		//}
		//byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 14 82 89 55");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), z_1);
		//	//z_2 = byte_pattern::temp_instance().get_first().address(0x7);
		//}


		//
		///* sub_199B240 : イベントダイアログ調整？ */
		//byte_pattern::temp_instance().find_pattern("81 EC 0C 03 00 00 8B");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x2), 0x0E, true);
		//}
		//byte_pattern::temp_instance().find_pattern("0F B6 04 38 8B 4D D8 8B 0C");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), q_1);
		//	//q_2_1 = byte_pattern::temp_instance().get_first().address(0xA);
		//}
		//byte_pattern::temp_instance().find_pattern("9F F6 C4 44 7A 58 66");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), bb_1);
		//	//bb_3 = byte_pattern::temp_instance().get_first().address(0x6);
		//}
		//byte_pattern::temp_instance().find_pattern("8B 45 14 8B 4D D4 8B 55");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//bb_2 = byte_pattern::temp_instance().get_first().address();
		//}
		//










		///* UTF-8ファイルを列挙できるようにする jz(74) -> jmp(EB) */ 
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("74 0E 78 0A 8A 41 01 41");
		//if (byte_pattern::temp_instance().has_size(2)) {
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(), 0xEB , true);
		//}

		///* ファイル名を安全にしている場所を短絡する jmp [address] */
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("85 FF 0F 84 EE 00 00 00 53 56");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0xE9, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0xF1, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x00, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x00, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(4), 0x00, true);
		//}

		//// 0: latin1
		//// 1: ucs2
		//// 2: ucs4
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("55 8B EC 56 8B 75 10 8B C6 57 8B 7D");
		//if (byte_pattern::temp_instance().has_size(3)) {
		//	PHYSFS_utf8FromUcs2 = byte_pattern::temp_instance().get(1).address();
		//}

		//// ファイル名を変換する
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("51 52 8D 4D B8 E8 ? ? ? ? 8D 4D B8 C7");
		//if (byte_pattern::temp_instance().has_size(2)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(-0x29), issue_7_1_start);
		//	issue_7_1_end = byte_pattern::temp_instance().get_first().address(-0x17);
		//}

		//// セーブファイルのタイトルを表示する
		////1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("57 68 ? ? ? ? FF 50 4C 8B C8");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_7_2_start_126);
		//	issue_7_2_end_126 = byte_pattern::temp_instance().get_first().address(0x9);
		//}
		//else {
		//	//1.25.1.0
		//	byte_pattern::temp_instance().find_pattern("8D 83 04 03 00 00 50 8B");
		//	if (byte_pattern::temp_instance().has_size(1)) {
		//		injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_7_2_start);
		//		issue_7_2_end = byte_pattern::temp_instance().get_first().address(0x9);
		//	}
		//}

		///* issue-12 nudgeモード修正 */
		//// 1.25.1.0, 1.26.0.0
		//byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 84 86 B4 00 00 00");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_12_start);
		//	//issue_12_end = byte_pattern::temp_instance().get_first().address(0xB);
		//}

		///* issue-19 */
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("83 C4 08 33 C0 E9 82 F8 FF FF");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xE), issue_19_keydown_start);
		//	issue_19_keydown_end = byte_pattern::temp_instance().get_first().address(0xE + 0xB);
		//}
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("55 8B EC 83 EC 40 56 8B 75 0C");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	sub_135FBC0 = byte_pattern::temp_instance().get_first().address(0x0);
		//}
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("83 FE 46 75 11 80 78 46 00 75");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xB), issue_19_keypress_start);
		//	issue_19_keypress_end = byte_pattern::temp_instance().get_first().address(0xB + 0xB);
		//}
	}
}
