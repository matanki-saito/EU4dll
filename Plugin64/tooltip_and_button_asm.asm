EXTERN	tooltipAndButtonProc1ReturnAddress	:	QWORD
EXTERN	tooltipAndButtonProc1CallAddress	:	QWORD
EXTERN	tooltipAndButtonProc2ReturnAddress	:	QWORD
EXTERN	tooltipAndButtonProc3ReturnAddress	:	QWORD
EXTERN	tooltipAndButtonProc4ReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProc4ReturnAddress2	:	QWORD
EXTERN	tooltipAndButtonProc5ReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProc5ReturnAddress2	:	QWORD
EXTERN	tooltipAndButtonProc7ReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProc7ReturnAddress2	:	QWORD
EXTERN	tooltipAndButtonProc8ReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProc9ReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProc9ReturnAddress2	:	QWORD
EXTERN	tooltipAndButtonProc10ReturnAddress1	:	QWORD
EXTERN	tooltipAndButtonProc10BufferWidth	:	QWORD

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
	tooltipAndButtonProc2TmpCharacter			DD	0
	tooltipAndButtonProc2TmpCharacterAddress	DQ	0
	tooltipAndButtonProc2TmpFlag				DD	0

.CODE
tooltipAndButtonProc1 PROC
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_4;
	jz		JMP_A;

	movzx	r8d, byte ptr[rax + rcx];
	mov     edx, 1;
	lea     rcx, qword ptr [rbp + 6E0h - 6B0h];
	mov		tooltipAndButtonProc2TmpFlag, 0h;
	call	tooltipAndButtonProc1CallAddress;

	jmp		JMP_B;
JMP_A:
	mov		tooltipAndButtonProc2TmpFlag, 1h;
	lea		r8, qword ptr [rax + rcx];
	mov		tooltipAndButtonProc2TmpCharacterAddress, r8;
	movzx	r8d, byte ptr[rax + rcx];
	mov     edx, 3; The memory is allocated 3 byte, but the first byte is copied 3 times.
	lea     rcx, qword ptr [rbp + 6E0h - 6B0h];
	call	tooltipAndButtonProc1CallAddress;

	; overwrite
	mov		rcx, tooltipAndButtonProc2TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx; 
JMP_B:
	push	tooltipAndButtonProc1ReturnAddress;
	ret;
tooltipAndButtonProc1 ENDP

;-------------------------------------------;

tooltipAndButtonProc1V133 PROC
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_4;
	jz		JMP_A;

	movzx	r8d, byte ptr[rax + rcx];
	mov     edx, 1;
	lea     rcx, qword ptr [rsp + 22D0h - 2258h];
	mov		tooltipAndButtonProc2TmpFlag, 0h;
	call	tooltipAndButtonProc1CallAddress;

	jmp		JMP_B;
JMP_A:
	mov		tooltipAndButtonProc2TmpFlag, 1h;

	; debug
	mov		r8, qword ptr [rbp + 21D0h - 2220h];

	lea		r8, qword ptr [rax + rcx];
	mov		tooltipAndButtonProc2TmpCharacterAddress, r8;
	movzx	r8d, byte ptr[rax + rcx];
	mov     edx, 3; The memory is allocated 3 byte, but the first byte is copied 3 times.
	lea     rcx, qword ptr [rsp + 22D0h - 2258h];
	call	tooltipAndButtonProc1CallAddress;

	; overwrite
	mov		rcx, tooltipAndButtonProc2TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx; 
JMP_B:
	push	tooltipAndButtonProc1ReturnAddress;
	ret;
tooltipAndButtonProc1V133 ENDP

;-------------------------------------------;

tooltipAndButtonProc1V137 PROC
	cmp		byte ptr [rax + rbx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + rbx], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr [rax + rbx], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr [rax + rbx], ESCAPE_SEQ_4;
	jz		JMP_A;

	movzx	r8d, byte ptr[rax + rbx];
	mov     edx, 1;
	lea     rcx, qword ptr [rsp + 2290h -2248h];
	mov		tooltipAndButtonProc2TmpFlag, 0h;
	call	tooltipAndButtonProc1CallAddress;

	jmp		JMP_B;
