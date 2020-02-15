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

END