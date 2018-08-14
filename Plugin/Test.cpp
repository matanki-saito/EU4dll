#include "stdinc.h"
#include "byte_pattern.h"

using namespace std;

namespace Test {


#define ESCAPE_SEQ_1 0x10
#define ESCAPE_SEQ_2 0x11
#define ESCAPE_SEQ_3 0x12
#define ESCAPE_SEQ_4 0x13

#define LOW_SHIFT 0x0F
#define HIGH_SHIFT 0x9

#define SHIFT_2 LOW_SHIFT
#define SHIFT_3 0x900
#define SHIFT_4 0x8F1

#define NO_FONT 0x98F
#define NOT_DEF 0x2026


	uintptr_t m_5;
	__declspec(naked) void m_1()
	{
		__asm {
			cmp byte ptr[eax + edx], ESCAPE_SEQ_1;
			jz m_10;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_2;
			jz m_11;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_3;
			jz m_12;

			cmp byte ptr[eax + edx], ESCAPE_SEQ_4;
			jz m_13;

			jmp m_3;

		m_10:
			movzx eax, word ptr[eax + edx + 1];
			jmp m_1x;

		m_11:
			movzx eax, word ptr[eax + edx + 1];
			sub eax, SHIFT_2;
			jmp m_1x;

		m_12:
			movzx eax, word ptr[eax + edx + 1];
			add eax, SHIFT_3;
			jmp m_1x;

		m_13:
			movzx eax, word ptr[eax + edx + 1];
			add eax, SHIFT_4;

		m_1x:
			add edx, 2;
			mov[ebp - 0x24], edx;
			sub edx, 2;

			movzx eax, ax;
			cmp eax, NO_FONT;
			ja m_4;
			mov eax, NOT_DEF;
			jmp m_4;

		m_3:
			movzx eax, byte ptr[eax + edx];

		m_4:
			mov esi, [esi + eax * 4];

			mov[ebp - 0x172], ax;
			cmp word ptr[ebp - 0x172], 0x100;

			jb m_421;
			cmp word ptr[ebp - 0x1C], 3;

			ja m_421;
			inc edx;
			mov word ptr[ebp - 0x172], 0x10;

		m_421:
			push m_5;
			ret;
		}
	}

	uintptr_t kk_4;
	__declspec(naked) void kk_1(){
		__asm {
			cmp word ptr[ebp - 0x172], 0x100;
			jb kk_2;
			sub eax, 3;
			jmp kk_3;

		kk_2:
			dec eax;

		kk_3:
			sqrtss xmm1, xmm1;

			push kk_4;
			ret;
		}

	};

	uintptr_t jj_2;
	__declspec(naked) void jj_1() {
		__asm {

			mov eax, [ebp - 0x0B4];
			mov esi, [ebx + 0x38];
			mov edx, [ebp - 0x24];
			inc edx;

			push jj_2;
			ret;
		}

	};

	uintptr_t loc_12CDF48;
	uintptr_t loc_12CDF51;
	__declspec(naked) void s_1()
	{			
		__asm {
			cmp al, ESCAPE_SEQ_1;
			jz s_2;

			cmp al, ESCAPE_SEQ_2;
			jz s_2;

			cmp al, ESCAPE_SEQ_3;
			jz s_2;

			cmp al, ESCAPE_SEQ_4;
			jz s_2;
				
			lea ecx, [ebp - 0x1C];
			lea edx, [ecx + 1];

			push loc_12CDF48;
			ret;

		s_2:
			mov ecx, 3;
			cmp byte ptr[ebp - 0xCC], 0x10;
			lea eax, [ebp - 0xE0];
			cmovnb eax, [ebp - 0xE0];
			movzx ax, word ptr[eax + esi + 1];
			mov word ptr[ebp - 0x1C + 1], ax;
			add esi, 2;
			
			push loc_12CDF51;
			ret;
		}
	}

	uintptr_t t_2;
	uintptr_t t_3;
	__declspec(naked) void t_1()
	{
		__asm {
			cmp esi, ebx;
			jz t_3_jmp;

			push 0xFFFFFFFF;
			push 0;
			lea eax, [ebp - 0x178];

			push t_2;
			ret;

		t_3_jmp:
			push t_3;
			ret;
		}
	};

	uintptr_t r_4;
	__declspec(naked) void r_1()
	{
		__asm {
			cmp byte ptr[ecx + eax], ESCAPE_SEQ_1;
			jz r_10;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_2;
			jz r_11;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_3;
			jz r_12;

			cmp byte ptr[ecx + eax], ESCAPE_SEQ_4;
			jz r_13;

			jmp r_2;

		r_10:
			movzx eax, word ptr[ecx + eax + 1];
			jmp r_1x;

		r_11:
			movzx eax, word ptr[ecx + eax + 1];
			sub eax, SHIFT_2;
			jmp r_1x;

		r_12:
			movzx eax, word ptr[ecx + eax + 1];
			add eax, SHIFT_3;
			jmp r_1x;

		r_13:
			movzx eax, word ptr[ecx + eax + 1];
			add eax, SHIFT_4;
			jmp r_1x;

		r_2:
			movzx eax, byte ptr[ecx + eax];
			jmp r_3;

		r_1x:
			add ecx, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja r_3;
			mov eax, NOT_DEF;
		r_3:
			mov eax, [edi + eax * 4];
			
			push r_4;
			ret;
		}
	};

	uintptr_t aa_retn_address_1;
	__declspec(naked) void AA()
	{
		__asm {
			mov esi, eax;
			lea ecx, [ebp - 0xD4];
			mov eax, ecx;

			cmp dword ptr[eax + 0x14], 0x10;
			jb aa_2;

			mov eax, [eax];

		aa_2:
			mov al, [eax];

			cmp al, 0x10;
			jz aa_3;

			cmp al, 0x11;
			jz aa_3;

			cmp al, 0x12;
			jz aa_3;

			cmp al, 0x13;
			jz aa_3;

			jmp aa_4;

		aa_3:
			push 3;
			jmp aa_6;

		aa_4:
			push 1;

		aa_6:
			push aa_retn_address_1;
			ret;
		}
	};

	uintptr_t diff;
	uintptr_t b_5;
	uintptr_t b_3;
	__declspec(naked) void b_2()
	{
		__asm {
			mov[ebp - 0x43C], eax;
			mov eax, [edi + eax * 4 + 0x8C];
			mov[ebp - 0x3C], esi;

			push b_3;
			ret;
		}
	}

	__declspec(naked) void b_6()
	{
		__asm {
			movzx eax, al;
			jmp b_2;
		}
	}

	__declspec(naked) void b_1()
	{
		__asm {
			push ebx;
			mov ebx, edx;
			add ebx, diff;

			mov al, [edx + esi];
			mov [ebx + ecx], al;
			inc ecx;

			cmp al, ESCAPE_SEQ_1;
			jz b_10;

			cmp al, ESCAPE_SEQ_2;
			jz b_11;

			cmp al, ESCAPE_SEQ_3;
			jz b_12;

			cmp al, ESCAPE_SEQ_4;
			jz b_13;

			jmp b_4;

		b_10:
			movzx eax, word ptr[edx + esi + 1];
			mov[ebx + ecx], ax;
			jmp b_1x;

		b_11:
			movzx eax, word ptr[edx + esi + 1];
			mov[ebx + ecx], ax;
			sub eax, SHIFT_2;
			jmp b_1x;

		b_12:
			movzx eax, word ptr[edx + esi + 1];
			mov[ebx + ecx], ax;
			add eax, SHIFT_3;
			jmp b_1x;

		b_13:
			movzx eax, word ptr[edx + esi + 1];
			mov[ebx + ecx], ax;
			add eax, SHIFT_4;
			jmp b_1x;

		b_1x:
			pop ebx;

			add esi, 2;
			add ecx, 2;
			mov edx, [ebp - 0x18];
			movzx eax, ax;

			cmp eax, NO_FONT;
			ja b_2;
			mov eax, NOT_DEF;
			jmp b_2;

		b_4:
			pop ebx;

			mov [ebp - 0x34], ecx;
			mov edx, [ebp - 0x18];
			test ah, ah;
			jz b_6;
			
			push b_5;
			ret;
		}
	};

