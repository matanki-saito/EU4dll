EXTERN	mapAdjustmentProc1ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc1ReturnAddressA	:	QWORD
EXTERN	mapAdjustmentProc1ReturnAddressB	:	QWORD
EXTERN	mapAdjustmentProc1CallAddress		:	QWORD
EXTERN	mapAdjustmentProc1CallAddressA		:	QWORD
EXTERN	mapAdjustmentProc1CallAddressB		:	QWORD
EXTERN	mapAdjustmentProc2ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc3ReturnAddress1	:	QWORD
EXTERN	mapAdjustmentProc3ReturnAddress2	:	QWORD
EXTERN	mapAdjustmentProc4ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc5ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc5SeparatorAddress	:	QWORD


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
MAP_LIMIT		=	2Dh-1

.DATA
DefaultSeparator	DB	" ", 0

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

	cmp		r14d, 45;
	jbe		JMP_C;
	nop;
JMP_C:
	push	mapAdjustmentProc1ReturnAddress;
	ret;
mapAdjustmentProc1 ENDP

;-------------------------------------------;

mapAdjustmentProc1V137A PROC
	movsx   ecx, byte ptr [rax+rbp]
	cmp		ecx, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_4;
	jz		JMP_A;

	lea     rbx, [rax+rbp]
	call	mapAdjustmentProc1CallAddressA;
	inc     edi
	mov     [rbx], al

	jmp		JMP_B;

JMP_A:
	add		edi, 3;
JMP_B:
	mov     eax, edi

	push	mapAdjustmentProc1ReturnAddressA;
	ret;
mapAdjustmentProc1V137A ENDP

;-------------------------------------------;

mapAdjustmentProc1V137B PROC
	movsx   ecx, byte ptr [rax+rbp]
	cmp		ecx, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		ecx, ESCAPE_SEQ_4;
	jz		JMP_A;

	lea     rbx, [rax+rbp]
	call	mapAdjustmentProc1CallAddressB;
	inc     edi
	mov     [rbx], al

	jmp		JMP_B;

JMP_A:
	add		edi, 3;
JMP_B:
	mov     eax, edi

	push	mapAdjustmentProc1ReturnAddressB;
	ret;
mapAdjustmentProc1V137B ENDP

;-------------------------------------------;


mapAdjustmentProc2 PROC
	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_A;

	lea     rax, qword ptr [rbp + 1F0h - 1F0h];
	or      r8, 0FFFFFFFFFFFFFFFFh;
	nop;

JMP_B:
	inc     r8;
	cmp     byte ptr [rax+r8], 0;
	jnz		JMP_B;
	jmp		JMP_C;

JMP_A:
	mov		r8, 3;

	lea     rax, qword ptr [rbp + 1F0h - 160h];
	cmp     qword ptr [rbp + 1F0h - 148h], 10h;
	cmovnb  rax, qword ptr [rbp + 1F0h - 160h];
	mov		dx, word ptr [rbx + rax + 1];

	mov		word ptr[rbp + 1F0h - 1F0h + 1], dx;
	add		rbx, 2;

JMP_C:
	push	mapAdjustmentProc2ReturnAddress;
	ret;
mapAdjustmentProc2 ENDP

;-------------------------------------------;

mapAdjustmentProc2V130 PROC
	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_A;

	lea     rax, qword ptr [rbp + 200h - 200h];
	or      r8, 0FFFFFFFFFFFFFFFFh;
	nop;

JMP_B:
	inc     r8;
	cmp     byte ptr [rax+r8], 0;
	jnz		JMP_B;
	jmp		JMP_C;

JMP_A:
	mov		r8, 3;

	lea     rax, qword ptr [rbp + 200h - 160h];
	cmp     qword ptr [rbp + 200h - 148h], 10h;
	cmovnb  rax, qword ptr [rbp + 200h - 160h];
	mov		dx, word ptr [rbx + rax + 1];

	mov		word ptr[rbp + 200h - 200h + 1], dx;
	add		rbx, 2;

JMP_C:
	push	mapAdjustmentProc2ReturnAddress;
	ret;
mapAdjustmentProc2V130 ENDP

;-------------------------------------------;

mapAdjustmentProc2V137 PROC
	lea     rax, qword ptr [rbp+230h-1A0h] ; 1A0 = Block
	cmp     r13, 10h
	cmovnb  rax, rsi
	movzx   eax, byte ptr [rax+rbx]
	mov     byte ptr [rbp+230h-230h], al

	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_A;

	lea     rax, qword ptr [rbp + 230h - 230h];
	mov     r8, 0FFFFFFFFFFFFFFFFh;

JMP_B:
	inc     r8;
	cmp     byte ptr [rax+r8], 0;
	jnz		JMP_B;
	jmp		JMP_C;

JMP_A:
	mov		r8, 3;

	lea     rax, qword ptr [rbp+230h-1A0h] ; 1A0 = Block
	cmp     r13, 10h
	cmovnb  rax, rsi
	mov		dx, word ptr [rax+rbx+1]
	mov     word ptr [rbp+230h-230h+1], dx

	add		rbx, 2;

JMP_C:
	push	mapAdjustmentProc2ReturnAddress;
	ret;
mapAdjustmentProc2V137 ENDP

;-------------------------------------------;

