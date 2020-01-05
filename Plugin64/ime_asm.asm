EXTERN	imeProc1ReturnAddress1	:	QWORD
EXTERN	imeProc1ReturnAddress2	:	QWORD
EXTERN	imeProc1CallAddress	:	QWORD

EXTERN	imeProc2ReturnAddress1	:	QWORD
EXTERN	imeProc2ReturnAddress2	:	QWORD
EXTERN	imeProc2CallAddress	:	QWORD
EXTERN	rectAddress	:	QWORD

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

imeProc1 PROC
	mov		edx, r13d;
	mov		rcx, r12;
	call	imeProc1CallAddress;
	test	eax,eax;
	jnz		JMP_A;

	push	imeProc1ReturnAddress1;
	ret;

JMP_A:
	push	imeProc1ReturnAddress2;
	ret;

imeProc1 ENDP

;-------------------------------------------;

imeProc2 PROC
	sub		edx, 0BCh;
	jz		JMP_A;

	push	imeProc2ReturnAddress2;
	ret;

JMP_A:
	mov		rcx, rectAddress;
	call	imeProc2CallAddress;

	push	imeProc2ReturnAddress1;
	ret;
imeProc2 ENDP

END