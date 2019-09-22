EXTERN mainTextProc1ReturnAddress: QWORD
EXTERN mainTextProc2ReturnAddress: QWORD
EXTERN mainTextProc2BufferAddress: QWORD
EXTERN mainTextProc3ReturnAddress1: QWORD
EXTERN mainTextProc3ReturnAddress2: QWORD

.DATA
	mainTextProc2TmpCharacter	DD	0

.CODE
mainTextProc1 PROC
	movsxd rax, edi;

	cmp byte ptr[rax + rbx], 10h;
	jz JMP_A;
	cmp byte ptr[rax + rbx], 11h;
	jz JMP_B;
	cmp byte ptr[rax + rbx], 12h;
	jz JMP_C;
	cmp byte ptr[rax + rbx], 13h;
	jz JMP_D;
	movzx eax, byte ptr [rax+rbx];
	jmp JMP_E;

JMP_A:
	movzx eax, word ptr[rax + rbx + 1];
	jmp JMP_F;

JMP_B:
	movzx eax, word ptr[rax + rbx + 1];
	sub eax, 0Eh;
	jmp JMP_F;

JMP_C:
	movzx eax, word ptr[rax + rbx + 1];
	add eax, 900h;
	jmp JMP_F;

JMP_D:
	movzx eax, word ptr[rax + rbx + 1];
	add eax, 8F2h;

JMP_F:
	movzx eax, ax;
	add edi, 2;
	cmp eax, 98Fh;

	ja JMP_E;
	mov eax, 2026h;
JMP_E:
	movss xmm3, dword ptr [r15+848h];
	mov rbx, qword ptr [r15+rax*8];
	mov qword ptr [rbp+100h], rbx;

	push mainTextProc1ReturnAddress;
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

	cmp al, 10h;
	jz JMP_A;
	cmp al, 11h;
	jz JMP_B;
	cmp al, 12h;
	jz JMP_C;
	cmp al, 13h;
	jz JMP_D;
	jmp JMP_E;

JMP_A:
	movzx eax, word ptr[rdx+r10+1];
	mov word ptr [rcx+r9], ax;
	jmp JMP_F;

JMP_B:
	movzx	eax, word ptr[rdx+r10+1];
	mov	word ptr [rcx+r9], ax;
	sub eax, 0Eh;
	jmp JMP_F;

JMP_C:
	movzx eax, word ptr [rdx+r10+1];
	mov	word ptr [rcx+r9], ax;
	add eax, 900h;
	jmp JMP_F;

JMP_D:
	movzx eax, word ptr [rdx+r10+1];
	mov	word ptr [rcx+r9], ax;
	add eax, 8F2h;

JMP_F:
	movzx eax, ax;
	add r14d, 2;
	add rcx,2;
	cmp eax, 98Fh;

	ja JMP_G;
	mov eax, 2026h;

JMP_G:
	add rdx, 2;
	add edi, 2;
JMP_E:

	mov mainTextProc2TmpCharacter, eax;
	
	push mainTextProc2ReturnAddress;
	ret;
mainTextProc2 ENDP

;-------------------------------------------;

mainTextProc3 PROC
	cmp word ptr [rcx+6],0;
	jnz JMP_A;
	jmp JMP_B;

JMP_A:
	cmp mainTextProc2TmpCharacter, 00FFh;
	ja JMP_B;

	push mainTextProc3ReturnAddress2;
	ret;
	
JMP_B:
	lea     eax, dword ptr [rbx+rbx];
	movd    xmm1, eax;

	push mainTextProc3ReturnAddress1;
	ret;

mainTextProc3 ENDP

END