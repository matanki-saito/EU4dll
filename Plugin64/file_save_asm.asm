EXTERN	fileSaveProc1ReturnAddress		:	QWORD
EXTERN	fileSaveProc2CallAddress		:	QWORD
EXTERN	fileSaveProc2ReturnAddress		:	QWORD
EXTERN	fileSaveProc3ReturnAddress		:	QWORD
EXTERN	fileSaveProc3CallAddress		:	QWORD
EXTERN  fileSaveProc3CallAddress2       :   QWORD
EXTERN	fileSaveProc4CallAddress		:	QWORD
EXTERN	fileSaveProc4MarkerAddress		:	QWORD
EXTERN	fileSaveProc4ReturnAddress		:	QWORD
EXTERN	fileSaveProc5CallAddress		:	QWORD
EXTERN	fileSaveProc5MarkerAddress		:	QWORD
EXTERN	fileSaveProc5ReturnAddress		:	QWORD
EXTERN	fileSaveProc6CallAddress		:	QWORD
EXTERN	fileSaveProc6MarkerAddress		:	QWORD
EXTERN	fileSaveProc6ReturnAddress		:	QWORD
EXTERN	fileSaveProc7CallAddress		:	QWORD
EXTERN	fileSaveProc7ReturnAddress		:	QWORD

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

fileSaveProc2 PROC
	mov		rcx, rax;
	call	fileSaveProc2CallAddress;

	cmp		qword ptr [rax+18h], 10h;
	jb		JMP_A;
	mov		rax, [rax];

JMP_A:

	mov     qword ptr [rbp + 57h - 50h], 0Fh;
	mov     qword ptr [rbp + 57h - 58h], rbx;
	mov     byte ptr [rbp + 57h - 68h], bl;
	cmp     byte ptr [rax], bl;

	push	fileSaveProc2ReturnAddress;
	ret;
fileSaveProc2 ENDP

;-------------------------------------------;

fileSaveProc2V137 PROC
	mov		rcx, rax;
	call	fileSaveProc2CallAddress;

	cmp		qword ptr [rax+18h], 10h;
	jb		JMP_A;
	mov		rax, [rax];

JMP_A:

	mov     qword ptr [rbp+57h-80h], r12
	mov     qword ptr [rbp+57h-70h], r12
	mov     qword ptr [rbp+57h-68h], 0Fh

	push	fileSaveProc2ReturnAddress;
	ret;
fileSaveProc2V137 ENDP

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

;-------------------------------------------;

fileSaveProc3V130 PROC
	mov		rdx, OFFSET fileSaveProc3Message;
	call	qword ptr [rax + 98h];
	mov		fileSaveProc3Tmp,rax;

	lea		rcx, [rbx +580h];
	call	fileSaveProc3CallAddress;
	mov		rdx, rax;

	xor		r8d, r8d;
	mov		rcx, fileSaveProc3Tmp;

	push	fileSaveProc3ReturnAddress;
	ret;
fileSaveProc3V130 ENDP


;-------------------------------------------;

fileSaveProc3V1316 PROC
	lea		rcx, dword ptr [rbx +580h];
	call	fileSaveProc3CallAddress;
	mov		rdx, rax;

	xor		r8d, r8d;
	mov		rcx, r14
	call	fileSaveProc3CallAddress2;

	push	fileSaveProc3ReturnAddress;
	ret;
fileSaveProc3V1316 ENDP

;-------------------------------------------;

fileSaveProc3V137 PROC
	lea     rcx, [rsi+240h]
	call	fileSaveProc3CallAddress;
	mov		rdx, rax;

	xor     r8d, r8d
	mov     rcx, rbp
	call	fileSaveProc3CallAddress2;

	push	fileSaveProc3ReturnAddress;
	ret;
fileSaveProc3V137 ENDP

;-------------------------------------------;

fileSaveProc4 PROC
	lea		rcx, [rsp + 1A8h -138h];
	call	fileSaveProc4CallAddress;
	mov		rcx, rax;

	mov		rdx, fileSaveProc4MarkerAddress;
	lea		r8, [rbp + 0];

	push	fileSaveProc4ReturnAddress;
	ret;
fileSaveProc4 ENDP

;-------------------------------------------;

fileSaveProc5 PROC
	lea		rcx, [r14 + 598h];
	call	fileSaveProc5CallAddress;
	mov		r8, rax;

	mov		rdx, fileSaveProc5MarkerAddress;
	lea		rcx, [rsp + 278h - 228h];

	push	fileSaveProc5ReturnAddress;
	ret;
fileSaveProc5 ENDP

;-------------------------------------------;