mapAdjustmentProc3 PROC
	mov		dword ptr[rbp + 1F0h - 1F0h], 0000h;
	cmp     rbx, rdi;
	jz		JMP_A;
	or      r9, 0FFFFFFFFFFFFFFFFh;
	xor     r8d, r8d;
	lea     rdx, qword ptr [rbp + 1F0h - 130h];
	lea     rcx, qword ptr [rbp + 1F0h - 1C0h];

	push	mapAdjustmentProc3ReturnAddress1;
	ret;

JMP_A:
	push	mapAdjustmentProc3ReturnAddress2;
	ret;
mapAdjustmentProc3 ENDP

;-------------------------------------------;

mapAdjustmentProc3V130 PROC
	mov		dword ptr[rbp + 200h - 200h], 0000h;
	cmp     rbx, rdi;
	jz		JMP_A;
	or      r9, 0FFFFFFFFFFFFFFFFh;
	xor     r8d, r8d;
	lea     rdx, qword ptr [rbp + 200h - 130h];
	lea     rcx, qword ptr [rbp + 200h - 1D0h];

	push	mapAdjustmentProc3ReturnAddress1;
	ret;

JMP_A:
	push	mapAdjustmentProc3ReturnAddress2;
	ret;
mapAdjustmentProc3V130 ENDP

;-------------------------------------------;

mapAdjustmentProc3V137 PROC
	mov		dword ptr[rbp + 230h - 230h], 0000h;
	cmp     rbx, r12
	jz		JMP_A;
	lea     rdx, [rbp+230h-1C0h]
	cmp     rdi, 10h
	cmovnb  rdx, [rbp+230h-1C0h] ;
	mov     r8, [rbp+230h-1B0h]
	lea     rcx, [rbp+230h-200h]

	push	mapAdjustmentProc3ReturnAddress1;
	ret;

JMP_A:
	push	mapAdjustmentProc3ReturnAddress2;
	ret;
mapAdjustmentProc3V137 ENDP

;-------------------------------------------;

mapAdjustmentProc4 PROC
	lea		rax, [rbp + 1F0h - 160h];
	cmp		r8, 10h;
	cmovnb	rax, r9;

	cmp		byte ptr[rcx + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rcx + rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rcx + rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rcx + rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr[rcx + rax];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rcx + rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rcx + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rcx + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rcx + rax + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		rcx, 2;
	cmp		rcx, MAP_LIMIT;
	ja		JMP_G;

	cmp		eax, NO_FONT;
	ja		JMP_E;
JMP_G:
	mov		eax, NOT_DEF;
	movzx	eax, ax;

JMP_E:

	push	mapAdjustmentProc4ReturnAddress;
	ret;
mapAdjustmentProc4 ENDP

;-------------------------------------------;

mapAdjustmentProc4V130 PROC
	lea		rax, [rbp + 200h - 160h];
	cmp		r8, 10h;
	cmovnb	rax, r9;

	cmp		byte ptr[rcx + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rcx + rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rcx + rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rcx + rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr[rcx + rax];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rcx + rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rcx + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rcx + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rcx + rax + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		rcx, 2;
	cmp		rcx, MAP_LIMIT;
	ja		JMP_G;

	cmp		eax, NO_FONT;
	ja		JMP_E;
JMP_G:
	mov		eax, NOT_DEF;
	movzx	eax, ax;

JMP_E:

	push	mapAdjustmentProc4ReturnAddress;
	ret;
mapAdjustmentProc4V130 ENDP

;-------------------------------------------;

mapAdjustmentProc4V137 PROC
	lea     rax, [rbp+230h-1A0h]
	cmp     r13, 10h
	cmovnb  rax, rsi

	cmp		byte ptr[rax+rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax+rcx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax+rcx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax+rcx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx   eax, byte ptr [rax+rcx]
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax+rcx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax+rcx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax+rcx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax+rcx + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		rcx, 2;
	cmp		rcx, MAP_LIMIT;
	ja		JMP_G;

	cmp		eax, NO_FONT;
	ja		JMP_E;
JMP_G:
	mov		eax, NOT_DEF;
	movzx	eax, ax;

JMP_E:

	push	mapAdjustmentProc4ReturnAddress;
	ret;
mapAdjustmentProc4V137 ENDP

;-------------------------------------------;

mapAdjustmentProc5 PROC
	; ex) {アラゴン}領シチリア ; {} = [rbp+190h-118h
	lea     rdx, [rbp+190h-118h];
	movsxd	rcx,dword ptr [rdx+10h];
	cmp		rcx , 10h;
	jle		JMP_A;
	mov		rdx, qword ptr [rdx];

JMP_A:
	; {}の最後の文字がマルチバイトであるかを確認する
	; 後ろから3バイト目を取得する。2バイト以下ならばスキップ
	cmp		rcx,3;
	jb		JMP_B;

	mov		dl, byte ptr[rdx + rcx - 3];

	cmp		dl, ESCAPE_SEQ_1;
	jz		JMP_D;
	cmp		dl, ESCAPE_SEQ_2;
	jz		JMP_D;
	cmp		dl, ESCAPE_SEQ_3;
	jz		JMP_D;
	cmp		dl, ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_B;

JMP_D:
	mov		r8,	mapAdjustmentProc5SeparatorAddress;
	jmp		JMP_C;

JMP_B: ;英語
	lea		r8,	DefaultSeparator;

JMP_C:
	lea     rcx, [rbp+190h-50h]; 元に戻す
	lea     rdx, [rbp+190h-118h]; 元に戻す
	push	mapAdjustmentProc5ReturnAddress;
	ret;
mapAdjustmentProc5 ENDP
END