JMP_A:
	mov		tooltipAndButtonProc2TmpFlag, 1h;


	lea		r8, qword ptr [rax + rbx];
	mov		tooltipAndButtonProc2TmpCharacterAddress, r8;
	movzx	r8d, byte ptr[rax + rbx];
	mov     edx, 3; The memory is allocated 3 byte, but the first byte is copied 3 times.
	lea     rcx, qword ptr [rsp + 2290h - 2248h];
	call	tooltipAndButtonProc1CallAddress;

	; overwrite
	mov		rcx, tooltipAndButtonProc2TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx; 
JMP_B:
	push	tooltipAndButtonProc1ReturnAddress;
	ret;
tooltipAndButtonProc1V137 ENDP

;-------------------------------------------;

tooltipAndButtonProc2 PROC
	mov		edx, ebx;

	cmp		byte ptr[rax+rdx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax+rdx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax+rdx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax+rdx], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax+rdx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax+rdx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax+rdx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax+rdx + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_E:
	movzx   eax, byte ptr [rax + rdx];
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;
	add		edx,2;
	;mov		dword ptr [rbp+6E0h- 6C0h], ebx;

	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov		rcx, qword ptr [r15 + rax * 8];
	mov		qword ptr [rbp + 6E0h - 640h], rcx; ; 640h is lpMem

	mov		tooltipAndButtonProc2TmpCharacter, eax;

	push	tooltipAndButtonProc2ReturnAddress;
	ret;
tooltipAndButtonProc2 ENDP

;-------------------------------------------;

tooltipAndButtonProc2V133 PROC
	mov		edx, ebx;

	cmp		byte ptr[rax+rdx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax+rdx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax+rdx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax+rdx], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax+rdx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax+rdx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax+rdx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax+rdx + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_E:
	movzx   eax, byte ptr [rax + rdx];
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;
	add		edx,2;
	;mov		dword ptr [rbp+6E0h- 6C0h], ebx;

	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov		rcx, qword ptr [r15 + rax * 8];
	mov		qword ptr [rbp + 21D0h - 21F0h], rcx; 

	mov		tooltipAndButtonProc2TmpCharacter, eax;

	push	tooltipAndButtonProc2ReturnAddress;
	ret;
tooltipAndButtonProc2V133 ENDP

;-------------------------------------------;

