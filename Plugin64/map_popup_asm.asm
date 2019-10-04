EXTERN	mapPopupProc1ReturnAddress		:	QWORD
EXTERN	mapPopupProc1CallAddress		:	QWORD
EXTERN	mapPopupProc2ReturnAddress		:	QWORD
EXTERN	mapPopupProc3ReturnAddress		:	QWORD

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
	mapPopupProc1TmpCharacterAddress	DQ	0
	mapPopupProc1MultibyteFlag			DD	0

.CODE
mapPopupProc1 PROC
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_2;
	jz		JMP_A;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_3;
	jz		JMP_A;
	cmp		byte ptr[rdi + rax], ESCAPE_SEQ_4;
	jz		JMP_A;

	movzx	r8d, byte ptr [rdi + rax];
	mov     edx, 1;
	lea		rcx, [rbp - 30h];
	call	mapPopupProc1CallAddress;
	jmp		JMP_B;

JMP_A:
	lea		rdx, qword ptr [rdi + rax];
	mov		mapPopupProc1TmpCharacterAddress, rdx;
	mov		edx, 3;  The memory is allocated 3 byte, but the first byte is copied 3 times.
	lea		rcx, [rbp - 30h];
	call	mapPopupProc1CallAddress;

	; overwrite
	mov		rcx, mapPopupProc1TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx; 

JMP_B:
	push	mapPopupProc1ReturnAddress;
	ret;
mapPopupProc1 ENDP

;-------------------------------------------;

mapPopupProc2 PROC
	cmp		byte ptr[rax + rdi], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rax + rdi], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rax + rdi], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rax + rdi], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rax+rdi];
	jmp		JMP_H;

JMP_A:
	movzx	eax, word ptr[eax + edi + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr[eax + edi + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr[eax + edi + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr[eax + edi + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		edi, 2;

JMP_H:
	mov     r14, qword ptr [r15 + rax * 8 + 100h];
	test	r14, r14;

	push	mapPopupProc2ReturnAddress;
	ret;
mapPopupProc2 ENDP

;-------------------------------------------;

mapPopupProc3 PROC
	cmp		byte ptr[rbx + rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr[rbx + rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr[rbx + rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr[rbx + rax], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rbx + rax];
	jmp		JMP_H;

JMP_A:
	movzx	eax, word ptr[rbx + rax + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr[rbx + rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr[rbx + rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr[rbx + rax + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
	mov		eax, NOT_DEF;

JMP_G:
	add		ebx, 2;

JMP_H:
	mov     r11, qword ptr [r15 + rax * 8 + 100h];
	mov     qword ptr [rbp + 80h], r11;

	push	mapPopupProc3ReturnAddress;
	ret;
mapPopupProc3 ENDP

END