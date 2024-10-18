; r13�͕����񃋁[�v�̃J�E���^�B�t�H���g�ɕ����������Ă��Ȃ��Ă��֌W�Ȃ�
; r10�͕������lenght
; edx�i[rbp+1D0h+var_138]�j�͕����|�W�V�����J�E���^

EXTERN	mapJustifyProc1ReturnAddress1	:	QWORD
EXTERN	mapJustifyProc1ReturnAddress2	:	QWORD
EXTERN	mapJustifyProc2ReturnAddress	:	QWORD
EXTERN	mapJustifyProc4ReturnAddress	:	QWORD

;temporary space for code point
.DATA
	mapJustifyProc1TmpFlag	DD	0
	debug	DQ	0

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
MAP_LIMIT		=	2Dh-3

.CODE
mapJustifyProc1 PROC
	movss   xmm9, dword ptr [rcx + 848h];

	mov		debug, rax;

	cmp		byte ptr [rax + r13], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rax + r13], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rax + r13], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rax + r13], ESCAPE_SEQ_4;
	jz		JMP_D;
	mov		mapJustifyProc1TmpFlag, 0h;
	movzx	esi, byte ptr [rax + r13];
	mov     rdi, qword ptr [rcx + rsi * 8];
	test	rdi, rdi;
	jz		JMP_I;
	jmp		mapJustifyProc1ReturnAddress1;

JMP_A:
	movzx	esi, word ptr [rax + r13 + 1];
	jmp		JMP_F;

JMP_B:
	movzx	esi, word ptr [rax + r13 + 1];
	sub		esi, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	esi, word ptr [rax + r13 + 1];
	add		esi, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	esi, word ptr [rax + r13 + 1];
	add		esi, SHIFT_4;

JMP_F:
	; ������dec�������̂܂�𐧌䂵�Ă���
	dec		r10;
	cmp		r13,MAP_LIMIT;
	ja		JMP_H;

	movzx	esi, si;
	cmp		esi, NO_FONT;
	ja		JMP_G;
JMP_H:
	mov		esi, NOT_DEF;

JMP_G:
	mov		mapJustifyProc1TmpFlag, 1h;
	mov     rdi, qword ptr [rcx + rsi * 8];
	mov		sil, ESCAPE_SEQ_1; // ���̕���sil���r����'��.�Ɣ�r���Ă���̂ł���̂œK���ɖ��߂�

	test	rdi, rdi;
	jz		JMP_I;
	push	mapJustifyProc1ReturnAddress1;
	ret;

JMP_I:
	push	mapJustifyProc1ReturnAddress2;
	ret;
mapJustifyProc1 ENDP

;-------------------------------------------;

mapJustifyProc1V137 PROC
	movss   xmm12, dword ptr [rdx+848h]

	cmp		byte ptr [rcx+rax], ESCAPE_SEQ_1;
	jz		JMP_A;
	cmp		byte ptr [rcx+rax], ESCAPE_SEQ_2;
	jz		JMP_B;
	cmp		byte ptr [rcx+rax], ESCAPE_SEQ_3;
	jz		JMP_C;
	cmp		byte ptr [rcx+rax], ESCAPE_SEQ_4;
	jz		JMP_D;
	movzx   eax, byte ptr [rcx+rax]	
	mov     byte ptr [rbp+7B0h+58h], al
	mov		mapJustifyProc1TmpFlag, 0h;
	jmp		JMP_I

JMP_A:
	movzx	eax, word ptr [rcx+rax + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr [rcx+rax + 1];
	sub		eax, SHIFT_2;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr [rcx+rax + 1];
	add		eax, SHIFT_3;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr [rcx+rax + 1];
	add		eax, SHIFT_4;

JMP_F:
	; ������dec�������̂܂�𐧌䂵�Ă���
	;dec		qword ptr [rbp+7B0h-650h]

	cmp		rcx,MAP_LIMIT;
	ja		JMP_H;

	movzx	eax, ax;
	cmp		eax, NO_FONT;
	ja		JMP_G;
JMP_H:
	mov		eax, NOT_DEF;

JMP_G:
	mov		mapJustifyProc1TmpFlag, 1h;
	mov     byte ptr [rbp+7B0h+58h], ESCAPE_SEQ_1 ; ���̕���sil���r����'��.�Ɣ�r���Ă���̂ł���̂œK���ɖ��߂�
	
JMP_I:
	mov     r14, qword ptr [rdx+rax*8]
	test    r14, r14
	push	mapJustifyProc1ReturnAddress1;
	ret;
mapJustifyProc1V137 ENDP

;-------------------------------------------;

mapJustifyProc2 PROC
	cmp		mapJustifyProc1TmpFlag, 1h;
	jnz		JMP_A;

	; 3byte = 1�������ǂ���
	cmp		r10, 2; 
	ja		JMP_A;
	inc		r10;
	inc		r10;
	mov		edx,1;

JMP_A:
	movd    xmm6, edx;

	; �G�X�P�[�v����
	cmp		mapJustifyProc1TmpFlag, 1h;
	jz		JMP_B;

	lea     eax, [r10 - 1]; ; -1���Ă���
	jmp		JMP_C;

JMP_B:
	lea     eax, [r10 - 2]; ; -2���Ă���

JMP_C:
	movd    xmm0, eax;
	cvtdq2ps xmm0, xmm0;

	push	mapJustifyProc2ReturnAddress;
	ret;
mapJustifyProc2 ENDP

;-------------------------------------------;

mapJustifyProc2V137 PROC

	mov     rax, [rbp+7B0h-648h]

	; �G�X�P�[�v����
	cmp		mapJustifyProc1TmpFlag, 1h;
	jz		JMP_B;

	dec     eax ; -1���Ă���
	jmp		JMP_C;

JMP_B:
	; 3byte = 1�������ǂ���
	cmp		rax, 3; 
	ja		JMP_A;
	inc		rax;
	mov		esi,1;

JMP_A:
	dec     eax;  -2���Ă���
	dec     eax

JMP_C:
	movd    xmm6, esi
	cvtdq2ps xmm6, xmm6
	movd    xmm1, eax

	push	mapJustifyProc2ReturnAddress;
	ret;
mapJustifyProc2V137 ENDP

;-------------------------------------------;

mapJustifyProc4 PROC
	movsd   xmm3, qword ptr [rbp + 1D0h - 168h];

	cmp		mapJustifyProc1TmpFlag, 1h;
	jnz		JMP_A;
	
	add     edx,3;
	add     r13,3;

	jmp		JMP_C;

JMP_A:
	inc     edx;
	inc     r13;

JMP_C:
	movsd   xmm4, qword ptr [rbp + 1D0h - 1B0h];
	movsd   xmm5, qword ptr [rbp + 1D0h - 1A8h];
	movsxd  rax, r10d;
	mov     qword ptr [rbp + 1D0h - 138h], rdx;

	push	mapJustifyProc4ReturnAddress;
	ret;
mapJustifyProc4 ENDP

;-------------------------------------------;

mapJustifyProc4V137 PROC
	cmp		mapJustifyProc1TmpFlag, 1h;
	jnz		JMP_A;
	
	add     esi,3;
	add     rcx,3;

	jmp		JMP_C;

JMP_A:
	inc     esi
	inc     rcx

JMP_C:
	mov     DWORD PTR [rbp+7B0h+38h], esi
	mov     QWORD PTR [rbp+7B0h-698h], rcx

	push	mapJustifyProc4ReturnAddress;
	ret;
mapJustifyProc4V137 ENDP

END