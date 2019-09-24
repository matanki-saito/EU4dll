EXTERN	mapAdjustmentProc1ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc1CallAddress		:	QWORD
EXTERN	mapAdjustmentProc2ReturnAddress		:	QWORD
EXTERN	mapAdjustmentProc3ReturnAddress1	:	QWORD
EXTERN	mapAdjustmentProc3ReturnAddress2	:	QWORD
EXTERN	mapAdjustmentProc4ReturnAddress		:	QWORD

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

	push	mapAdjustmentProc1ReturnAddress;
	ret;
mapAdjustmentProc1 ENDP

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
	cmovnb  rdx, qword ptr [rbp + 1F0h - 160h];
	mov		dx, word ptr [rbx + rax + 1];

	mov		word ptr[rbp + 1F0h - 1F0h], dx;
	add		rbx, 2;

JMP_C:
	push	mapAdjustmentProc2ReturnAddress;
	ret;
mapAdjustmentProc2 ENDP

;-------------------------------------------;

mapAdjustmentProc3 PROC
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
	cmp		eax, NO_FONT;
	ja		JMP_E;
	mov		eax, NOT_DEF;
	movzx	eax, ax;

JMP_E:

	push	mapAdjustmentProc4ReturnAddress;
	ret;
mapAdjustmentProc4 ENDP
END