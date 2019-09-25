EXTERN	mapJustifyProc1ReturnAddress1	:	QWORD
EXTERN	mapJustifyProc1ReturnAddress2	:	QWORD

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
	movzx	esi, byte ptr [rax + r13];
	mov     rdi, qword ptr [rcx + rsi * 8];
	test	rdi, rdi;
	jz		JMP_H;
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
	add		r13, 2;

JMP_H:
	push	mapJustifyProc1ReturnAddress2;
	ret;
mapJustifyProc1 ENDP

;-------------------------------------------;

mapJustifyProc2 PROC

mapJustifyProc2 ENDP

END