#include "stdinc.h"
#include "byte_pattern.h"

using namespace std;

namespace Test {





	uintptr_t c_2;
	__declspec(naked) void c_1()
	{
		__asm {
			mov eax,[eax + esi];
			mov[ebp - 0xA0], eax;

			push c_2;
			ret;
		}
	}

	uintptr_t d_2;
	__declspec(naked) void d_1()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz d_3;
			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz d_3;
			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz d_3;
			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz d_3;
			jmp d_4;

		d_3:
			mov ecx, [ebp - 0xA0];
			mov[eax], ecx;
			lea ecx, [eax];
			mov byte ptr[ecx + 0x10], 3;

		d_4:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push d_2;
			ret;
		}
	}

	uintptr_t e_5;
	__declspec(naked) void e_1()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz e_10;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz e_11;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz e_12;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz e_13;
			jmp e_2;

		e_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp e_3;

		e_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp e_3;
			
		e_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp e_3;

		e_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			jmp e_3;

		e_2:
			mov al, [eax + esi];
			movzx eax, al;
			jmp e_4;

		e_3:
			movzx eax, ax;
			add esi, 2;
			cmp eax, NO_FONT;
			ja e_4;
			mov eax, NOT_DEF;

		e_4:
			mov word ptr[ebp - 0x564], ax;

			push e_5;
			ret;
		}
	}

	uintptr_t v_2;
	uintptr_t v_3;
	__declspec(naked) void v_1()
	{
		__asm {
			cmp word ptr[eax + 6], 0;
			jz v_3_jmp;

			cmp word ptr[ebp - 0x564], 0xFF;
			ja v_3_jmp;

			push v_2;
			ret;

		v_3_jmp:
			push v_3;
			ret;
		}
	}

	uintptr_t b_6;
	__declspec(naked) void b_1()
	{
		__asm {
			cmp byte ptr[eax + edi], ESCAPE_SEQ_1;
			jz b_10;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_2;
			jz b_11;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_3;
			jz b_12;
			cmp byte ptr[eax + edi], ESCAPE_SEQ_4;
			jz b_13;
			jmp b_3;

		b_10:
			movzx eax, word ptr[eax + edi + 1];
			jmp b_1x;

		b_11:
			movzx eax, word ptr[eax + edi + 1];
			sub eax, SHIFT_2;
			jmp b_1x;

		b_12:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_3;
			jmp b_1x;

		b_13:
			movzx eax, word ptr[eax + edi + 1];
			add eax, SHIFT_4;
			jmp b_1x;

		b_3:
			movzx eax, byte ptr[eax + edi];
			jmp b_4;

		b_1x:
			movzx eax, ax;
			add edi, 2;
			mov[ebp - 0x1C], edi;
			cmp eax, NO_FONT;
			ja b_4;
			mov eax, NOT_DEF;

		b_4:
			mov eax, [ecx + eax * 4];
			
			push b_6;
			ret;
		}
	}
















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





	uintptr_t loc_193704C;
	__declspec(naked) void dd_1()
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

			push     loc_193704C;
			ret;
		}
	}

	uintptr_t cc_end;
	uintptr_t PHYSFS_utf8ToUcs2;
	uintptr_t sub_1D7B347;
	uintptr_t sub_1966D50;
	uintptr_t sub_1D7B41A;
	uintptr_t loc_1974E8D;
	__declspec(naked) void cc_start()
	{
		__asm {
			mov ecx, [ebp - 0x48];
			cmp ch, 0;
			jnz cc_1;
			xor al, al;

			push cc_end;
			ret;

		cc_1:
			push    0x0FF; //dwBytes
			call    sub_1D7B347;
			pop     ecx;
			test    eax, eax;
			jz      cc_1;

			push    0;
			push    0x0FF;
			lea     eax, [eax];
			mov [ebp - 0xDC], eax; //lpMem
			push    eax;
			lea     ecx, [ebp - 0x48];
			push    ecx;
			call    PHYSFS_utf8ToUcs2;
			add     esp, 0x10;
			push    0x0FF; // dwBytes;
			call    sub_1D7B347;
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
			mov[ebp -0xE0], eax; //Mem
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
			call    sub_1966D50;
			push    eax;
			mov     ecx, ebx;
			call    dword ptr[edx + 0x0C];
			add     edi, 1;
			jmp     cc_12;
			
		cc_13:
			pop     edi;
			push [ebp - 0xDC]; //lpMem
			call    sub_1D7B41A;
			push [ebp - 0xE0]; //Mem
			call    sub_1D7B41A;
			pop     ecx;
			pop     ecx;
			
			push loc_1974E8D;
			ret;
		}
	}

	uintptr_t ee_5;
	uintptr_t SDL_SetTextInputRect;
	uintptr_t loc_1B46960;
	__declspec(naked) void ee_4()
	{
		__asm {
			jz ee_2;
			
			push ee_5;
			ret;

		ee_2:
			sub     esp, 8;
			mov     ecx, [ebp + 0x18];
			mov     edx, [ebp + 0x8];
			mov     [ecx + 0x38], edx;
			mov     dword ptr[ebp - 0x14], 0;
			mov     dword ptr[ebp - 0x10], 0;
			lea     eax, [ebp - 0x14];
			push    eax;
			call    SDL_SetTextInputRect;
			add     esp, 0xC;
			
			push     loc_1B46960;
			ret;
		}
	}

	uintptr_t ee_7;
	uintptr_t ee_9;
	__declspec(naked) void ee_6()
	{
		__asm {
			add esp, 0x14;
			test eax, eax;
			jnz ee_8;

			push ee_7;
			ret;

		ee_8:
			mov ecx, [ebp + 0x0C];
			mov ebx, [ebp + 0x10]; //hDrop

			push ee_9;
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




		///* sub_1936F30 入力の修正 */
		//// バックスペースの修正
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("8B 07 8B CF 85");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), dd_1);
		//}
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("0F B7 47 3A 8B CF 50 8D 45 D8");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	loc_193704C = byte_pattern::temp_instance().get_first().address();
		//}

		///* sub_1974E10 入力の修正 */
		//// 入力した文字をutf8からエスケープ列へ変換する
		////スタック拡張
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("D8 00 00 00 53 8B 5D 08 56 8B F1 85");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(), 0xE0, true);
		//}
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("8B 4D B8 32 C0 88 45 0B");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), cc_start);
		//	cc_end = byte_pattern::temp_instance().get_first().address(0x5);
		//}
		////該当箇所はたくさん引っかかるので、少し上に引っかかるようにした
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("6A 00 6A 00 6A 0A 8B 07"); 
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	loc_1974E8D = byte_pattern::temp_instance().get_first().address(0xB);
		//}
		////utf8バイト列からUCS2列にする
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("55 8B EC 51 8B 4D 10 53");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	PHYSFS_utf8ToUcs2 = byte_pattern::temp_instance().get_first().address();
		//}

		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//// ヒープ確保関数を保持
		//byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 56 8B 75 08 83 FE E0 77 30");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	sub_1D7B347 = byte_pattern::temp_instance().get_first().address();
		//}

		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		////オブジェクト初期化関数を保持。たくさん引っかかるので少し下に
		//byte_pattern::temp_instance().find_pattern("C7 41 08 00 00 00 00 8A 00 88 41 0C");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	sub_1966D50 = byte_pattern::temp_instance().get_first().address(-0x13);
		//}

		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		////ヒープクリア関数を保持
		//byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 83 7D 08 00 74 2D FF 75 08 6A");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	sub_1D7B41A = byte_pattern::temp_instance().get_first().address();
		//}

		///* sub_1994720 : 一部のUI、ツールチップの表示 */
		//// スタックの修正
		////スタック修正
		//byte_pattern::temp_instance().find_pattern("81 EC 58 05 00 00 8B");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x5A, true);
		//}
		//byte_pattern::temp_instance().find_pattern("8A 04 30 88 85 60 FF FF");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), c_1);
		//	//c_2 = byte_pattern::temp_instance().get_first().address(0x9);

		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), d_1);
		//	//d_2 = byte_pattern::temp_instance().get_first().address(0x19);
		//}
		//byte_pattern::temp_instance().find_pattern("8A 04 30 0F B6 C0 8B 84");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), e_1);
		//	//e_5 = byte_pattern::temp_instance().get_first().address(0x6);
		//}
		//byte_pattern::temp_instance().find_pattern("66 83 78 06 00 0F 85");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), v_1);
		//	//v_3 = byte_pattern::temp_instance().get_first().address(0xB);
		//}
		//byte_pattern::temp_instance().find_pattern("46 3B 75 DC 0F 8C DD F7");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//v_2 = byte_pattern::temp_instance().get_first().address();
		//}
		//byte_pattern::temp_instance().find_pattern("0F B6 04 38 8B 04 81");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), b_1);
		//	//b_6 = byte_pattern::temp_instance().get_first().address(0x7);
		//}
		////スタックの後始末
		//byte_pattern::temp_instance().find_pattern("8D A5 94 FA FF FF");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	//injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x92, true);
		//}



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



		///* sub_1B23C80 入力の修正 */
		//// SDL_windowsevents.cの修正
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("83 C4 14 85 C0 0F 85 BF");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), ee_6);
		//	ee_7 = byte_pattern::temp_instance().get_first().address(0xB);
		//}
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("FF 75 14 53 51 FF 75 08 FF 35");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	ee_9 = byte_pattern::temp_instance().get_first().address();
		//}

		///* sub_1B46720 入力の修正 */
		//// SDL_windowskeyboard.cの修正
		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("0F 84 FA 01 00 00 83 E8");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), ee_4);
		//	ee_5 = byte_pattern::temp_instance().get_first().address(0x6);
		//}

		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("55 8B EC A1 ? ? ? ? 85 C0 74 13 8B");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	SDL_SetTextInputRect = byte_pattern::temp_instance().get_first().address();
		//}

		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("5F BB 01 00 00 00 5E 8B");
		//if (byte_pattern::temp_instance().has_size(2)) {
		//	loc_1B46960 = byte_pattern::temp_instance().get(1).address();
		//}

		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("68 00 08 00 00 57");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(-0x2), 0xEB, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(-0x1), 0x41, true);
		//}

		//// 1.25.1.0, 1.26.0.0, 1.27.0.0
		//byte_pattern::temp_instance().find_pattern("8B 4D 14 89 19");
		//if (byte_pattern::temp_instance().has_size(1)) {
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x0), 0x90, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x1), 0x90, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x2), 0x90, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x3), 0x90, true);
		//	injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x4), 0x90, true);
		//}







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
