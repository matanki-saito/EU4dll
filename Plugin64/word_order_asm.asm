EXTERN wordOrderProc1CallAddress: QWORD
EXTERN wordOrderProc2ReturnAddress: QWORD

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

;temporary space for code point
.DATA
	mainTextProc2TmpCharacter	DD	0

.CODE
wordOrderProc2 PROC
	nop;

	mov		qword ptr [rsp+58h-38h], 0FFFFFFFFFFFFFFFFh;
	mov		r9,	1;	 // start
	mov		r8, rax; // text
	xor		rdx,rdx;  // pos1
	mov		rcx, rbx; // this
	call	wordOrderProc1CallAddress;

	push	wordOrderProc2ReturnAddress;
	ret;
wordOrderProc2 ENDP
END