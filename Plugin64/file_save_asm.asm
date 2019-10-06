EXTERN	fileSaveProc1ReturnAddress		:	QWORD
EXTERN	fileSaveProc3ReturnAddress		:	QWORD
EXTERN	fileSaveProc3CallAddress		:	QWORD

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


; temporary space
.DATA
	fileSaveProc3Tmp	DQ	0
	fileSaveProc3Message	DB	'save_game_title',0

.CODE
fileSaveProc1 PROC
	mov		eax, dword ptr [rcx + 10h];
	test	eax, eax;

	push	fileSaveProc1ReturnAddress;
	ret;
fileSaveProc1 ENDP

;-------------------------------------------;

fileSaveProc3 PROC
	mov		rdx, OFFSET fileSaveProc3Message;
	call	qword ptr [rax + 98h];
	mov		fileSaveProc3Tmp,rax;

	lea		rcx, [rbx +558h];
	call	fileSaveProc3CallAddress;
	mov		rdx, rax;

	xor		r8d, r8d;
	mov		rcx, fileSaveProc3Tmp;

	push	fileSaveProc3ReturnAddress;
	ret;
fileSaveProc3 ENDP
END