	// C
	uintptr_t c_2;
	uintptr_t loc_1942AD2;

	__declspec(naked) void c_1()
	{
		__asm {
			cmp dword ptr [ebp - 0x2C], 0;
			jz c_2_jmp;
			cmp dword ptr[ebp - 0x43C], 0x100;
			jg c_2_jmp;

			push loc_1942AD2;
			ret;

		c_2_jmp:
			push c_2;
			ret;
		}
	}

	/* */
	uintptr_t d_6;
	__declspec(naked) void d_1()
	{
		__asm {
			mov al, [ecx + edx];

			cmp al, ESCAPE_SEQ_1;
			jz d_10;

			cmp al, ESCAPE_SEQ_2;
			jz d_11;

			cmp al, ESCAPE_SEQ_3;
			jz d_12;

			cmp al, ESCAPE_SEQ_4;
			jz d_13;

			jmp d_4;

		d_10:
			movzx eax, word ptr[ecx + edx + 1];
			jmp d_2;

		d_11:
			movzx eax, word ptr[ecx + edx + 1];
			sub eax, SHIFT_2;
			jmp d_2;

		d_12:
			movzx eax, word ptr[ecx + edx + 1];
			add eax, SHIFT_3;
			jmp d_2;

		d_13:
			movzx eax, word ptr[ecx + edx + 1];
			add eax, SHIFT_4;
		
		d_2:
			mov byte ptr[ebp - 0x59], 0;
			add edx, 2;
			movzx eax, ax;

			cmp eax, NO_FONT;
			ja d_3;

			mov eax, NOT_DEF;

		d_3:
			mov[ebp - 0x1C], edx;
			jmp d_5;

		d_4:
			mov[ebp - 0x59], al;
			movzx eax, al;

		d_5:
			push d_6;
			ret;
		}
	}

	/* */
	uintptr_t u_4;
	uintptr_t u_2;
	__declspec(naked) void u_1()
	{
		__asm {
			mov al, [edi + esi];

			cmp al, ESCAPE_SEQ_1;
			jz u_3;

			cmp al, ESCAPE_SEQ_2;
			jz u_3;

			cmp al, ESCAPE_SEQ_3;
			jz u_3;

			cmp al, ESCAPE_SEQ_4;
			jz u_3;

			cmp al, 0xFE;
			
			push u_4;
			ret;

		u_3:
			add esi, 3;
			
			push u_2;
			ret;
		}
	}

	/* */
	uintptr_t v_4;
	uintptr_t v_1;
	__declspec(naked) void v_2()
	{
		__asm {
			mov al, [edi + esi];

			cmp al, ESCAPE_SEQ_1;
			jz v_3;

			cmp al, ESCAPE_SEQ_2;
			jz v_3;

			cmp al, ESCAPE_SEQ_3;
			jz v_3;

			cmp al, ESCAPE_SEQ_4;
			jz v_3;

			push v_4;
			ret;

		v_3:
			add esi, 3;

			push v_1;
			ret;
		}
	}

	uintptr_t dd_5;
	uintptr_t dd_4;
	__declspec(naked) void dd_1()
	{
		__asm {
			cmp cl, ESCAPE_SEQ_1;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_2;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_3;
			jz dd_3;

			cmp cl, ESCAPE_SEQ_4;
			jz dd_3;

			cmp cl, 0x20;
			jz dd_3;
			jmp dd_2;

		dd_3:
			mov eax, esi;

		dd_2:
			mov[ebp - 0x1C], eax;
			xor eax, eax;
			
			cmp cl, ESCAPE_SEQ_1;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_2;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_3;
			jz dd_6;

			cmp cl, ESCAPE_SEQ_4;
			jz dd_6;
			
			cmp cl, 0x20;
			jz dd_6;

			push dd_5;
			ret;

		dd_6:
			push dd_4;
			ret;
		}
	}

	uintptr_t k_2;
	__declspec(naked) void k_1()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz k_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz k_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz k_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz k_13;

			mov al, [eax + esi];
			movzx eax, al;
			jmp k_6;

		k_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp k_1x;

		k_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp k_1x;

		k_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp k_1x;

		k_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		k_1x:
			add esi, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja k_6;
			mov eax, NOT_DEF;

		k_6:
			mov ecx, [ebp - 0x20];
			
			cmp ax, 0x20;
			jz k_2_2;
			
			cmp ax, 0x100;
			ja k_2_2;

			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb k_2_5;

		k_2_6:
			mov word ptr[ebp - 0x8C + 2], 9;
			jmp k_2_3;

		k_2_5:
			cmp word ptr[ebp - 0x8C + 2], 9;
			jz k_2_6;

		k_2_2:
			mov word ptr[ebp - 0x8C + 2], ax;

