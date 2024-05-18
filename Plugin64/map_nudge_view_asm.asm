EXTERN	mapNudgeViewProc1ReturnAddress	:	QWORD

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

.CODE
mapNudgeViewProc1 PROC
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rax + rcx];
	jmp		JMP_F;

JMP_A:
	movzx	eax, word ptr [rax + rcx + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr [rax + rcx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr [rax + rcx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr [rax + rcx + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	add		rcx, 2;
	cmp		eax, NO_FONT;
	ja		JMP_F;
	mov		eax, NOT_DEF;

JMP_F:
	mov		rdx, qword ptr [r12 + rax * 8 + 100h];
	test	rdx, rdx;

	push	mapNudgeViewProc1ReturnAddress;
	ret;
mapNudgeViewProc1 ENDP

;----------------------------------------;

mapNudgeViewProc1V130 PROC
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rax + rcx];
	jmp		JMP_F;

JMP_A:
	movzx	eax, word ptr [rax + rcx + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr [rax + rcx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr [rax + rcx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr [rax + rcx + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	add		rcx, 2;
	cmp		eax, NO_FONT;
	ja		JMP_F;
	mov		eax, NOT_DEF;

JMP_F:
	mov		rdx, qword ptr [r12 + rax * 8 + 120h];
	test	rdx, rdx;

	push	mapNudgeViewProc1ReturnAddress;
	ret;
mapNudgeViewProc1V130 ENDP

;-------------------------------------------;

mapNudgeViewProc1V136 PROC
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rax + rcx], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rax + rcx];
	jmp		JMP_F;

JMP_A:
	movzx	eax, word ptr [rax + rcx + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr [rax + rcx + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr [rax + rcx + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr [rax + rcx + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	add		rcx, 2;
	cmp		eax, NO_FONT;
	ja		JMP_F;
	mov		eax, NOT_DEF;

JMP_F:
	mov		rdx, qword ptr [r15 + rax * 8 + 120h];
	test	rdx, rdx;

	push	mapNudgeViewProc1ReturnAddress;
	ret;
mapNudgeViewProc1V136 ENDP

;-------------------------------------------;

mapNudgeViewProc1V137 PROC
	cmp		byte ptr [rcx+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rcx+rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rcx+rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rcx+rax], ESCAPE_SEQ_4;
	jz		JMP_D;

	movzx	eax, byte ptr [rcx+rax];
	jmp		JMP_F;

JMP_A:
	movzx	eax, word ptr [rcx+rax + 1];
	jmp		JMP_E;

JMP_B:
	movzx	eax, word ptr [rcx+rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_E;

JMP_C:
	movzx	eax, word ptr [rcx+rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_E;

JMP_D:
	movzx	eax, word ptr [rcx+rax + 1];
	add		eax, SHIFT_4;

JMP_E:
	movzx	eax, ax;
	add		rcx, 2;
	cmp		eax, NO_FONT;
	ja		JMP_F;
	mov		eax, NOT_DEF;

JMP_F:
	mov     rdx, qword ptr [r12+rax*8+120h]
	test	rdx, rdx;

	push	mapNudgeViewProc1ReturnAddress;
	ret;
mapNudgeViewProc1V137 ENDP
END