fileSaveProc5V130 PROC
	lea		rcx, [r14 + 5C0h];
	call	fileSaveProc5CallAddress;
	mov		r8, rax;

	mov		rdx, fileSaveProc5MarkerAddress;
	lea		rcx, [rsp + 278h - 228h];

	push	fileSaveProc5ReturnAddress;
	ret;
fileSaveProc5V130 ENDP

;-------------------------------------------;

fileSaveProc5V1316 PROC
	lea		rcx, [r14 + 5C0h];
	call	fileSaveProc5CallAddress;
	mov		r8, rax;

	mov		rdx, fileSaveProc5MarkerAddress;
	lea		rcx, [rsp + 288h - 228h];

	push	fileSaveProc5ReturnAddress;
	ret;
fileSaveProc5V1316 ENDP

;-------------------------------------------;

fileSaveProc5V137 PROC
	mov     rcx, rdx
	call	fileSaveProc5CallAddress;
	mov		rdx, rax;
	mov     r8, [rdx+10h]

	cmp     qword ptr [rdx+18h], 10h
	jb		JMP_A
	mov     rdx, [rdx]

JMP_A:
	lea     rcx, [rsp+478h-398h]

	push	fileSaveProc5ReturnAddress;
	ret;
fileSaveProc5V137 ENDP

;-------------------------------------------;

fileSaveProc6 PROC
	lea		rcx, [rbp + 380h];
	call	fileSaveProc6CallAddress;
	mov		r8, rax;

	mov		rdx, fileSaveProc6MarkerAddress;
	lea		rcx, [rsp + 808h - 7D8h];

	push	fileSaveProc6ReturnAddress;
	ret;
fileSaveProc6 ENDP

;-------------------------------------------;

fileSaveProc6V130 PROC
	lea		rcx, [rbp +730h - 3A0h];
	call	fileSaveProc6CallAddress;
	mov		r8, rax;

	mov		rdx, fileSaveProc6MarkerAddress;
	lea		rcx, [rsp + 830h - 800h];

	push	fileSaveProc6ReturnAddress;
	ret;
fileSaveProc6V130 ENDP

;-------------------------------------------;

fileSaveProc6V137 PROC
	lea     rdx, [rbp+2E0h-240h]
	mov		rcx, rdx
	call	fileSaveProc6CallAddress
	mov		rdx, rax
	mov     r8, [rdx+10h]
	cmp     qword ptr [rdx+18h], 10h
	jb		JMP_A
	mov     rdx, [rdx]
JMP_A:
	lea     rcx, [rsp+3E0h-390h]

	push	fileSaveProc6ReturnAddress;
	ret;
fileSaveProc6V137 ENDP

;-------------------------------------------;

fileSaveProc6V137E PROC
	lea     rdx, [rbp+2E0h-240h]
	mov		rcx, rdx
	call	fileSaveProc6CallAddress
	mov		rdx, rax
	mov     r8, [rdx+10h]
	cmp     qword ptr [rdx+18h], 10h
	jb		JMP_A
	mov     rdx, [rdx]
JMP_A:
	lea     rcx, [rsp+3E0h-388h]

	push	fileSaveProc6ReturnAddress;
	ret;
fileSaveProc6V137E ENDP

;-------------------------------------------;

fileSaveProc6V137G PROC
	lea     rdx, [rsp+560h-510h]
	mov     rcx, rdx
	call    fileSaveProc6CallAddress
	mov     rdx, rax
	mov     r8, [rdx+10h]
	cmp     qword ptr [rdx+18h], 10h
	jb      JMP_A
	mov     rdx, [rdx]
JMP_A:
	lea     rcx, [rbp+460h-4E0h]

	push    fileSaveProc6ReturnAddress;
	ret;
fileSaveProc6V137G ENDP

;-------------------------------------------;

fileSaveProc7 PROC

	lea		rcx, [rsp + 58h - 30h];
	call	fileSaveProc7CallAddress;
	mov		rdx, rax;

	lea		rcx, [rbx+0C8h];
	mov		rax, qword ptr [rcx];

	push	fileSaveProc7ReturnAddress;
	ret;
fileSaveProc7 ENDP

;-------------------------------------------;

fileSaveProc7V137 PROC

	lea     rdx, [rsp+48h-28h]
	mov		rcx, rdx
	call	fileSaveProc7CallAddress;
	mov		rdx, rax;
	mov     r8, [rdx+10h]

	lea		rcx, [rdi+0C8h];
	mov     rax, [rcx]

	push	fileSaveProc7ReturnAddress;
	ret;
fileSaveProc7V137 ENDP

END