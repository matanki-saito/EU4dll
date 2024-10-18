EXTERN	mapViewProc1ReturnAddress	:	QWORD
EXTERN	mapViewProc2ReturnAddress	:	QWORD
EXTERN	mapViewProc3ReturnAddress	:	QWORD
EXTERN	mapViewProc4ReturnAddress	:	QWORD
EXTERN	mapViewProc3CallAddress		:	QWORD
EXTERN	mapViewProc3CallAddress		:	QWORD

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

; temporary space for code point
.DATA
	mapViewProc3TmpCharacterAddress	DQ	0

.CODE
mapViewProc1 PROC
	cmp		byte ptr [rax+r8], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax+r8], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rax+r8], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rax+r8], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr [rax + r8 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr [rax + r8 + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [rax + r8 + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [rax + r8 + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		ebx, 2;
	add		r8d, 2;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;
	jmp		JMP_G;

JMP_E:
	movzx	eax, byte ptr [rax + r8];

JMP_G:
	mov     r11, qword ptr [ rdi + rax * 8];

	;issue-161
	cmp		r11,0;
	jnz		JMP_N;

	; issue-237
	cmp		rax, 0FFh;
	jl		JMP_N;
	
	mov		eax, 2dh ; -
	mov     r11, qword ptr [ rdi + rax * 8];

JMP_N:
	mov     qword ptr [rbp + 38h], r11;
	movss   dword ptr [rbp + 40h], xmm2

	push	mapViewProc1ReturnAddress;
	ret;
mapViewProc1 ENDP

;-------------------------------------------;

mapViewProc1V137 PROC
	movss	dword ptr [rbp + 1060h - 10C0h], xmm3

	cmp		byte ptr [r9+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [r9+rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [r9+rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [r9+rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr [r9+rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr [r9+rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [r9+rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [r9+rax + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		r11d, 2;
	add		r9d, 2;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;
	jmp		JMP_G;

JMP_E:
	movzx   eax, byte ptr [r9+rax]

JMP_G:
	mov     rdx, qword ptr [r15+rax*8]

	;issue-161
	cmp		rdx,0;
	jnz		JMP_N;

	; issue-237
	cmp		rax, 0FFh;
	jl		JMP_N;
	
	mov		rax, 2dh ; -
	mov     rdx, qword ptr [r15+rax*8]

JMP_N:
	test    rdx, rdx
	push	mapViewProc1ReturnAddress;
	ret;
mapViewProc1V137 ENDP

;-------------------------------------------;

mapViewProc2 PROC
	lea     r9, [r12 + 100h];

	cmp		byte ptr[rax + r15], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + r15], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + r15], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + r15], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr[rax + r15];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax + r15 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax + r15 + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax + r15 + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax + r15 + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		esi, 2;
	add		r15, 2;

	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;

JMP_G:
	mov		eax, NOT_DEF;

JMP_E:
	mov     r12, qword ptr [r9 + rax * 8];

	push	mapViewProc2ReturnAddress;
	ret;
mapViewProc2 ENDP

;-------------------------------------------;

mapViewProc2V130 PROC
	lea     r9, [r12 + 120h];

	cmp		byte ptr[rax + r15], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + r15], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + r15], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + r15], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr[rax + r15];
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax + r15 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax + r15 + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax + r15 + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax + r15 + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		esi, 2;
	add		r15, 2;

	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;

JMP_G:
	mov		eax, NOT_DEF;

JMP_E:
	mov     r12, qword ptr [r9 + rax * 8];

	push	mapViewProc2ReturnAddress;
	ret;
mapViewProc2V130 ENDP

;-------------------------------------------;

mapViewProc2V137 PROC
	cmp		byte ptr[r15+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[r15+rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[r15+rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[r15+rax], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx   eax, byte ptr [r15+rax]
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[r15+rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[r15+rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[r15+rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[r15+rax + 1];
	add		eax, SHIFT_4;

JMP_F:
	add		r14d, 2;
	add		r15, 2;

	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_E;

JMP_G:
	mov		eax, NOT_DEF;

JMP_E:
	mov     r11, qword ptr [r9+rax*8+120h]
	test    r11, r11

	push	mapViewProc2ReturnAddress;
	ret;
mapViewProc2V137 ENDP

;-------------------------------------------;

mapViewProc3 PROC
    mov		qword ptr[rsp + 488h - 448h],0;

	cmp		byte ptr [rax + r15], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + r15], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr [rax + r15], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr [rax + r15], ESCAPE_SEQ_4;
	jz		JMP_A;

	movzx	r8d, byte ptr[rax + r15];
	mov     edx, 1;
	lea     rcx, qword ptr [rsp + 488h - 448h];
	call	mapViewProc3CallAddress;

	jmp		JMP_B;
JMP_A:
	lea		r8, qword ptr [rax + r15];
	mov		mapViewProc3TmpCharacterAddress, r8;
	movzx	r8d, byte ptr[rax + r15];
	mov     edx, 3; The memory is allocated 3 byte, but the first byte is copied 3 times.
	lea     rcx, qword ptr [rsp + 488h - 448h];
	call	mapViewProc3CallAddress;

	; overwrite
	mov		rcx, mapViewProc3TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx; 

JMP_B:
	push	mapViewProc3ReturnAddress;
	ret;
mapViewProc3 ENDP

;-------------------------------------------;

mapViewProc3V137 PROC
	cmp		byte ptr [r15+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [r15+rax], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr [r15+rax], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr [r15+rax], ESCAPE_SEQ_4;
	jz		JMP_A;

	movzx	r8d, byte ptr[r15+rax];
	mov     edx, 1;
	lea     rcx, qword ptr [rsp+1160h-1108h] ; 1108 = src
	call	mapViewProc3CallAddress;

	jmp		JMP_B;
JMP_A:
	lea		r8, qword ptr [r15+rax];
	mov		mapViewProc3TmpCharacterAddress, r8;
	movzx	r8d, byte ptr[r15+rax];
	mov     edx, 3; The memory is allocated 3 byte, but the first byte is copied 3 times.
	lea     rcx, qword ptr [rsp+1160h-1108h]
	call	mapViewProc3CallAddress;

	; overwrite
	mov		rcx, mapViewProc3TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx; 

JMP_B:
	push	mapViewProc3ReturnAddress;
	ret;
mapViewProc3V137 ENDP

;-------------------------------------------;

mapViewProc4V137 PROC
	lea     rcx, qword ptr [rsp+1160h-10E8h]
	cmp     rbx, 10h
	cmovnb  rcx, rsi
	movzx   r8d, byte ptr [rax+rcx]
	lea     rax, qword ptr [rsp+1160h-10E8h]
	cmovnb  rax, rsi
	movzx   edx, byte ptr [rax+r9]
	mov     rcx, r15

	push	mapViewProc4ReturnAddress;
	ret;
mapViewProc4V137 ENDP


END