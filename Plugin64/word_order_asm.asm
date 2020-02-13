EXTERN wordOrderProc1CallAddress1: QWORD
EXTERN wordOrderProc1CallAddress2: QWORD
EXTERN wordOrderProc2ReturnAddress: QWORD
EXTERN wordOrderProc3ReturnAddress: QWORD
EXTERN wordOrderProc4ReturnAddress: QWORD
EXTERN wordOrderProc5ReturnAddress: QWORD

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
	call	wordOrderProc1CallAddress1;

	push	wordOrderProc2ReturnAddress;
	ret;
wordOrderProc2 ENDP

;-----------------------------------;

wordOrderProc3 PROC
	nop;

	;ãtã^ñ‚ïÑ(0xBF)Ç™ç≈èâÇ…óàÇƒÇ¢ÇÍÇŒîΩì]Ç≥ÇπÇÈ
	cmp		byte ptr[rax+1], 0BFh; // [0]ÇÕ0x20(white space)
	jnz		JMP_A;

	mov		qword ptr [rsp+20h], 0FFFFFFFFFFFFFFFFh;
	xor		r9,	r9;	 // start
	mov		r8, rax; // text
	xor		rdx,rdx;  // pos1
	mov		rcx, r12; // this
	call	wordOrderProc1CallAddress1;
	jmp		JMP_B;

JMP_A:
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	mov		rdx, rax;
	mov		rcx, r12;
	call    wordOrderProc1CallAddress2;

JMP_B:
	push	wordOrderProc3ReturnAddress;
	ret;
wordOrderProc3 ENDP

;-----------------------------------;

wordOrderProc4 PROC
	nop;

	;ãtã^ñ‚ïÑ(0xBF)Ç™ç≈èâÇ…óàÇƒÇ¢ÇÍÇŒîΩì]Ç≥ÇπÇÈ
	cmp		byte ptr[rax+1], 0BFh; // [0]ÇÕ0x20(white space)
	jnz		JMP_A;

	mov		qword ptr [rsp+20h], 0FFFFFFFFFFFFFFFFh;
	xor		r9,	r9;	 // start
	mov		r8, rax; // text
	xor		rdx,rdx;  // pos1
	mov		rcx, r12; // this
	call	wordOrderProc1CallAddress1;
	jmp		JMP_B;

JMP_A:
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	mov		rdx, rax;
	mov		rcx, r12;
	call    wordOrderProc1CallAddress2;

JMP_B:
	push	wordOrderProc4ReturnAddress;
	ret;
wordOrderProc4 ENDP

;-----------------------------------;

wordOrderProc5 PROC
	nop;

	;ãtã^ñ‚ïÑ(0xBF)Ç™ç≈èâÇ…óàÇƒÇ¢ÇÍÇŒîΩì]Ç≥ÇπÇÈ
	cmp		byte ptr[rax+1], 0BFh; // [0]ÇÕ0x20(white space)
	jnz		JMP_A;

	mov		qword ptr [rsp+20h], 0FFFFFFFFFFFFFFFFh;
	mov		r9, 1;	 // start
	mov		r8, rax; // text
	xor		rdx,rdx;  // pos1
	mov		rcx, rdi; // this
	call	wordOrderProc1CallAddress1;
	jmp		JMP_B;

JMP_A:
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor     r8d, r8d;
	mov     rdx, rax;
	mov     rcx, rdi;
	call    wordOrderProc1CallAddress2;

JMP_B:
	push	wordOrderProc5ReturnAddress;
	ret;
wordOrderProc5 ENDP
END