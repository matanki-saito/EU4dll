; 多分このコードは一番難しい

EXTERN	mapJustifyProc1ReturnAddress1	:	QWORD
EXTERN	mapJustifyProc1ReturnAddress2	:	QWORD
EXTERN	mapJustifyProc2ReturnAddress	:	QWORD

;temporary space for code point
.DATA
	mapJustifyProc1TmpFlag	DD	0

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
mapJustifyProc1 PROC
	movss   xmm9, dword ptr [rcx + 848h];

	cmp		byte ptr [rax + r13], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + r13], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rax + r13], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rax + r13], ESCAPE_SEQ_4;
	jz		JMP_D;
	mov		mapJustifyProc1TmpFlag, 0h;
	movzx	esi, byte ptr [rax + r13];
	mov     rdi, qword ptr [rcx + rsi * 8];
	test	rdi, rdi;
	jz		JMP_I;
	jmp		mapJustifyProc1ReturnAddress1;

JMP_A:
	movzx	esi, word ptr [rax + r13 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	esi, word ptr [rax + r13 + 1];
	sub		esi, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	esi, word ptr [rax + r13 + 1];
	add		esi, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	esi, word ptr [rax + r13 + 1];
	add		esi, SHIFT_4;

JMP_F:
	movzx	esi, si;
	cmp		esi, NO_FONT;
	ja		JMP_G;
	mov		esi, NOT_DEF;

JMP_G:
	mov     rdi, qword ptr [rcx + rsi * 8];
	test	rdi, rdi;
	jz		JMP_H;
	push	mapJustifyProc1ReturnAddress1;
	ret;

JMP_H:
	mov		mapJustifyProc1TmpFlag, 1h;
	add		rdx, 2;
	mov     qword ptr [rbp + 1D0h - 138h], rdx;
	sub		rdx, 2;

JMP_I:
	push	mapJustifyProc1ReturnAddress2;
	ret;
mapJustifyProc1 ENDP

;-------------------------------------------;

mapJustifyProc2 PROC
	cmp		mapJustifyProc1TmpFlag, 1h;
	jnz		JMP_A;

	; 3byte = 1文字かどうか
	cmp		r10, 3; 
	ja		JMP_A;
	add		edx, 2;
	mov		qword ptr [rbp + 1D0h - 138h], rdx;
	mov		rax, r10;
	add		eax, 2;
	mov		r10, rax; 
	mov		mapJustifyProc1TmpFlag, 0; 以降の処理はスキップ

JMP_A:
	movd    xmm6, edx;

	; エスケープ文字
	cmp		mapJustifyProc1TmpFlag, 1h;
	jz		JMP_B;

	lea     eax, [r10 - 1]; ; -1している
	jmp		JMP_C;

JMP_B:
	add		edx, 2;
	mov		qword ptr [rbp + 1D0h - 138h], rdx;
	lea     eax, [r10 - 2]; ; -2している

JMP_C:
	movd    xmm0, eax;
	cvtdq2ps xmm0, xmm0;

	push	mapJustifyProc2ReturnAddress;
	ret;
mapJustifyProc2 ENDP

END