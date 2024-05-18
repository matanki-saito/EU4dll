EXTERN	cBitmapFontProc1ReturnAddress	:	QWORD
EXTERN	cBitmapFontProc2ReturnAddress	:	QWORD

ESCAPE_SEQ_1	=	10h
ESCAPE_SEQ_2	=	11h
ESCAPE_SEQ_3	=	12h
ESCAPE_SEQ_4	=	13h
LOW_SHIFT		=	0Eh
HIGH_SHIFT		=	9h
SHIFT_2			=	LOW_SHIFT
SHIFT_3			=	900h
SHIFT_4			=	8F2h
NO_FONT			=	98Fh
NOT_DEF			=	2026h


.CODE
cBitmapFontProc1 PROC
	;movzx   eax, byte ptr [rdi+rax]
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rdi + rax];
	jmp		JMP_H;

JMP_A:
	movzx	eax, word ptr[rdi + rax + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr[rdi + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr[rdi + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr[rdi + rax + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		edi, 2;
	xorps   xmm6, xmm6

JMP_H:
	mov     rcx, qword ptr [r15 + rax * 8 + 120h];
	test    rcx, rcx

	push	cBitmapFontProc1ReturnAddress;
	ret;
cBitmapFontProc1 ENDP

;----------------------------------------------;

cBitmapFontProc1V137 PROC
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rdi + rax];
	jmp		JMP_H;

JMP_A:
	movzx	eax, word ptr[rdi + rax + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr[rdi + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr[rdi + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr[rdi + rax + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		edi, 2;
	xorps   xmm6, xmm6

JMP_H:
	mov     rcx, qword ptr [r14 + rax * 8 + 120h];
	test    rcx, rcx

	push	cBitmapFontProc1ReturnAddress;
	ret;
cBitmapFontProc1V137 ENDP

;----------------------------------------------;

cBitmapFontProc2 PROC
	mov     r13d, edi;
	movss   xmm6, dword ptr [r12+848h];

	cmp		byte ptr[rax + r13], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + r13], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + r13], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + r13], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rax + r13];
	jmp		JMP_H;

JMP_A:
	movzx	eax, word ptr[rax + r13 + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr[rax + r13 + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr[rax + r13 + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr[rax + r13 + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		edi, 2;

JMP_H:
	mov     r12, [r12+rax*8];
	test    r12, r12

	push	cBitmapFontProc2ReturnAddress;
	ret;
cBitmapFontProc2 ENDP

;----------------------------------------------;

cBitmapFontProc2V137 PROC
	movss   xmm6, dword ptr [r14+848h]

	cmp		byte ptr[rdx+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rdx+rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rdx+rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rdx+rax], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rdx+rax];
	jmp		JMP_H;

JMP_A:
	movzx	eax, word ptr[rdx+rax + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr[rdx+rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr[rdx+rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr[rdx+rax + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		edi, 2;

JMP_H:
	mov     r15, qword ptr [r14+rax*8];
	test    r15, r15

	push	cBitmapFontProc2ReturnAddress;
	ret;
cBitmapFontProc2V137 ENDP

END
