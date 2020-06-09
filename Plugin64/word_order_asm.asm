EXTERN wordOrderProc1CallAddress1: QWORD
EXTERN wordOrderProc1CallAddress2: QWORD
EXTERN wordOrderProc2ReturnAddress: QWORD
EXTERN wordOrderProc3ReturnAddress: QWORD
EXTERN wordOrderProc4ReturnAddress: QWORD
EXTERN wordOrderProc5ReturnAddress: QWORD
EXTERN wordOrderProc6ReturnAddress: QWORD
EXTERN wordOrderProc7ReturnAddress: QWORD
EXTERN wordOrderProc7CallAddress1: QWORD
EXTERN wordOrderProc7CallAddress2: QWORD
EXTERN wordOrderProc8ReturnAddress: QWORD

EXTERN year: QWORD
EXTERN month: QWORD
EXTERN day: QWORD

EXTERN generateCString: QWORD
EXTERN concatCString: QWORD
EXTERN concat2CString: QWORD

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

wordOrderProc3V130 PROC
	nop;

	;ãtã^ñ‚ïÑ(0xBF)Ç™ç≈èâÇ…óàÇƒÇ¢ÇÍÇŒîΩì]Ç≥ÇπÇÈ
	cmp		byte ptr[rax+1], 0BFh; // [0]ÇÕ0x20(white space)
	jnz		JMP_A;

	mov		qword ptr [rsp+20h], 0FFFFFFFFFFFFFFFFh;
	xor		r9,	r9;	 // start
	mov		r8, rax; // text
	xor		rdx,rdx;  // pos1
	mov		rcx, r15; // this
	call	wordOrderProc1CallAddress1;
	jmp		JMP_B;

JMP_A:
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	mov		rdx, rax;
	mov		rcx, r15;
	call    wordOrderProc1CallAddress2;

JMP_B:
	push	wordOrderProc3ReturnAddress;
	ret;
wordOrderProc3V130 ENDP

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

wordOrderProc4V130 PROC
	nop;

	;ãtã^ñ‚ïÑ(0xBF)Ç™ç≈èâÇ…óàÇƒÇ¢ÇÍÇŒîΩì]Ç≥ÇπÇÈ
	cmp		byte ptr[rax+1], 0BFh; // [0]ÇÕ0x20(white space)
	jnz		JMP_A;

	mov		qword ptr [rsp+20h], 0FFFFFFFFFFFFFFFFh;
	xor		r9,	r9;	 // start
	mov		r8, rax; // text
	xor		rdx,rdx;  // pos1
	mov		rcx, r15; // this
	call	wordOrderProc1CallAddress1;
	jmp		JMP_B;

JMP_A:
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	mov		rdx, rax;
	mov		rcx, r15;
	call    wordOrderProc1CallAddress2;

JMP_B:
	push	wordOrderProc4ReturnAddress;
	ret;
wordOrderProc4V130 ENDP

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

;-----------------------------------;

wordOrderProc6 PROC
	nop;

	; 1450
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	lea		rdx, [rsp+0D0h-0A8h];
	mov		rcx, rsi;
	call	wordOrderProc1CallAddress2;

	; 1450îN
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	mov		rdx, year;
	mov		rcx, rsi;
	call	wordOrderProc1CallAddress2;
	
	; 1450îN1åé
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	lea		rdx, [rbp+57h - 78h];
	mov		rcx, rsi;
	call	wordOrderProc1CallAddress2;


	push	wordOrderProc6ReturnAddress;
	ret;
wordOrderProc6 ENDP

;-----------------------------------;

wordOrderProc7 PROC
	; 1450
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	lea		rdx, [rsp+168h-100h];
	mov		rcx, rdi;
	call	wordOrderProc1CallAddress2;

	; 1450îN
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	mov		rdx, year;
	mov		rcx, rdi;
	call	wordOrderProc1CallAddress2;

	; 1450îN1åé
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	lea		rdx, [rbp+8];
	mov		rcx, rdi;
	call	wordOrderProc1CallAddress2;

	; 1450îN1åé1
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	lea		rdx, [rsp+168h - 140h];
	mov		rcx, rdi;
	call	wordOrderProc1CallAddress2;

	; 1450îN1åé1ì˙
	or		r9, 0FFFFFFFFFFFFFFFFh;
	xor		r8d, r8d;
	mov		rdx, day;
	mov		rcx, rdi;
	call	wordOrderProc1CallAddress2;
	nop;

	; à»â∫äJï˙Ç∑ÇÈÇΩÇﬂÇæÇØÇ…ïKóv
	lea     r8, [rsp + 168h - 120h];
	lea     rdx, [rsp + 168h - 140h];
	lea     rcx, [rbp - 18h];
	call    wordOrderProc7CallAddress1;
	nop;

	lea		r8, [rbp + 8];
	mov		rdx, rax;
	lea		rcx, [rbp - 38h];
	call	wordOrderProc7CallAddress2;
	nop;

	mov		r8, year;
	mov		rdx, rax;
	lea		rcx, [rbp-58h];
	call	wordOrderProc7CallAddress2;
	nop;

	lea		r8, [rsp + 168h - 100h];
	mov		rdx, rax;
	lea		rcx, [rbp - 78h];
	call	wordOrderProc7CallAddress1;

	push	wordOrderProc7ReturnAddress;
	ret;
wordOrderProc7 ENDP

;-----------------------------------;

wordOrderProc8 PROC

	; îN
	mov		r8d, 1;
	mov		rdx, year;
	lea		rcx, [rbp-59h];
	call    generateCString;
	nop;

	; 1450îN
	lea		r8, [rbp-59h];
	lea		rdx, [rbp-31h];
	lea		rcx, [rbp-11h];
	call	concatCString;
	nop;

	; 1450îN1åé
	lea		r8, [rbp+0Fh];
	mov		rdx, rax;
	mov		rcx, rdi;
	call	concat2CString;

	push	wordOrderProc8ReturnAddress;
	ret;
wordOrderProc8 ENDP
END