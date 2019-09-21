EXTERN mainTextProc1ReturnAddress: QWORD

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
END