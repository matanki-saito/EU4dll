EXTERN	mapAdjustmentProc1ReturnAddress	:	QWORD
EXTERN	mapAdjustmentProc1CallAddress	:	QWORD

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
mapAdjustmentProc1 PROC
	movsx	ecx, byte ptr[rdi + rbx];
	cmp		ecx, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_4;
	jz		JMP_A;

	call	mapAdjustmentProc1CallAddress;
	mov     byte ptr [rdi + rbx], al;
	inc     r14d;

	jmp		JMP_B;

JMP_A:
	add		r14d, 3;

JMP_B:
	mov     ebx, r14d;

	push	mapAdjustmentProc1ReturnAddress;
	ret;
mapAdjustmentProc1 ENDP
END