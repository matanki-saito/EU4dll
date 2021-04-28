EXTERN	listFieldAdjustmentProc1ReturnAddress	:	QWORD
EXTERN	listFieldAdjustmentProc2ReturnAddress	:	QWORD
EXTERN	listFieldAdjustmentProc3ReturnAddress	:	QWORD

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
	listFieldAdjustmentProc1MultibyteFlag			DD	0
	listFieldAdjustmentProc2MultibyteFlag			DD	0

.CODE
listFieldAdjustmentProc1 PROC
	mov		r8, qword ptr [rbp + 0B0h - 118h];
	movss	xmm6, dword ptr [r8 + 848h];

	cmp		byte ptr[r12 + rax], ESCAPE_SEQ_1;
	jz		JMP_A;

	cmp		byte ptr[r12 + rax], ESCAPE_SEQ_2;
	jz		JMP_B;

	cmp		byte ptr[r12 + rax], ESCAPE_SEQ_3;
	jz		JMP_C;

	cmp		byte ptr[r12 + rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	
	movzx	eax, byte ptr[r12 + rax];
	jmp		JMP_G;

JMP_A:
	movzx	eax, word ptr[r12 + rax + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr[r12 + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr[r12 + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr[r12 + rax + 1];
	add		eax, SHIFT_4;
	jmp		JMP_E;

JMP_E:
	mov		listFieldAdjustmentProc1MultibyteFlag, 1h;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov     r15, qword ptr [r8 + rax * 8];
	test    r15, r15;

	push	listFieldAdjustmentProc1ReturnAddress;
	ret;
listFieldAdjustmentProc1 ENDP

;-------------------------------------------;

listFieldAdjustmentProc1_v131 PROC
	mov		rcx, qword ptr [rbp + 0C0h - 128h];
	movss	xmm6, dword ptr [rcx + 848h];

	cmp		byte ptr[r12 + rax], ESCAPE_SEQ_1;
	jz		JMP_A;

	cmp		byte ptr[r12 + rax], ESCAPE_SEQ_2;
	jz		JMP_B;

	cmp		byte ptr[r12 + rax], ESCAPE_SEQ_3;
	jz		JMP_C;

	cmp		byte ptr[r12 + rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	
	movzx	eax, byte ptr[r12 + rax];
	jmp		JMP_G;

JMP_A:
	movzx	eax, word ptr[r12 + rax + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr[r12 + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr[r12 + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr[r12 + rax + 1];
	add		eax, SHIFT_4;
	jmp		JMP_E;

JMP_E:
	mov		listFieldAdjustmentProc1MultibyteFlag, 1h;
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	mov     r15, qword ptr [rcx + rax * 8];
	test    r15, r15;

	push	listFieldAdjustmentProc1ReturnAddress;
	ret;
listFieldAdjustmentProc1_v131 ENDP

;-------------------------------------------;

listFieldAdjustmentProc2 PROC
	cmp		listFieldAdjustmentProc1MultibyteFlag, 1h;
	jnz		JMP_A;
	mov		listFieldAdjustmentProc2MultibyteFlag, 1h;
	add		ebx,2;

JMP_A:
	inc		ebx;
	mov		listFieldAdjustmentProc1MultibyteFlag, 0h; reset

	mov		r9, qword ptr [rdi + 10h];
	movzx	edx, byte ptr [rbp + 0B0h + 048h];arg_8=0x48
	cmp		ebx, r9d;

	push	listFieldAdjustmentProc2ReturnAddress;
	ret;
listFieldAdjustmentProc2 ENDP

;-------------------------------------------;

listFieldAdjustmentProc2_v131 PROC
	cmp		listFieldAdjustmentProc1MultibyteFlag, 1h;
	jnz		JMP_A;
	mov		listFieldAdjustmentProc2MultibyteFlag, 1h;
	add		ebx,2;

JMP_A:
	inc		ebx;
	mov		listFieldAdjustmentProc1MultibyteFlag, 0h; reset

	mov		r10, qword ptr [rdi + 10h];
	movzx	edx, byte ptr [rbp + 0C0h + 048h];arg_38=0x48
	cmp		ebx, r10d;

	push	listFieldAdjustmentProc2ReturnAddress;
	ret;
listFieldAdjustmentProc2_v131 ENDP

;-------------------------------------------;

listFieldAdjustmentProc3 PROC
	mov		rcx, qword ptr [rax + rcx * 8];
	mov		r9d, dword ptr [rcx + rdx * 4];

	cmp		listFieldAdjustmentProc2MultibyteFlag, 1h;
	jnz		JMP_A;
	mov		r9d, ebx;
	sub		r9d, 3;

JMP_A:
	xor		r8d, r8d;
	lea		rdx, [rsp + 180h - 160h];
	mov		rcx, rdi;

	push	listFieldAdjustmentProc3ReturnAddress;
	ret;
listFieldAdjustmentProc3 ENDP
END