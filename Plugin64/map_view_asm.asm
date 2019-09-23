EXTERN mapViewProc1ReturnAddress: QWORD

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
mapViewProc1 PROC
	cmp		byte ptr [rbx + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rbx + rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rbx + rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rbx + rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr [rbx + rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr [rbx + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [rbx + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [rbx + rax + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		ebx, 2;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;
	jmp		JMP_G;

JMP_E:
	movzx	eax, byte ptr [rbx + rax];

JMP_G:
	mov     r11, qword ptr [r15 + rax * 8 + 100h];
	mov     qword ptr [rbp + 80h], r11;

	push	mapViewProc1ReturnAddress;
	ret;
mapViewProc1 ENDP

END