tooltipAndButtonProc2V137 PROC
	mov     r9d, r14d

	cmp		byte ptr[r9+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[r9+rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[r9+rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[r9+rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[r9+rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[r9+rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[r9+rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[r9+rax + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_E:
	movzx   eax, byte ptr [r9+rax]
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;
	add		r9d,2;

	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov		tooltipAndButtonProc2TmpCharacter, eax;
	mov     r11, [rcx+rax*8]
	test    r11, r11

	push	tooltipAndButtonProc2ReturnAddress;
	ret;
tooltipAndButtonProc2V137 ENDP

;-------------------------------------------;

tooltipAndButtonProc3 PROC
	mov     ecx, ebx;
	movss   xmm10, dword ptr [r15 + 848h];

	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + rcx], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax + rcx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax + rcx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax + rcx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax + rcx + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_E:
	movzx   eax, byte ptr [rax + rcx];
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;
	add		ebx, 2;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov     r11, qword ptr [r15 + rax * 8];

	push	tooltipAndButtonProc3ReturnAddress;
	ret;
tooltipAndButtonProc3 ENDP

;-------------------------------------------;

tooltipAndButtonProc3V137 PROC
	mov     ecx, r15d
	movss   xmm11, dword ptr [rdx+848h]

	cmp		byte ptr[rcx+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rcx+rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rcx+rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rcx+rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rcx+rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rcx+rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rcx+rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rcx+rax + 1];
	add		eax, SHIFT_4;
	jmp		JMP_F;

JMP_E:
	movzx   eax, byte ptr [rcx+rax]
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;
	add		r15d, 2;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov     r8, [rdx+rax*8]
	mov     [rbp+2190h-2138h], r8

	push	tooltipAndButtonProc3ReturnAddress;
	ret;
tooltipAndButtonProc3V137 ENDP

;-------------------------------------------;

tooltipAndButtonProc4 PROC
	cmp		word ptr [rcx + 6], 0
	jz		JMP_A;

	cmp		tooltipAndButtonProc2TmpCharacter, 00FFh;
	ja		JMP_A;

	push	tooltipAndButtonProc4ReturnAddress1;
	ret;

JMP_A:
	cmp     dword ptr [rbp + 6E0h - 668h], 0;
	push	tooltipAndButtonProc4ReturnAddress2;
	ret;
tooltipAndButtonProc4 ENDP

;-------------------------------------------;

tooltipAndButtonProc4V133 PROC
	cmp		word ptr [rcx + 6], 0
	jz		JMP_A;

	cmp		tooltipAndButtonProc2TmpCharacter, 00FFh;
	ja		JMP_X;

	push	tooltipAndButtonProc4ReturnAddress1;
	ret;

JMP_X:
	nop;

JMP_A:
	cmp     dword ptr [rbp + 21D0h - 2210h], 0;
	push	tooltipAndButtonProc4ReturnAddress2;
	ret;
tooltipAndButtonProc4V133 ENDP

;-------------------------------------------;

tooltipAndButtonProc4V137 PROC
	cmp		word ptr [r11 + 6], 0
	jz		JMP_A;

	cmp		tooltipAndButtonProc2TmpCharacter, 00FFh;
	ja		JMP_X;

	push	tooltipAndButtonProc4ReturnAddress1;
	ret;

JMP_X:
	nop;

JMP_A:
	cmp		dword ptr [rbp+2190h-21E0h], 0
	push	tooltipAndButtonProc4ReturnAddress2;
	ret;
tooltipAndButtonProc4V137 ENDP

;-------------------------------------------;

tooltipAndButtonProc5 PROC
	lea     rcx, qword ptr [r12 + 100h];

	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx   edx, byte ptr [rbx + r14];
	jmp		JMP_G;

JMP_A:
	movzx	edx, word ptr[rbx + r14 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	edx, word ptr[rbx + r14 + 1];
	sub		edx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	edx, word ptr[rbx + r14 + 1];
	add		edx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	edx, word ptr[rbx + r14 + 1];
	add		edx, SHIFT_4;

JMP_F:
	movzx	edx, dx;
	cmp		edx, NO_FONT;
	ja		JMP_H;
	mov		edx, NOT_DEF;

JMP_H:
	add		rbx, 3;
	add		edi, 3;
	cmp		rbx, r13;
	ja		JMP_J;
	dec		rbx;
	dec		edi;

JMP_G:
	mov     rsi, qword ptr [rcx + rdx * 8];
	test    rsi, rsi;

	push	tooltipAndButtonProc5ReturnAddress1;
	ret;

JMP_J:
	push	tooltipAndButtonProc5ReturnAddress2;
	ret;
tooltipAndButtonProc5 ENDP

;-------------------------------------------;

tooltipAndButtonProc5V130 PROC
	lea     rcx, qword ptr [r12 + 120h];

	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rbx + r14], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx   edx, byte ptr [rbx + r14];
	jmp		JMP_G;

JMP_A:
	movzx	edx, word ptr[rbx + r14 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	edx, word ptr[rbx + r14 + 1];
	sub		edx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	edx, word ptr[rbx + r14 + 1];
	add		edx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	edx, word ptr[rbx + r14 + 1];
	add		edx, SHIFT_4;

JMP_F:
	movzx	edx, dx;
	cmp		edx, NO_FONT;
	ja		JMP_H;
	mov		edx, NOT_DEF;

JMP_H:
	add		rbx, 3;
	add		edi, 3;
	cmp		rbx, r13;
	ja		JMP_J;
	dec		rbx;
	dec		edi;

JMP_G:
	mov     rsi, qword ptr [rcx + rdx * 8];
	test    rsi, rsi;

	push	tooltipAndButtonProc5ReturnAddress1;
	ret;

JMP_J:
	movd    xmm0, eax
	push	tooltipAndButtonProc5ReturnAddress2;
	ret;
tooltipAndButtonProc5V130 ENDP

;-------------------------------------------;

tooltipAndButtonProc5V137 PROC
	lea     rcx, [r15+120h]

	cmp		byte ptr [rbx+rbp], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rbx+rbp], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rbx+rbp], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rbx+rbp], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx   edx, byte ptr [rbx+rbp];
	jmp		JMP_G;

JMP_A:
	movzx	edx, word ptr[rbx+rbp + 1];
	jmp		JMP_F;

JMP_B:
	movzx	edx, word ptr[rbx+rbp + 1];
	sub		edx, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	edx, word ptr[rbx+rbp + 1];
	add		edx, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	edx, word ptr[rbx+rbp + 1];
	add		edx, SHIFT_4;

JMP_F:
	movzx	edx, dx;
	cmp		edx, NO_FONT;
	ja		JMP_H;
	mov		edx, NOT_DEF;

JMP_H:
	add		rbx, 3;
	add		edi, 3;
	cmp		rbx, r12;
	ja		JMP_J;
	dec		rbx;
	dec		edi;

JMP_G:
	mov     r11, [rcx+rdx*8]
	test    r11, r11

	push	tooltipAndButtonProc5ReturnAddress1;
	ret;

JMP_J:
	movd    xmm0, eax
	push	tooltipAndButtonProc5ReturnAddress2;
	ret;
tooltipAndButtonProc5V137 ENDP

;-------------------------------------------;

tooltipAndButtonProc7 PROC
	cmp		tooltipAndButtonProc2TmpFlag, 1;
	jnz		JMP_A;

	add		ebx,2;

JMP_A:
	inc		ebx;
	cmp     ebx, dword ptr [rbp + 6E0h - 680h];
	jge		JMP_B;
	push	tooltipAndButtonProc7ReturnAddress1;
	ret;

JMP_B:
	push	tooltipAndButtonProc7ReturnAddress2;
	ret;
tooltipAndButtonProc7 ENDP

;-------------------------------------------;

tooltipAndButtonProc7V133 PROC
	cmp		tooltipAndButtonProc2TmpFlag, 1;
	jnz		JMP_A;

	add		ebx,2;

JMP_A:
	inc		ebx;
	cmp     ebx, dword ptr [rbp + 21D0h - 2228h];
	jge		JMP_B;
	push	tooltipAndButtonProc7ReturnAddress1;
	ret;

JMP_B:
	; debug
	mov		rdi, qword ptr [rbp + 21D0h - 2220h];

	push	tooltipAndButtonProc7ReturnAddress2;
	ret;
tooltipAndButtonProc7V133 ENDP

;-------------------------------------------;

tooltipAndButtonProc7V137 PROC
	cmp		tooltipAndButtonProc2TmpFlag, 1;
	jnz		JMP_A;

	add		r14d,2;

JMP_A:
	inc		r14d;
	cmp     r14d, dword ptr [rbp+2190h-21B8h]
	jl		JMP_B;
	mov     r15d, dword ptr [rbp+2190h+38h]
	push	tooltipAndButtonProc7ReturnAddress2;
	ret;

JMP_B:	
	push	tooltipAndButtonProc7ReturnAddress1;
	ret;
tooltipAndButtonProc7V137 ENDP

;-------------------------------------------;

tooltipAndButtonProc8 PROC
	mov     eax, [rbp + 22A0h - 2294h]
	xorps   xmm0, xmm0
	cvtsi2ss xmm0, rax
	comiss  xmm1, xmm0

	push	tooltipAndButtonProc8ReturnAddress1;
	ret;
tooltipAndButtonProc8 ENDP

;-------------------------------------------;

tooltipAndButtonProc9 PROC
	lea     rax, [rsp + 22D0h - 2280h]
	cmp     rdi, 10h
	cmovnb  rax, rsi
	cmp     byte ptr [rax+rdx], 0Ah
	jz      JMP_A;

	lea     rax, [rsp + 22D0h - 2280h]
	cmp     rdi, 10h
	cmovnb  rax, rsi
	cmp     byte ptr [rax + rdx], 0Dh
	jnz     JMP_B;

JMP_A:
	push	tooltipAndButtonProc9ReturnAddress1;
	ret;

JMP_B:
	push	tooltipAndButtonProc9ReturnAddress2;
	ret;

tooltipAndButtonProc9 ENDP

;-------------------------------------------;

tooltipAndButtonProc10 PROC
	movaps  xmm6, [rsp + 0F8h - 38h]
	mov		r15, tooltipAndButtonProc10BufferWidth;
	add		rax, r15
	add     rsp, 0F0h
	pop     r15

	push	tooltipAndButtonProc10ReturnAddress1;
	ret;
tooltipAndButtonProc10 ENDP

END