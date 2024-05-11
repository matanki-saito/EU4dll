EXTERN mainTextProc1ReturnAddress: QWORD
EXTERN mainTextProc2ReturnAddress: QWORD
EXTERN mainTextProc2BufferAddress: QWORD
EXTERN mainTextProc3ReturnAddress1: QWORD
EXTERN mainTextProc3ReturnAddress2: QWORD
EXTERN mainTextProc4ReturnAddress: QWORD

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
mainTextProc1 PROC
	movsxd	rax, edi;

	cmp		byte ptr[rax + rbx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + rbx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + rbx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + rbx], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx	eax, byte ptr [rax+rbx];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax + rbx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax + rbx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax + rbx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax + rbx + 1];
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	add		edi, 2;
	cmp		eax, NO_FONT;

	ja		JMP_E;
	mov		eax, NOT_DEF;
JMP_E:
	movss	xmm3, dword ptr [r15+848h];
	mov		rbx, qword ptr [r15+rax*8];
	mov		qword ptr [rbp+100h], rbx;

	push	mainTextProc1ReturnAddress;
	ret;
mainTextProc1 ENDP

;-------------------------------------------;

mainTextProc1V137 PROC
	cmp		byte ptr [rcx+r9], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rcx+r9], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rcx+r9], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rcx+r9], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx   r8d, byte ptr [rcx+r9]
	jmp		JMP_E;

JMP_A:
	movzx	r8d, word ptr[rcx+r9 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	r8d, word ptr[rcx+r9 + 1];
	sub		r8d, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	r8d, word ptr[rcx+r9 + 1];
	add		r8d, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	r8d, word ptr[rcx+r9 + 1];
	add		r8d, SHIFT_4;

JMP_F:
	movzx	r8d, r8w;
	add		r15d, 2;
	cmp		r8d, NO_FONT;

	ja		JMP_E;
	mov		r8d, NOT_DEF;
JMP_E:
	movss   xmm3, dword ptr [r14+968h]
	mov     rdx, [r14+r8*8+120h]

	push	mainTextProc1ReturnAddress;
	ret;
mainTextProc1V137 ENDP

;-------------------------------------------;

mainTextProc2 PROC
	movsxd  rdx, edi;
	movsxd  rcx, r14d;
	mov     r10, [rsp+858h-7E0h];

	movzx	eax, byte ptr [rdx+r10];
	mov		r9, mainTextProc2BufferAddress;
	mov     byte ptr [rcx+r9], al;

	inc     r14d;
	inc		rcx;

	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rdx+r10+1];
	mov		word ptr [rcx+r9], ax;
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rdx+r10+1];
	mov		word ptr [rcx+r9], ax;
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [rdx+r10+1];
	mov		word ptr [rcx+r9], ax;
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [rdx+r10+1];
	mov		word ptr [rcx+r9], ax;
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	add		r14d, 2;
	add		rcx,2;
	cmp		eax, NO_FONT;

	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		rdx, 2;
	add		edi, 2;
JMP_E:

	mov		mainTextProc2TmpCharacter, eax;
	
	push	mainTextProc2ReturnAddress;
	ret;
mainTextProc2 ENDP

;-------------------------------------------;

mainTextProc2V131 PROC
	movsxd  rdx, edi;
	movsxd  rcx, r14d;
	mov     r10, [rbp+750h-7D0h];

	movzx	eax, byte ptr [rdx+r10];
	mov		r9, mainTextProc2BufferAddress;
	mov     byte ptr [rcx+r9], al;

	inc     r14d;
	inc		rcx;

	cmp		al, ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		al, ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		al, ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		al, ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rdx+r10+1];
	mov		word ptr [rcx+r9], ax;
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rdx+r10+1];
	mov		word ptr [rcx+r9], ax;
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [rdx+r10+1];
	mov		word ptr [rcx+r9], ax;
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [rdx+r10+1];
	mov		word ptr [rcx+r9], ax;
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	add		r14d, 2;
	add		rcx,2;
	cmp		eax, NO_FONT;

	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		rdx, 2;
	add		edi, 2;
JMP_E:

	mov		mainTextProc2TmpCharacter, eax;
	
	push	mainTextProc2ReturnAddress;
	ret;
mainTextProc2V131 ENDP

;-------------------------------------------;

mainTextProc2V137 PROC
	movsxd  r9, edi
	mov     rdx, [rbp+2340h-2348h]
	add     r9, rdx
	movsxd  rcx, esi
	movzx   eax, byte ptr [r9]
	mov     r11, mainTextProc2BufferAddress
	mov     byte ptr[rcx+r11], al
	inc     esi
	inc		rcx

	cmp		al, ESCAPE_SEQ_1
	jz		JMP_A
	cmp		al, ESCAPE_SEQ_2
	jz		JMP_B
	cmp		al, ESCAPE_SEQ_3
	jz		JMP_C
	cmp		al, ESCAPE_SEQ_4
	jz		JMP_D
	jmp		JMP_E

JMP_A:
	movzx	eax, word ptr[r9+1];
	mov		word ptr [rcx+r11], ax;
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[r9+1];
	mov		word ptr [rcx+r11], ax;
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [r9+1];
	mov		word ptr [rcx+r11], ax;
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [r9+1];
	mov		word ptr [rcx+r11], ax;
	add		eax, SHIFT_4;

JMP_F:
	movzx	eax, ax;
	add		esi, 2;
	add		rcx,2;
	cmp		eax, NO_FONT;

	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		edi, 2;
	add		r9, 2;
JMP_E:

	mov		mainTextProc2TmpCharacter, eax;
	
	push	mainTextProc2ReturnAddress;
	ret;
mainTextProc2V137 ENDP

;-------------------------------------------;

mainTextProc3 PROC
	cmp		word ptr [rcx+6],0;
	jnz		JMP_A;
	jmp		JMP_B;

JMP_A:
	cmp		mainTextProc2TmpCharacter, 00FFh;
	ja		JMP_B;

	push	mainTextProc3ReturnAddress2;
	ret;
	
JMP_B:
	lea     eax, dword ptr [rbx+rbx];
	movd    xmm1, eax;

	push	mainTextProc3ReturnAddress1;
	ret;

mainTextProc3 ENDP

;-------------------------------------------;

mainTextProc4 PROC
	; check code point saved proc1
	cmp		mainTextProc2TmpCharacter, 00FFh;
	ja		JMP_A;

	movzx	eax, byte ptr[rdx + r10];
	jmp		JMP_B;

JMP_A:
	mov		eax, mainTextProc2TmpCharacter;

JMP_B:
	mov		rcx, qword ptr [r15 + rax*8];
	mov		qword ptr [rbp-60h],rcx;
	test	rcx,rcx;

	push	mainTextProc4ReturnAddress;
	ret;
mainTextProc4 ENDP

;-------------------------------------------;

mainTextProc4V137 PROC
	; check code point saved proc1
	cmp		mainTextProc2TmpCharacter, 00FFh;
	ja		JMP_A;

	movzx	eax, byte ptr[r9];
	jmp		JMP_B;

JMP_A:
	mov		eax, mainTextProc2TmpCharacter;

JMP_B:
	mov     rcx, [r14+rax*8+120h]
	mov     [rbp+2340h-2340h], rcx
	test	rcx,rcx;

	push	mainTextProc4ReturnAddress;
	ret;
mainTextProc4V137 ENDP

END