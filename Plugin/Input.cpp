#include "stdinc.h"
#include "byte_pattern.h"

/*  一部のUI、本文文字表示 */
namespace Input {

	/*-----------------------------------------------*/

	uintptr_t encodeUtf8_end;
	uintptr_t PHYSFS_utf8ToUcs2;
	uintptr_t heapMallocAddr;
	uintptr_t initilizeObjectFuncAddr;
	uintptr_t heapFreeAddr;
	uintptr_t encodeUtf8_end2;
	__declspec(naked) void encodeUtf8_start()
	{
		__asm {
			mov ecx, [ebp - 0x48];
			cmp ch, 0;
			jnz cc_1;
			xor al, al;

			push encodeUtf8_end;
			ret;

		cc_1:
			push    0x0FF; //dwBytes
			call    heapMallocAddr;
			pop     ecx;
			test    eax, eax;
			jz      cc_1;

			push    0;
			push    0x0FF;
			lea     eax, [eax];
			mov[ebp - 0xDC], eax; //lpMem
			push    eax;
			lea     ecx, [ebp - 0x48];
			push    ecx;
			call    PHYSFS_utf8ToUcs2;
			add     esp, 0x10;
			push    0x0FF; // dwBytes;
			call    heapMallocAddr;
			pop     ecx;
			jmp     cc_9s;

		cc_9r:
			push    esi;
			xor     esi, esi;

		cc_2:
			mov     eax, [ebp - 0xDC]; //lpMem
			movzx   ax, word ptr[eax + esi];
			cmp     ax, 0;
			jz      cc_10;
			xor     ecx, ecx;
			mov     ecx, 0x10;
			cmp     ah, 0xA4;
			jz      cc_4;
			cmp     ah, 0xA3;
			jz      cc_4;
			cmp     ah, 0xA7;
			jz      cc_4;
			cmp     ah, 0x24;
			jz      cc_4;
			cmp     ah, 0x5B;
			jz      cc_4;
			cmp     ah, 0;
			jz      cc_4;
			cmp     ah, 0x5C;
			jz      cc_4;
			cmp     ah, 0x20;
			jz      cc_4;
			cmp     ah, 0x0D;
			jz      cc_4;
			cmp     ah, 0x0A;
			jz      cc_4;
			cmp     ah, 0x22;
			jz      cc_4;
			cmp     ah, 0x7B;
			jz      cc_4;
			cmp     ah, 0x7D;
			jz      cc_4;
			cmp     ah, 0x40;
			jz      cc_4;
			cmp     ah, 0x80;
			jz      cc_4
				cmp     ah, 0x7E;
			jz      cc_4;
			cmp     ah, 0x2F;
			jz      cc_4;
			cmp     ah, 0xBD;
			jz      cc_4;
			cmp     ah, 0x3B;
			jz      cc_4;
			cmp     ah, 0x5D;
			jz      cc_4;
			cmp     ah, 0x5F;
			jz      cc_4;
			cmp     ah, 0x3D;
			jz      cc_4;
			cmp     ah, 0x23;
			jnz     cc_3;

		cc_4:
			add ecx, 2;

		cc_3:
			cmp     al, 0xA4;
			jz      cc_5;
			cmp     al, 0xA3;
			jz      cc_5;
			cmp     al, 0xA7;
			jz      cc_5;
			cmp     al, 0x24;
			jz      cc_5;
			cmp     al, 0x5B;
			jz      cc_5;
			cmp     al, 0;
			jz      cc_5;
			cmp     al, 0x5C;
			jz      cc_5;
			cmp     al, 0x20;
			jz      cc_5;
			cmp     al, 0x0D;
			jz      cc_5;
			cmp     al, 0x0A;
			jz      cc_5;
			cmp     al, 0x22;
			jz      cc_5;
			cmp     al, 0x7B;
			jz      cc_5;
			cmp     al, 0x7D;
			jz      cc_5;
			cmp     al, 0x40;
			jz      cc_5;
			cmp     al, 0x80;
			jz      cc_5;
			cmp     al, 0x7E;
			jz      cc_5;
			cmp     al, 0x2F;
			jz      cc_5;
			cmp     al, 0xBD;
			jz      cc_5;
			cmp     al, 0x3B;
			jz      cc_5;
			cmp     al, 0x5D;
			jz      cc_5;
			cmp     al, 0x5F;
			jz      cc_5;
			cmp     al, 0x3D;
			jz      cc_5;
			cmp     al, 0x23;
			jnz     cc_6;

		cc_5:
			add     ecx, 1;

		cc_6:
			cmp ecx, ESCAPE_SEQ_2;
			jnz cc_6_1;
			add al, LOW_SHIFT;
			jmp cc_7;

		cc_6_1:
			cmp ecx, ESCAPE_SEQ_3;
			jnz cc_6_2;
			sub ah, HIGH_SHIFT;
			jmp cc_7;

		cc_6_2:
			cmp ecx, ESCAPE_SEQ_4;
			jnz cc_7;
			add al, LOW_SHIFT;
			sub ah, HIGH_SHIFT;

		cc_7:
			add esi, 2;
			mov ebx, [ebp - 0xE0]; //Mem
			mov[ebx + edi], cl;
			mov[ebx + edi + 1], ax;
			add edi, 3;
			jmp cc_2;

		cc_9s:
			push    edi;
			push    ebx;
			xor     edi, edi;
			mov[ebp - 0xE0], eax; //Mem
			jmp     cc_9r;

		cc_10:
			pop esi;
			pop ebx;
			xor edi, edi;

		cc_12:
			mov     edx, [ebx];
			lea     ecx, [ebp - 0xD8];
			mov     eax, [ebp - 0xE0]; //Mem
			mov     al, [eax + edi];
			cmp     al, 0;
			jz      cc_13;
			mov     byte ptr[ebp + 0x8 + 3], al; //0x8 = arg_0
			lea     eax, [ebp + 0x8 + 3];
			push    eax;
			call    initilizeObjectFuncAddr;
			push    eax;
			mov     ecx, ebx;
			call    dword ptr[edx + 0x0C];
			add     edi, 1;
			jmp     cc_12;

		cc_13:
			pop     edi;
			push[ebp - 0xDC]; //lpMem
			call    heapFreeAddr;
			push[ebp - 0xE0]; //Mem
			call    heapFreeAddr;
			pop     ecx;
			pop     ecx;

			push encodeUtf8_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t input1_hook(EU4Version version) {
		std::string desc = "input ";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			
			//スタック拡張
			byte_pattern::temp_instance().find_pattern("D8 00 00 00 53 8B 5D 08 56 8B F1 85");
			if (byte_pattern::temp_instance().has_size(1, desc + "stack size change")) {
				// sub esp,0xD8
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(), 0xE0, true);
			}
			else return EU4_ERROR1;

			// 入力した文字をutf8からエスケープ列へ変換する
			byte_pattern::temp_instance().find_pattern("8B 4D B8 32 C0 88 45 0B");
			if (byte_pattern::temp_instance().has_size(1, desc + "encode utf8")) {
				// mov ecx, [ebp-0x48]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), encodeUtf8_start);
				encodeUtf8_end = byte_pattern::temp_instance().get_first().address(0x5);
			}
			else return EU4_ERROR1;

			//該当箇所はたくさん引っかかるので、少し上に引っかかるようにした
			byte_pattern::temp_instance().find_pattern("6A 00 6A 00 6A 0A 8B 07"); 
			if (byte_pattern::temp_instance().has_size(1, desc + "end2")) {
				// push 0
				encodeUtf8_end2 = byte_pattern::temp_instance().get_first().address(0xB);
			}
			else return EU4_ERROR1;

			//utf8バイト列からUCS2列にする
			byte_pattern::temp_instance().find_pattern("55 8B EC 51 8B 4D 10 53");
			if (byte_pattern::temp_instance().has_size(1,desc+"get PHYSFS_utf8ToUcs2 addr")) {
				// push ebp
				PHYSFS_utf8ToUcs2 = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;

			// ヒープ確保関数を保持
			byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 56 8B 75 08 83 FE E0 77 30");
			if (byte_pattern::temp_instance().has_size(1,desc + "get heap malloc get")) {
				// mov edi,edi
				heapMallocAddr = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;

			//オブジェクト初期化関数を保持。たくさん引っかかるので少し下に
			byte_pattern::temp_instance().find_pattern("C7 41 08 00 00 00 00 8A 00 88 41 0C");
			if (byte_pattern::temp_instance().has_size(1, desc + "get initilize object func addr")) {
				// mov dword ptr [ecx+8],0
				initilizeObjectFuncAddr = byte_pattern::temp_instance().get_first().address(-0x13);
			}
			else return EU4_ERROR1;

			//ヒープクリア関数を保持
			byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 83 7D 08 00 74 2D FF 75 08 6A");
			if (byte_pattern::temp_instance().has_size(1,desc + "get heap free func addr")) {
				// mov edi,edi
				heapFreeAddr = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;

			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t backspace_v125_end;
	__declspec(naked) void backspace_v125_start()
	{
		__asm {
			push    ebx;
			xor     ebx, ebx;
			mov     eax, [edi + 0x2C]; // 文字列長さ
			cmp     eax, 0x10;
			lea     ecx, [edi + 0x1C];
			jbe     dd_2;
			mov     ecx, [ecx];

		dd_2:
			mov     eax, [edi + 0x38]; // eax: キャレット位置
			sub     eax, 3;
			js      dd_3;
			mov     al, [ecx + eax];
			cmp     al, ESCAPE_SEQ_1;
			jz      dd_4;
			;			cmp     al, ESCAPE_SEQ_2;
			jz      dd_4;
			cmp     al, ESCAPE_SEQ_3;
			jz      dd_4;
			cmp     al, ESCAPE_SEQ_4;
			jnz     dd_3;

		dd_4:
			mov     ebx, 2;

		dd_3:
			mov     eax, [edi];
			mov     ecx, edi;
			test    esi, esi;
			jz      dd_6;
			call    dword ptr[eax + 0x0A00];
			jmp     dd_5;

		dd_6:
			call    dword ptr[eax + 0x9C];

		dd_5:
			cmp     ebx, 0;
			jz      dd_7;
			sub     ebx, 1;
			jmp     dd_3;

		dd_7:
			pop     ebx;

			push     backspace_v125_end;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t backspace_hook(EU4Version version) {
		std::string desc = "backspace";

		switch (version) {
		case v1_25_X:
		case v1_26_X:
		case v1_27_X:
		case v1_28_X:
		case v1_28_3:
			byte_pattern::temp_instance().find_pattern("8B 07 8B CF 85");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// mov eax, [edi]
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), backspace_v125_start);
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("0F B7 47 3A 8B CF 50 8D 45 D8");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				// movzx eax,word ptr [edi+3Ah]
				backspace_v125_end = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;
			return NOERROR;
		}
		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("input fix");

		/* バックスペース調整 */
		result |= backspace_hook(version);
		/* input stack 拡張*/
		result |= input1_hook(version);

		return result;
	}
}