		k_2_3:
			push k_2;
			ret;			
		}
	}

	uintptr_t w_2;
	__declspec(naked) void w_1()
	{
		__asm {
			cmp word ptr [ebp - 0x8C + 2], 0x100;
			jb w_3;

			sub esi, 2;

		w_3:
			mov eax, [ebp + 0x18];//arg_10
			add eax, [ebp - 0x24];

			push w_2;
			ret;
		}
	}

	uintptr_t ee_2;
	uintptr_t ee_3;
	__declspec(naked) void ee_1_1()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 9;
			jz ee_2_jmp;
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			ja ee_2_jmp;
			cmp ebx, [ebp - 0x18];
			jg ee_3_jmp;
			jmp ee_2_jmp;
		
		ee_2_jmp:
			push ee_2;
			ret;

		ee_3_jmp:
			push ee_3;
			ret;
		}
	}

	// dummy
	void __fastcall X_f1(void *p) {
		__asm {
			nop;
			nop;
			nop;
			nop;
			nop;
			nop;
			nop;
		}
	}

	uintptr_t x_2;
	__declspec(naked) void x_1()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_4;

			mov ecx, [eax + 0x10];
			sub ecx, 1;
			mov[eax + 0x10], ecx;

		x_4:
			lea ecx, [ebp - 0x70];

			call X_f1;
			
			push x_2;
			ret;
		}
	}

	uintptr_t loc_194690F;
	__declspec(naked) void x_5()
	{
		__asm {
			cmp word ptr[ebp - 0x8C + 2], 0x100;
			jb x_6;
			sub esi, 1;
		x_6:
			mov[ebp - 0x14], 0;
			push loc_194690F;
			ret;
		}
	}

	uintptr_t cc_4;
	__declspec(naked) void cc_1()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz cc_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz cc_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz cc_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz cc_13;

			movzx eax, byte ptr[eax + esi];
			jmp cc_3;

		cc_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp cc_6;

		cc_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp cc_6;

		cc_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp cc_6;
		
		cc_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;

		cc_6:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja cc_2;
			mov eax, NOT_DEF;

		cc_2:
			add esi, 2;

		cc_3:
			mov ecx, [esp + 0x48 - 0x28];

			push cc_4;
			ret;
		}
	}

	uintptr_t l_5;
	__declspec(naked) void l_1()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz l_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz l_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz l_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz l_13;

			jmp l_2;

		l_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp l_1x;
		l_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp l_1x;
		l_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp l_1x;
		l_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			jmp l_1x;

		l_1x:
			add esi, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja l_3
			mov eax, NOT_DEF;
		l_3:
			jmp l_4;

		l_2:
			movzx eax, byte ptr[eax + esi];
		l_4:
			mov edx, [ebp - 0x0C];
			push l_5;
			ret;
		}
	}

	uintptr_t p_5;
	__declspec(naked) void p_1()
	{
		__asm {
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz p_10;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz p_11;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz p_12;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz p_13;

			mov al, [eax + ebx];
			lea ecx, [ebp - 0xFC];
			mov byte ptr[ebp - 0x34], al;

			push p_5;
			ret;

		p_10:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x34];
			mov byte ptr[ecx], ESCAPE_SEQ_1;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_11:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x34];
			mov byte ptr[ecx], ESCAPE_SEQ_2;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_12:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x34];
			mov byte ptr[ecx], ESCAPE_SEQ_3;
			mov[ecx + 1], ax;
			jmp p_1x;

		p_13:
			movzx eax, word ptr[eax + ebx + 1];
			lea ecx, [ebp - 0x34];
			mov byte ptr[ecx], ESCAPE_SEQ_4;
			mov[ecx + 1], ax;

		p_1x:
			lea ecx, [ebp - 0xFC];

			push p_5;
			ret;
		}
	}

	uintptr_t q_4;
	__declspec(naked) void q_1()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz q_2;

			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz q_2;

			jmp q_3;

		q_2:
			mov ecx, [ebp - 0x34];
			mov[eax], ecx;
			mov byte ptr[eax + 0x10], 3;

		q_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;

			push q_4;
			ret;
		}
	}

	uintptr_t o_5;
	__declspec(naked) void o_1()
	{
		__asm {
			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz o_10;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz o_11;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz o_12;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz o_13;

			jmp o_3;

		o_10:
			movzx eax, word ptr[eax + ebx + 1];
			jmp o_1x;

		o_11:
			movzx eax, word ptr[eax + ebx + 1];
			sub eax, SHIFT_2;
			jmp o_1x;

		o_12:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_3;
			jmp o_1x;

		o_13:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_4;
	
		o_1x:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja o_2;
			mov eax, NOT_DEF;

		o_2:
			add ebx, 2;
			jmp o_4;

		o_3:
			movzx eax, byte ptr[eax + ebx];

		o_4:
			mov edx, [ebp - 0x20];

			push o_5;
			ret;
		}
	}

	uintptr_t n_4;
	__declspec(naked) void n_1()
	{
		__asm {
			cmp byte ptr[eax + ecx], ESCAPE_SEQ_1;
			jz n_10;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_2;
			jz n_11;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_3;
			jz n_12;

			cmp byte ptr[eax + ecx], ESCAPE_SEQ_4;
			jz n_13;

			jmp n_3;

		n_10:
			movzx eax, word ptr[eax + ecx + 1];
			jmp n_1x;

		n_11:
			movzx eax, word ptr[eax + ecx + 1];
			sub eax, SHIFT_2;
			jmp n_1x;

		n_12:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_3;
			jmp n_1x;

		n_13:
			movzx eax, word ptr[eax + ecx + 1];
			add eax, SHIFT_4;

		n_1x:
			add ecx, 2;
			movzx eax, ax;
			mov[ebp - 0x14], ecx;

			cmp eax, NO_FONT;
			ja n_2;
			mov eax, NOT_DEF;

		n_2:
			jmp n_5;

		n_3:
			movzx eax, byte ptr[eax + ecx];
		n_5:
			mov edx, [edx + eax * 4 + 0x8C];

			push n_4;
			ret;
		}
	}

	uintptr_t j_7;
	uintptr_t j_8;
	__declspec(naked) void j_1()
	{
		__asm {
			mov al, [esi + edx];

			cmp al, ESCAPE_SEQ_1;
			jz j_10;

			cmp al, ESCAPE_SEQ_2;
			jz j_11;

			cmp al, ESCAPE_SEQ_3;
			jz j_12;

			cmp al, ESCAPE_SEQ_4;
			jz j_13;

			mov[ebp - 0x2], al;
			movzx eax, al;
			jmp j_6

		j_10:
			movzx eax, word ptr[esi + edx + 1];
			jmp j_2;

		j_11:
			movzx eax, word ptr[esi + edx + 1];
			sub eax, SHIFT_2;
			jmp j_2;

		j_12:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_3;
			jmp j_2;

		j_13:
			movzx eax, word ptr[esi + edx + 1];
			add eax, SHIFT_4;
		
		j_2:
			movzx eax, ax;
			cmp eax, NO_FONT;

			ja j_3;
			mov eax, NOT_DEF;

		j_3:
			mov[ebp - 0x2], 0x10;
			add esi, 2;

			cmp esi, ebx;
			jnb j_4;

		j_6:
			mov ecx, [ebp - 0x10];
			push j_7;
			ret;

		j_4:
			mov ecx, [ebp - 0x8];
			push j_8;
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

			jmp e_3;

		e_10:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0xC4];
			mov byte ptr[ecx], ESCAPE_SEQ_1;
			mov[ecx + 1], ax;
			jmp e_2;

		e_11:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0xC4];
			mov byte ptr[ecx], ESCAPE_SEQ_2;
			mov[ecx + 1], ax;
			jmp e_2;

		e_12:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0xC4];
			mov byte ptr[ecx], ESCAPE_SEQ_3;
			mov[ecx + 1], ax;
			jmp e_2;

		e_13:
			movzx eax, word ptr[eax + esi + 1];
			lea ecx, [ebp - 0xC4];
			mov byte ptr[ecx], ESCAPE_SEQ_4;
			mov[ecx + 1], ax;
			jmp e_2;

		e_2:
			lea ecx, [ebp - 0x80];
			jmp e_5_jmp;

		e_3:
			mov al, [eax + esi];
			lea ecx, [ebp - 0x80];
			mov byte ptr[ebp - 0xC4], al;
		
		e_5_jmp:
			push e_5;
			ret;
		}
	}

	uintptr_t f_5;
	__declspec(naked) void f_1()
	{
		__asm {
			cmp byte ptr[eax], ESCAPE_SEQ_1;
			jz f_2;

			cmp byte ptr[eax], ESCAPE_SEQ_2;
			jz f_2;

			cmp byte ptr[eax], ESCAPE_SEQ_3;
			jz f_2;

			cmp byte ptr[eax], ESCAPE_SEQ_4;
			jz f_2;

			jmp f_3;

		f_2:
			mov ecx, [ebp - 0xC4];
			mov[eax], ecx;
			mov byte ptr[eax + 0x10], 3;

		f_3:
			push 0xFFFFFFFF;
			push 0;
			push eax;
			
			push f_5;
			ret;
		}
	}

	uintptr_t g_5;
	__declspec(naked) void g_1()
	{
		__asm {
			cmovnb eax, edx;
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz g_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz g_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz g_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz g_13;

			jmp g_3;

		g_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp g_2;

		g_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp g_2;

		g_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp g_2;

		g_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			jmp g_2;
		
		g_2:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja g_4;
			mov eax, NOT_DEF;
		
		g_4:
			add esi, 2;
			jmp g_6;

		g_3:
			movzx eax, byte ptr[eax + esi];

		g_6:
			mov[ebp - 0x380], eax;

			push g_5;
			ret;
		}
	}

	uintptr_t h_2;
	uintptr_t loc_19417DE;
	__declspec(naked) void h_1()
	{
		__asm {
			mov byte ptr[ebp - 0x5C], 0;
			jz h_2_jmp;
			cmp[ebp - 0x380], 0x100;
			jg h_2_jmp;

			push loc_19417DE;
			ret;

		h_2_jmp:
			push h_2;
			ret;
		}
	}

	uintptr_t i_6;
	__declspec(naked) void i_1()
	{
		__asm {
			cmovnb eax, edi;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_1;
			jz i_10;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_2;
			jz i_11;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_3;
			jz i_12;

			cmp byte ptr[eax + ebx], ESCAPE_SEQ_4;
			jz i_13;

			movzx eax, byte ptr[eax + ebx];
			push i_6;
			ret;

		i_10:
			movzx eax, word ptr[eax + ebx + 1];
			jmp i_3;

		i_11:
			movzx eax, word ptr[eax + ebx + 1];
			sub eax, SHIFT_2;
			jmp i_3;

		i_12:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_3;
			jmp i_3;

		i_13:
			movzx eax, word ptr[eax + ebx + 1];
			add eax, SHIFT_4;

		i_3:
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja i_4;
			mov eax, NOT_DEF;
		i_4:
			add ebx, 2;
			mov[ebp - 0x14], ebx;

			push i_6;
			ret;
		}
	}

	uintptr_t aa_5;
	__declspec(naked) void aa_1()
	{
		__asm {
			mov esi, eax;
			lea ecx, [ebp - 0xD4];
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb aa_2;
			mov eax, [eax];

		aa_2:
			mov al, [eax];
			cmp al, ESCAPE_SEQ_1;
			jz aa_3;

			cmp al, ESCAPE_SEQ_2;
			jz aa_3;
			
			cmp al, ESCAPE_SEQ_3;
			jz aa_3;

			cmp al, ESCAPE_SEQ_4;
			jz aa_3;

			jmp aa_4;

		aa_3:
			push 3;
			jmp aa_6;

		aa_4:
			push 1;

		aa_6:
			push aa_5;
			ret;
		}
	}

	uintptr_t bb_6;
	__declspec(naked) void bb_1()
	{
		__asm {
			lea ecx, [ebp - 0xD4];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb bb_2;
			mov ecx, [ecx];

		bb_2:
			mov cl, [ecx];

			cmp cl, ESCAPE_SEQ_1;
			jz bb_3;

			cmp cl, ESCAPE_SEQ_2;
			jz bb_3;

			cmp cl, ESCAPE_SEQ_3;
			jz bb_3;

			cmp cl, ESCAPE_SEQ_4;
			jz bb_3;

			jmp bb_4;

		bb_3:
			push 3;
			jmp bb_5;

		bb_4:
			push 1;

		bb_5:
			push eax;
			lea ecx, [ebp - 0xD4];

			push bb_6;
			ret;
		}
	}

	uintptr_t ll_5;
	__declspec(naked) void ll_1()
	{
		__asm {
			lea ecx, [ebp - 0x88];
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb ll_4;
			mov eax, [eax];
		
		ll_4:
			mov al, [eax];
			
			cmp al, ESCAPE_SEQ_1;
			jz ll_3;

			cmp al, ESCAPE_SEQ_2;
			jz ll_3;

			cmp al, ESCAPE_SEQ_3;
			jz ll_3;

			cmp al, ESCAPE_SEQ_4;
			jz ll_3;

			push 1;
			jmp ll_2;

		ll_3:
			push 3;

		ll_2:
			lea eax, [ebp - 0x168];
			push 0;

			push ll_5;
			ret;
		}
	}

	uintptr_t mm_5;
	__declspec(naked) void mm_1()
	{
		__asm {
			lea ecx, [ebp - 0x88];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb mm_3;
			mov ecx, [ecx];

		mm_3:
			mov cl, [ecx];
			cmp cl, ESCAPE_SEQ_1;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_2;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_3;
			jz mm_2;

			cmp cl, ESCAPE_SEQ_4;
			jz mm_2;

			push 1;
			jmp mm_4;

		mm_2:
			push 3;

		mm_4:
			push eax;
			lea ecx, [ebp - 0x88];

			push mm_5;
			ret;
		}
	}

	uintptr_t y_5;
	__declspec(naked) void y_8()
	{
		__asm {
			lea ecx, [ebp - 0x168];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb y_8_;
			mov ecx, [ecx];

		y_8_:
			mov al, [ecx];

			cmp al, ESCAPE_SEQ_1;
			jz y_4;

			cmp al, ESCAPE_SEQ_2;
			jz y_4;

			cmp al, ESCAPE_SEQ_3;
			jz y_4;

			cmp al, ESCAPE_SEQ_4;
			jz y_4;

			jmp y_2;

		y_4:
			push 3;
			jmp y_3;

		y_2:
			push 1;

		y_3:
			push 0;
			lea eax, [ebp - 0xAA4];

			push y_5;
			ret;
		}
	}

	uintptr_t z_6;
	__declspec(naked) void z_8()
	{
		__asm {
			lea ecx,[ebp - 0x168];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb z_8_;
			mov ecx, [ecx];

		z_8_:
			mov al, [ecx];

			cmp al, ESCAPE_SEQ_1;
			jz z_2;

			cmp al, ESCAPE_SEQ_2;
			jz z_2;

			cmp al, ESCAPE_SEQ_3;
			jz z_2;

			cmp al, ESCAPE_SEQ_4;
			jz z_2;

			jmp z_3;

		z_2:
			push 3;
			jmp z_4;

		z_3:
			push 1;

		z_4:
			lea eax, [ebp - 0xAD4];

			lea ecx, [ebp - 0x168];

			push z_6;
			ret;
		}
	}

	uintptr_t ff_5;
	__declspec(naked) void ff_1()
	{
		__asm {
			mov edi, eax;
			lea ecx, [ebp - 0x34];
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb ff_2;
			mov eax, [eax];

		ff_2:
			mov al, [eax];

			cmp al, ESCAPE_SEQ_1;
			jz ff_3;

			cmp al, ESCAPE_SEQ_2;
			jz ff_3;

			cmp al, ESCAPE_SEQ_3;
			jz ff_3;

			cmp al, ESCAPE_SEQ_4;
			jz ff_3;

			push 1;
			jmp ff_4;

		ff_3:
			push 3;

		ff_4:
			push ff_5;
			ret;
		}
	}

	uintptr_t gg_4;
	__declspec(naked) void gg_1()
	{
		__asm {
			lea ecx, [ebp - 0x34];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb gg_2;
			mov ecx, [ecx];

		gg_2:
			mov cl, [ecx];
			cmp cl, ESCAPE_SEQ_1;
			jz gg_3;

			cmp cl, ESCAPE_SEQ_2;
			jz gg_3;

			cmp cl, ESCAPE_SEQ_3;
			jz gg_3;

			cmp cl, ESCAPE_SEQ_4;
			jz gg_3;

			push 1;
			jmp gg_5;

		gg_3:
			push 3;

		gg_5:
			push eax;
			lea ecx, [ebp - 0x34];

			push gg_4;
			ret;
		}
	}

	uintptr_t hh_6;
	__declspec(naked) void hh_1()
	{
		__asm {
			mov edi, eax;
			lea ecx, [ebp - 0x70];
			mov eax, ecx;
			cmp dword ptr[eax + 0x14], 0x10;
			jb hh_2;
			mov eax, [eax];

		hh_2:
			mov al, [eax];
			cmp al, ESCAPE_SEQ_1;
			jz hh_3;

			cmp al, ESCAPE_SEQ_2;
			jz hh_3;

			cmp al, ESCAPE_SEQ_3;
			jz hh_3;

			cmp al, ESCAPE_SEQ_4;
			jz hh_3;

			push 1;
			jmp hh_4;

		hh_3:
			push 3;

		hh_4:
			push hh_6;
			ret;
		}
	}

	uintptr_t ii_5;
	__declspec(naked) void ii_1()
	{
		__asm {
			lea ecx, [ebp - 0x70];
			cmp dword ptr[ecx + 0x14], 0x10;
			jb ii_2;
			mov ecx, [ecx];

		ii_2:
			mov cl, [ecx];
			cmp cl, ESCAPE_SEQ_1;
			jz ii_3;

			cmp cl, ESCAPE_SEQ_2;
			jz ii_3;

			cmp cl, ESCAPE_SEQ_3;
			jz ii_3;

			cmp cl, ESCAPE_SEQ_4;
			jz ii_3;

			push 1;
			jmp ii_4;

		ii_3:
			push 3;

		ii_4:
			push eax;
			lea ecx, [ebp - 0x70];

			push ii_5;
			ret;
		}
	}

	uintptr_t xx_end;
	uintptr_t xx_end2;
	__declspec(naked) void heap_alloc_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 1;
		}
	}
	__declspec(naked) void heap_free_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 2;
		}
	}
	__declspec(naked) void PHYSFS_utf8ToUcs2_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 3;
		}
	}
	__declspec(naked) void sub_122FEC0_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 4;
		}
	}

	__declspec(naked) void xx_start()
	{
		__asm {
			mov ecx, [ebp - 0x64];

			cmp ch, 0;
			jnz xx_1;

			xor esi, esi;
			push xx_end;
			ret;

		xx_1:
			push 0xFF;	/* dwBytes */
			call heap_alloc_f1;
			pop ecx;

			test eax, eax;
			jz xx_1;
			
			push 0;
			push 0xFF;
			lea eax, [eax];
			mov[ebp - 0x74], eax;
			push eax;
			lea ecx, [ebp - 0x64];
			push ecx;
			call PHYSFS_utf8ToUcs2_f1;
			add esp, 0x10;

			push 0xFF; /* dwBytes */
			call heap_alloc_f1;
			pop ecx;

			/* push */
			push edi;
			push ebx;

			xor edi, edi;
			mov[ebp - 0x78], eax;

			xor esi, esi;

		xx_2:
			mov eax, [ebp - 0x74];
			movzx ax, word ptr[eax + esi];

			// 終了
			cmp ax, 0;
			jz xx_10;

			// 2バイトじゃない
			cmp ah, 0;
			jz xx_2_1;

			xor ecx, ecx;
			mov ecx, ESCAPE_SEQ_1;

			cmp ah, 0xA4;
			jz xx_4;

			cmp ah, 0xA3;
			jz xx_4;

			cmp ah, 0xA7;
			jz xx_4;

			cmp ah, 0x24;
			jz xx_4;

			cmp ah, 0x5B;
			jz xx_4;

			cmp ah, 0x0;
			jz xx_4;

			cmp ah, 0x5C;
			jz xx_4;

			cmp ah, 0x20;
			jz xx_4;

			cmp ah, 0x0D;
			jz xx_4;

			cmp ah, 0x0A;
			jz xx_4;

			cmp ah, 0x22;
			jz xx_4;

			cmp ah, 0x7B;
			jz xx_4;

			cmp ah, 0x7D;
			jz xx_4;

			cmp ah, 0x40;
			jz xx_4;

			cmp ah, 0x3B;
			jz xx_4;

			cmp ah, 0x80;
			jz xx_4;

			cmp ah, 0x7E;
			jz xx_4;

			cmp ah, 0xBD;
			jz xx_4;

			cmp ah, 0x5F;
			jnz xx_3;

		xx_4:
			add ecx, 2;

		xx_3:
			cmp al, 0xA4;
			jz xx_5;

			cmp al, 0xA3;
			jz xx_5;

			cmp al, 0xA7;
			jz xx_5;

			cmp al, 0x24;
			jz xx_5;

			cmp al, 0x5B;
			jz xx_5;

			cmp al, 0x0;
			jz xx_5;

			cmp al, 0x5C;
			jz xx_5;

			cmp al, 0x20;
			jz xx_5;

			cmp al, 0x0D;
			jz xx_5;

			cmp al, 0x0A;
			jz xx_5;

			cmp al, 0x22;
			jz xx_5;

			cmp al, 0x7B;
			jz xx_5;

			cmp al, 0x7D;
			jz xx_5;

			cmp al, 0x40;
			jz xx_5;

			cmp al, 0x3B;
			jz xx_5;

			cmp al, 0x80;
			jz xx_5;

			cmp al, 0x7E;
			jz xx_5;

			cmp al, 0xBD;
			jz xx_5;

			cmp al, 0x5F;
			jnz xx_6;

		xx_5:
			add ecx, 1;

		xx_6:
			cmp ecx, ESCAPE_SEQ_2;
			jnz xx_6_1;
			add al, LOW_SHIFT;
			jmp xx_7;

		xx_6_1:
			cmp ecx, ESCAPE_SEQ_3;
			jnz xx_6_2;
			sub ah, HIGH_SHIFT;
			jmp xx_7;

		xx_6_2:
			cmp ecx, ESCAPE_SEQ_4;
			jnz xx_7;
			add al, LOW_SHIFT;
			sub ah, HIGH_SHIFT;
		
		xx_7:
			add esi, 2;
			mov ebx, [ebp - 0x78];
			mov[ebx + edi], cl;
			mov[ebx + edi + 1], ax;
			add edi, 3;

			jmp xx_2;

		xx_2_1:
			inc esi;
			mov ebx, [ebp - 0x78];
			mov byte ptr [ebx + edi], al;
			inc edi;

			jmp xx_2;

		/* LOOP END */

		xx_10:
			/* pop */
			pop ebx;
			pop edi;

			/* count */
			xor esi, esi;

		xx_12:
			mov ecx, [ebp - 0x78];
			movzx ecx,byte ptr [ecx + esi];

			cmp cl, 0;
			jz xx_13;

			/*  edi */
			/* eax, esi, ecx */

			lea eax, [ebp - 0x1C];
			mov[ebp - 0x1C], ecx;
			mov edx, [edi];
			lea ecx, [ebp - 0x38];
			push eax;
			mov[ebp - 0x18], 1;
			call sub_122FEC0_f1;
			push eax;
			mov ecx, edi;
			mov edx,[edi];
			call dword ptr[edx + 0x28];

			inc esi;
			jmp xx_12;

		xx_13:

			push[ebp - 0x74];
			call heap_free_f1;

			push[ebp - 0x78];
			call heap_free_f1;

			pop ecx;
			pop ecx;

			push xx_end2;
			ret;
		}
	}

	uintptr_t loc_172DEE2;
	__declspec(naked) void yy_1() {
		__asm {
			// store reg / counter
			push esi;
			xor esi, esi;

			mov eax, [edi + 0x28]; // 文字列長さ
			
			lea ecx, [edi + 0x18]; // テキスト

			cmp eax, 0x10;
			jbe yy_2;

			mov ecx, [ecx];

		yy_2:
			mov eax, [edi + 0x34]; // キャレット位置
			sub eax, 3;
			js yy_3;
			mov al, [ecx + eax];

			cmp al, ESCAPE_SEQ_1;
			jz yy_4;

			cmp al, ESCAPE_SEQ_2;
			jz yy_4;

			cmp al, ESCAPE_SEQ_3;
			jz yy_4;

			cmp al, ESCAPE_SEQ_4;
			jnz yy_3;

		yy_4:
			mov esi, 2;

		yy_3:
			mov eax, [edi];
			mov ecx, edi;

			test bl, bl;
			jnz yy_6;

			call dword ptr[eax + 0xA0];
			jmp yy_5;

		yy_6:
			call dword ptr[eax + 0x9C];

		yy_5:
			cmp esi, 0;
			jz yy_7;

			sub esi, 1;
			jmp yy_3;

		yy_7:
			// restore reg / counter
			pop esi;

			pop ebx;

			push loc_172DEE2;
			ret;
		}
	}

	uintptr_t zz_21;
	uintptr_t loc_18AB507;
	__declspec(naked) void zz_8() {
		__asm {
			add esp, 0x14;
			test eax, eax;
			jz loc_18AB507_jmp;

			push zz_21;
			ret;

		loc_18AB507_jmp:
			push loc_18AB507;
			ret;
		}
	}

	uintptr_t zz_4;
	uintptr_t loc_18C8D09;
	__declspec(naked) void SDL_SetTextInputRect_f1() {
		__asm {
			nop;
			nop;
			nop;
			add eax, 5;
		}
	}
	__declspec(naked) void zz_2() {
		__asm {
			jz zz_5;
			
			push zz_4;
			ret;

		zz_5:
			sub esp, 8;
			mov ecx, [ebp + 0x18];
			mov edx, [ebp + 8];
			mov[ecx + 0x38], edx;
			mov dword ptr[ebp - 0x14], 0;
			mov dword ptr[ebp - 0x10], 0;
			lea eax, [ebp - 0x14];
			push eax;
			call SDL_SetTextInputRect_f1;
			add esp, 0x0C;
			
			push loc_18C8D09;
			ret;
		}
	}

	uintptr_t issue_suffix_id_r;
	uintptr_t loc_8858F2;
	__declspec(naked) void issue_suffix_id() {
		__asm {
			mov edx, [ebp - 0x18];
			mov esi, [ebp - 0x2C];

			cmp ecx, 3;
			jl issue_suffix_id_ret;

			cmp edx, 0x10;
			lea eax, [ebp - 0x2C];
			cmovnb eax, esi;

			cmp byte ptr[ecx + eax - 3], 0x10;
			jz issue_suffix_id_fix;
			cmp byte ptr[ecx + eax - 3], 0x11;
			jz issue_suffix_id_fix;
			cmp byte ptr[ecx + eax - 3], 0x12;
			jz issue_suffix_id_fix;
			cmp byte ptr[ecx + eax - 3], 0x13;
			jz issue_suffix_id_fix;

			jmp issue_suffix_id_ret;

		issue_suffix_id_fix:
			push loc_8858F2;
			ret;

		issue_suffix_id_ret:

			push issue_suffix_id_r;
			ret;
		}

	}

	void InitAndPatch() {

		/* sub_12CC4E0 */
		//M用にスタック修正
		byte_pattern::temp_instance().find_pattern("81 EC 78 01 00 00 8B 43 18");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x7A, true);
		}
		//マップフォント表示
		byte_pattern::temp_instance().find_pattern("0F B6 04 10 8B 34 86");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), m_1);
			m_5 = byte_pattern::temp_instance().get_first().address(7);
		}
		//マップテキストの表示位置調整
		byte_pattern::temp_instance().find_pattern("48 F3 0F 51 C9 66 0F 6E");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), kk_1);
			kk_4 = byte_pattern::temp_instance().get_first().address(5);
		}
		//マップフォントの位置調整
		byte_pattern::temp_instance().find_pattern("8B 85 4C FF FF FF 8B 73");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(-0xE), 0x90, true);
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), jj_1);
			jj_2 = byte_pattern::temp_instance().get_first().address(9);
		}
		// スタックの後始末
		byte_pattern::temp_instance().find_pattern("8D A5 80 FE FF FF");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x7E, true);
		}
		/* sub_12CC4E0 */

		/* sub_12CD260 */
		//
		byte_pattern::temp_instance().find_pattern("8D 4D E4 8D 51 01 8A 01 41");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), s_1);
		}
		byte_pattern::temp_instance().find_pattern("8A 01 41 84 C0 75 F9 2B CA 51 8D 45 E4 50");
		if (byte_pattern::temp_instance().has_size(2)) {
			loc_12CDF48 = byte_pattern::temp_instance().get_first().address();
		}
		byte_pattern::temp_instance().find_pattern("51 8D 45 E4 50 8D 8D 48");
		if (byte_pattern::temp_instance().has_size(2)) {
			loc_12CDF51 = byte_pattern::temp_instance().get_first().address();
		}
		//
		byte_pattern::temp_instance().find_pattern("6A FF 6A 00 8D 85 88 FE FF FF 50");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), t_1);
			t_2 = byte_pattern::temp_instance().get_first().address(10);
		}
		byte_pattern::temp_instance().find_pattern("8B 75 08 8D 45 E0 50 8D");
		if (byte_pattern::temp_instance().has_size(1)) {
			t_3 = byte_pattern::temp_instance().get_first().address(0);
		}
		//
		byte_pattern::temp_instance().find_pattern("0F B6 04 01 8B 04 87 85");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), r_1);
			r_4 = byte_pattern::temp_instance().get_first().address(0x07);
		}
		/* sub_12CD260 */

		/* フォントのバッファ拡張（ランチャー）*/
		byte_pattern::temp_instance().find_pattern("68 90 26 00 00");
		if (byte_pattern::temp_instance().has_size(3)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(3), 0x04, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(3), 0x04, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(2).address(3), 0x04, true);
		}
		/* フォントのバッファ拡張（ランチャー）*/

		/* sub_149BC00 終了ダイアログ時の花文字の修正 */
		byte_pattern::temp_instance().find_pattern("6A 01 8B F0 8D 8D 2C");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), aa_1);
			aa_5 = byte_pattern::temp_instance().get_first().address(10);
		}
		byte_pattern::temp_instance().find_pattern("E8 ? ? ? ? FF B5 3C FF FF FF 8D 45");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xE), bb_1);
			bb_6 = byte_pattern::temp_instance().get_first().address(0x17);
		}
		/* sub_149BC00 */

		/* sub_149E0B0 終了ダイアログ時の花文字の修正 */
		byte_pattern::temp_instance().find_pattern("6A 01 6A 00 8D 85 98");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), ll_1);
			ll_5 = byte_pattern::temp_instance().get_first().address(10);
		}
		byte_pattern::temp_instance().find_pattern("6A 01 50 8D 8D 78 FF FF FF E8");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), mm_1);
			mm_5 = byte_pattern::temp_instance().get_first().address(9);
		}
		/* sub_149E0B0 */

		/* sub_14EC330 花文字 */
		byte_pattern::temp_instance().find_pattern("6A 01 6A 00 8D 85 5C F5 FF");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), y_8);
			y_5 = byte_pattern::temp_instance().get_first().address(10);
		}
		byte_pattern::temp_instance().find_pattern("8D 8D 98 FE FF FF 6A 01 8D");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), z_8);
			z_6 = byte_pattern::temp_instance().get_first().address(14);
		}
		/* sub_14EC330 */

		/* sub_1763AA0 継承画面の花文字 */
		byte_pattern::temp_instance().find_pattern("6A 01 8B F8 8D 4D CC");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), ff_1);
			ff_5 = byte_pattern::temp_instance().get_first().address(7);
		}
		byte_pattern::temp_instance().find_pattern("6A 01 50 8D 4D CC E8");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), gg_1);
			gg_4 = byte_pattern::temp_instance().get_first().address(6);
		}
		/* sub_1763AA0 継承画面の花文字 */

		/* sub_17641E0 花文字 */
		byte_pattern::temp_instance().find_pattern("6A 01 8B F8 8D 4D 90 6A");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), hh_1);
			hh_6 = byte_pattern::temp_instance().get_first().address(7);
		}
		byte_pattern::temp_instance().find_pattern("6A 01 50 8D 4D 90 E8");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), ii_1);
			ii_5 = byte_pattern::temp_instance().get_first().address(6);
		}
		/* sub_17641E0 花文字 */

		/* フォントのバッファ拡張（本体）*/
		byte_pattern::temp_instance().find_pattern("68 84 26 00 00");
		if (byte_pattern::temp_instance().has_size(3)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(3), 0x04, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(3), 0x04, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(2).address(3), 0x04, true);
		}
		/* フォントのバッファ拡張（本体）*/

		/* sub_1941060 ボタン（UI） */
		// スタック修正
		byte_pattern::temp_instance().find_pattern("81 EC 70 03 00 00 8B");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x78, true);
		}
		byte_pattern::temp_instance().find_pattern("8A 04 30 88 85 3C FF FF");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(),e_1 );
			e_5 = byte_pattern::temp_instance().get_first().address(9);

			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), f_1);
			f_5 = byte_pattern::temp_instance().get_first().address(0x19);
		}
		byte_pattern::temp_instance().find_pattern("0F 43 C2 0F B6 04 30 8B 84 83");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), g_1);
			g_5 = byte_pattern::temp_instance().get_first().address(7);
		}
		byte_pattern::temp_instance().find_pattern("83 7D A4 00 0F 85 9B");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), h_1);
			h_2 = byte_pattern::temp_instance().get_first().address(10);
		}
		byte_pattern::temp_instance().find_pattern("46 3B 75 E4 0F 8C AA F9");
		if (byte_pattern::temp_instance().has_size(1)) {
			loc_19417DE = byte_pattern::temp_instance().get_first().address();
		}
		// スタック後始末の修正
		byte_pattern::temp_instance().find_pattern("8D A5 78 FC FF FF");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x70, true);
		}
		byte_pattern::temp_instance().find_pattern("0F 43 C7 0F B6 04 18 8B");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), i_1);
			i_6 = byte_pattern::temp_instance().get_first().address(7);
		}
		/* sub_1941060 */

		/* sub_19423E0 本文 */
		// スタック修正
		byte_pattern::temp_instance().find_pattern("81 EC 28 04 00 00 56 57 8B F9");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x30, true);
		}
		// 転送バッファ
		byte_pattern::temp_instance().find_pattern("8A 86 ? ? ? ? 88 81 ? ? ? ? 41");
		if (byte_pattern::temp_instance().has_size(1)) {
			char *pSRC = *byte_pattern::temp_instance().get_first().pointer<char *>(2);
			char *pDST = *byte_pattern::temp_instance().get_first().pointer<char *>(8);

			diff = pDST - pSRC;

			injector::WriteMemory<char *>(byte_pattern::temp_instance().get_first().address(8), pSRC, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x8D, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x15, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(6), 0x8D, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(7), 0x15, true);
		}
		byte_pattern::temp_instance().find_pattern("41 89 4D CC 84 E4 0F");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), b_1);
			b_5 = byte_pattern::temp_instance().get_first().address(12);
		}
		byte_pattern::temp_instance().find_pattern("8B 84 87 8C 00 00 00 89");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), b_6);
			b_3 = byte_pattern::temp_instance().get_first().address(7);
		}
		byte_pattern::temp_instance().find_pattern("83 7D D4 00 0F 85 FA 00 00");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0), c_1);
			c_2 = byte_pattern::temp_instance().get_first().address(10);
		}
		byte_pattern::temp_instance().find_pattern("80 3D ? ? ? ? 00 0F 84 47");
		if (byte_pattern::temp_instance().has_size(1)) {
			loc_1942AD2 = byte_pattern::temp_instance().get_first().address();
		}
		byte_pattern::temp_instance().find_pattern("8A 82 ? ? ? ? 88 45 A7 0F B6");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x8D, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x0D, true);
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(6), d_1);
			d_6 = byte_pattern::temp_instance().get_first().address(12);
		}
		/* sub_19423E0 本文 */

		/* sub_1943B70 */
		byte_pattern::temp_instance().find_pattern("8A 04 16 8B 4D F0 88");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), j_1);
			j_7 = byte_pattern::temp_instance().get_first().address(12);
		}
		byte_pattern::temp_instance().find_pattern("3B F9 0F 4F CF 5F 5E 8B");
		if (byte_pattern::temp_instance().has_size(1)) {
			j_8 = byte_pattern::temp_instance().get_first().address();
		}
		/* sub_1943B70 */

		/* sub_1945620 マップフォント */
		byte_pattern::temp_instance().find_pattern("8A 04 18 8D 8D 04 FF");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), p_1);
			p_5 = byte_pattern::temp_instance().get_first().address(12);

			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x14), q_1);
			q_4 = byte_pattern::temp_instance().get_first().address(0x19);
		}
		byte_pattern::temp_instance().find_pattern("0F B6 04 18 8B 55 E0");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), o_1);
			o_5 = byte_pattern::temp_instance().get_first().address(7);
		}
		byte_pattern::temp_instance().find_pattern("0F B6 04 08 8B 94 82 8C");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), n_1);
			n_4 = byte_pattern::temp_instance().get_first().address(11);
		}
		/* sub_1945620 */

		/* sub_1945F30 */
		byte_pattern::temp_instance().find_pattern("8B 55 F4 0F B6 04 30");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), l_1);
			l_5 = byte_pattern::temp_instance().get_first().address(7);
		}
		/* sub_1945F30 */

		/* sub_1946210 */
		byte_pattern::temp_instance().find_pattern("0F B6 04 30 8B 4C 24");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), cc_1);
			cc_4 = byte_pattern::temp_instance().get_first().address(8);
		}
		/* sub_1946210 */

		/* sub_19465B0　？ */
		//スタック修正
		byte_pattern::temp_instance().find_pattern("83 EC 7C 53 8B 5D 0C 56 57");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x7E, true);
		}
		byte_pattern::temp_instance().find_pattern("80 F9 20 0F 44 C6 89 45");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), dd_1);
			dd_5 = byte_pattern::temp_instance().get_first().address(14);
			dd_4 = byte_pattern::temp_instance().get_first().address(0x12);
		}
		byte_pattern::temp_instance().find_pattern("8A 04 30 8B 4D");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), k_1);
			k_2 = byte_pattern::temp_instance().get_first().address(9);
		}
		byte_pattern::temp_instance().find_pattern("8B 45 18 03 45 DC 89 55");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), w_1);
			w_2 = byte_pattern::temp_instance().get_first().address(6);
		}
		byte_pattern::temp_instance().find_pattern("3B 5D E8 0F 8F");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), ee_1_1);
			ee_2 = byte_pattern::temp_instance().get_first().address(9);
		}
		byte_pattern::temp_instance().find_pattern("53 FF 75 E8 8D 45 90 C7");
		if (byte_pattern::temp_instance().has_size(1)) {
			ee_3 = byte_pattern::temp_instance().get_first().address();
		}
		byte_pattern::temp_instance().find_pattern("8B 5D 0C 8B CB 6A FF 6A 00 50 C6 45 FC 02 E8");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x13), x_1);
			x_2 = byte_pattern::temp_instance().get_first().address(0x1B);
		}
		byte_pattern::temp_instance().find_pattern("56 8B F1 8B 46 14 83 F8 10 72 0E");
		if (byte_pattern::temp_instance().has_size(2)) {
			injector::MakeJMP(X_f1, byte_pattern::temp_instance().get_first().address(0));
		}
		byte_pattern::temp_instance().find_pattern("8A 55 20 89 4D E4 89 75 E8");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x9), x_5);
		}
		byte_pattern::temp_instance().find_pattern("3B 45 14 0F 8F 70 01 00 00");
		if (byte_pattern::temp_instance().has_size(1)) {
			loc_194690F = byte_pattern::temp_instance().get_first().address();
		}
		/* sub_19465B0　？ */

		/* start sub_19BEAF0  */
		byte_pattern::temp_instance().find_pattern("83 FB 01 72 34 56 33 F6");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0x15), u_1);
			u_4 = byte_pattern::temp_instance().get_first().address(0x1A);
		}
		byte_pattern::temp_instance().find_pattern("80 3C 37 00 75 D9 5E 5F");
		if (byte_pattern::temp_instance().has_size(1)) {
			u_2 = byte_pattern::temp_instance().get_first().address();
		}
		/* end sub_19BEB40  */

		/* start sub_19BEB40 */
		byte_pattern::temp_instance().find_pattern("33 F6 80 3F 00 74 28 83 FE 01");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(0xC), v_2);
			v_4 = byte_pattern::temp_instance().get_first().address(0x11);
		}
		byte_pattern::temp_instance().find_pattern("80 3C 37 00 75 D8 5F 5E");
		if (byte_pattern::temp_instance().has_size(1)) {
			v_1 = byte_pattern::temp_instance().get_first().address();
		}
		/* end sub_19BEB40 */

		/* sub_16FEEFB ヒープクリアフラグの修正 */
		byte_pattern::temp_instance().find_pattern("59 85 C0 74 15 56 6A 00");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x7), 0x08, true);
		}
		/* sub_16FEEFB ヒープクリアフラグの修正 */

		/* 日付 */
		byte_pattern::temp_instance().find_pattern("64 20 77 20 6D 77 20 2C");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0), 0x79, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(1), 0x20, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(2), 0x10, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x74, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(4), 0x5E, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(5), 0x20, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(6), 0x6D, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(7), 0x77, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(8), 0x20, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(9), 0x64, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(10), 0x20, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(11), 0x10, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(12), 0xE5, true);
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(13), 0x65, true);
		}
		/* 日付 */
		
		/* sub_15AB8F0 入力 */
		byte_pattern::temp_instance().find_pattern("55 8B EC 83 EC 70 53 56 57 8B F9 8B DA");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(5), 0x78, true);
		}
		byte_pattern::temp_instance().find_pattern("8A 4D 9C 33 F6 80 F9 80");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), xx_start);
			xx_end = byte_pattern::temp_instance().get_first().address(5);
		}
		byte_pattern::temp_instance().find_pattern("FF 75 A0 E8 ? ? ? ? 83 C4 04 25");
		if (byte_pattern::temp_instance().has_size(1)) {
			xx_end2 = byte_pattern::temp_instance().get_first().address();
		}
		// same as sub_16FEEFB
		byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 56 8B 75 08 83 FE E0");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(heap_alloc_f1, byte_pattern::temp_instance().get_first().address());
		}
		byte_pattern::temp_instance().find_pattern("8B FF 55 8B EC 83 7D 08 00 74 2D FF 75");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(heap_free_f1, byte_pattern::temp_instance().get_first().address());
		}
		// PHYSFS_utf8ToUcs2
		byte_pattern::temp_instance().find_pattern("55 8B EC 51 8B 4D 10 53");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(PHYSFS_utf8ToUcs2_f1, byte_pattern::temp_instance().get_first().address());
		}
		// struct init
		byte_pattern::temp_instance().find_pattern("C7 41 08 01 00 00 00 C7 41 0C 00 00 00 00");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(sub_122FEC0_f1, byte_pattern::temp_instance().get_first().address(-0x12));
		}
		/* sub_15AB8F0 入力 */

		/*  Backspace */
		byte_pattern::temp_instance().find_pattern("8B 07 84 DB 5B 8B CF");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), yy_1);
		}
		byte_pattern::temp_instance().find_pattern("0F B7 47 36 8B CF 50 8D 45 DC 50");
		if (byte_pattern::temp_instance().has_size(2)) { // select first !
			loc_172DEE2 = byte_pattern::temp_instance().get_first().address();
		}
		/*  Backspace */

		/* show candidate and composition window */
		// see https://twitter.com/matanki_saito/status/1005093384946479104
		//
		// (SDL_windowskeyboard.c)
		//
		// skip
		//if (*lParam & GCS_RESULTSTR) {
		//    IME_GetCompositionString(videodata, himc, GCS_RESULTSTR);
		//    IME_SendInputEvent(videodata);
		//}
		byte_pattern::temp_instance().find_pattern("B9 00 08 00 00 8B 45");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(
				byte_pattern::temp_instance().get_first().address(0x8),
				byte_pattern::temp_instance().get_first().address(0x37)
			);
		}
		// remove
		// *lParam = 0;
		byte_pattern::temp_instance().find_pattern("8B 45 14 89 08 E9 83 00");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeNOP(
				byte_pattern::temp_instance().get_first().address(),
				5,
				true
			);
		}
		// skip
		//if (!videodata->ime_initialized || !videodata->ime_available || !videodata->ime_enabled)
		//    return SDL_FALSE;
		byte_pattern::temp_instance().find_pattern("39 4E 28 0F 84 19 02");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(
				byte_pattern::temp_instance().get_first().address(0),
				byte_pattern::temp_instance().get_first().address(0x1B)
			);
		}
		// insert 
		//videodata->ime_hwnd_current = hwnd;
		//rect.x = 0;
		//rect.y = 0;
		//SDL_SetTextInputRect(&rect);
		byte_pattern::temp_instance().find_pattern("0F 84 FD 00 00 00 83 E8 01");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), zz_2);
			zz_4 = byte_pattern::temp_instance().get_first().address(0x06);
		}
		byte_pattern::temp_instance().find_pattern("33 DB 43 E9 E5");
		if (byte_pattern::temp_instance().has_size(1)) {
			loc_18C8D09 = byte_pattern::temp_instance().get_first().address();
		}
		byte_pattern::temp_instance().find_pattern("55 8B EC A1 ? ? ? ? 85 C0 74 12 8B");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(SDL_SetTextInputRect_f1, byte_pattern::temp_instance().get_first().address());
		}

		// SDL_keyborad.c
		// skip
		byte_pattern::temp_instance().find_pattern("85 F6 74 30 57 57 6A 0C");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(
				byte_pattern::temp_instance().get_first().address(-0x6),
				byte_pattern::temp_instance().get_first().address(0)
			);
		}

		// SDL_windowevent.c
		// insert goto
		//if (IME_HandleMessage(hwnd, msg, wParam, &lParam, data->videodata)) {
		//	goto A;
		//}
		byte_pattern::temp_instance().find_pattern("83 C4 14 85 C0 74 07 33");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), zz_8);
		}
		byte_pattern::temp_instance().find_pattern("FF 75 14 FF 75 10 FF 75 0C FF 75 08 E9 B0 0D 00");
		if (byte_pattern::temp_instance().has_size(1)) {
			zz_21 = byte_pattern::temp_instance().get_first().address();
		}
		byte_pattern::temp_instance().find_pattern("8B 45 0C B9 01 01 00 00");
		if (byte_pattern::temp_instance().has_size(1)) {
			loc_18AB507 = byte_pattern::temp_instance().get_first().address();
		}
		/* Candidate */

		/* dynastyに-idがついてしまう問題 */
		byte_pattern::temp_instance().find_pattern("8B 55 E8 8B 75 D4 83 F9");
		if (byte_pattern::temp_instance().has_size(1)) {
			injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), issue_suffix_id);
			issue_suffix_id_r = byte_pattern::temp_instance().get_first().address(0x06);
		}
		byte_pattern::temp_instance().find_pattern("8B 75 C0 8D 45 D4 50 8B");
		if (byte_pattern::temp_instance().has_size(2)) {
			loc_8858F2 = byte_pattern::temp_instance().get_first().address();
		}

	}
}
