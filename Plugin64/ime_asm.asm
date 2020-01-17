EXTERN	imeProc1ReturnAddress1	:	QWORD
EXTERN	imeProc1ReturnAddress2	:	QWORD
EXTERN	imeProc1CallAddress	:	QWORD

EXTERN	imeProc2ReturnAddress1	:	QWORD
EXTERN	imeProc2ReturnAddress2	:	QWORD
EXTERN	imeProc2CallAddress	:	QWORD
EXTERN	rectAddress	:	QWORD

EXTERN	imeProc3ReturnAddress	:	QWORD
EXTERN	imeProc3CallAddress1	:	QWORD
EXTERN	imeProc3CallAddress2	:	QWORD
EXTERN	imeProc3CallAddress3	:	QWORD
EXTERN	imeProc3CallAddress4	:	QWORD
EXTERN	imeProc3CallAddress5	:	QWORD

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

.DATA
	aSdl_windows_no		DB	"SDL_WINDOWS_NO_CLOSE_ON_ALT_F4"

.CODE
imeProc1 PROC
	mov		edx, r13d;
	mov		rcx, r12;
	call	imeProc1CallAddress;
	test	eax,eax;
	jnz		JMP_A;

	push	imeProc1ReturnAddress1;
	ret;

JMP_A:
	push	imeProc1ReturnAddress2;
	ret;

imeProc1 ENDP

;-------------------------------------------;

imeProc2 PROC
	sub		edx, 0BCh;
	jz		JMP_A;

	push	imeProc2ReturnAddress2;
	ret;

JMP_A:
	mov		rcx, rectAddress;
	call	imeProc2CallAddress;

	push	imeProc2ReturnAddress1;
	ret;
imeProc2 ENDP

;-------------------------------------------;

imeProc3 PROC
	mov		rcx,qword ptr [rbp + 0C0h + 28h];
	mov		rdx, r14;
	call	imeProc3CallAddress1;
	xor		ecx, ecx;
	mov		edi, eax;
	call	imeProc3CallAddress2;
	cmp		byte ptr [rax + 0E2h], sil;
	jz      JMP_A;
	cmp		byte ptr [rax + 0E6h], sil;
	jnz		JMP_B;

JMP_A:
	cmp		edi, 3Dh;
	jnz		JMP_B;
	lea		rcx, aSdl_windows_no;
	call	imeProc3CallAddress3;
	test	rax, rax;
	jz		JMP_C;
	cmp		byte ptr [rax], 30h;
	jnz		JMP_E;

JMP_C:
	mov		rcx, qword ptr [rbx];
	xor		r9d, r9d;
	xor		r8d, r8d;
	mov		dl, 0Eh;
	call	imeProc3CallAddress4;
	jmp     JMP_E;

JMP_B:
	test	edi, edi;
	jz		JMP_D;

JMP_E:
	cmp		r14,229; –{“–‚É‚â‚è‚½‚©‚Á‚½‚Ì‚Í‚±‚±‚¾‚¯
	jz		JMP_D;
	mov		edx, edi
	movzx	ecx, sil;
	call    imeProc3CallAddress5;

JMP_D:
	push	imeProc3ReturnAddress;
	ret;
imeProc3 ENDP

END