EXTERN	inputProc1ReturnAddress	:	QWORD
EXTERN	inputProc1CallAddress	:	QWORD

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
inputProc1 PROC
	mov		eax, dword ptr [rbp + 120h - 198h + 0Ch];
	cmp		ah, 0;
	jnz		JMP_A;
	xor		bl, bl;

JMP_C:
	cmp		al, 80h;
	jnb		JMP_X;
	mov		ebx, eax;
	jmp     JMP_Y;

JMP_X:
	cmp		al, 0E0h;
	jnb		JMP_Y;
	movzx	ebx, byte ptr [rbp + 120h - 198h + 0Dh];
	and		bl, 3Fh;
	shl		al, 6;
	or		bl, al;

JMP_Y:
	push	inputProc1ReturnAddress;
	ret;

JMP_A:
	lea		rcx,[rbp + 120h - 198h + 0Ch];
	call	inputProc1CallAddress;
	mov		eax, dword ptr [rbp + 120h - 198h + 0Ch];
	xor		bl, bl;
	jmp		JMP_C;

inputProc1 ENDP
END