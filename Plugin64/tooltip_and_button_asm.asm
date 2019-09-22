EXTERN tooltipAndButtonProc1ReturnAddress: QWORD
EXTERN tooltipAndButtonProc1CallAddress : QWORD
EXTERN tooltipAndButtonProc2ReturnAddress : QWORD
EXTERN tooltipAndButtonProc3ReturnAddress : QWORD

; 後で使うので一時的にコードポイントを入れておく
.DATA
	tooltipAndButtonProc2TmpCharacter	DD	0
	tooltipAndButtonProc2TmpCharacterAddress	DQ	0

.CODE
tooltipAndButtonProc1 PROC
	; 1文字目をみる
	cmp		byte ptr [rax + rcx], 10h;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], 11h;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], 12h;
	jz		JMP_A;
	cmp		byte ptr [rax + rcx], 13h;
	jz		JMP_A;

	movzx	r8d, byte ptr[rax + rcx];
	mov     edx, 1;
	lea     rcx, qword ptr [rbp + 6E0h - 6B0h];
	call	tooltipAndButtonProc1CallAddress;

	jmp		JMP_B;
JMP_A:
	lea		r8, qword ptr [rax + rcx];
	mov		tooltipAndButtonProc2TmpCharacterAddress, r8;
	movzx	r8d, byte ptr[rax + rcx];
	mov     edx, 3; ;3byte確保されるが、先頭の1byteが３つコピーされる…
	lea     rcx, qword ptr [rbp + 6E0h - 6B0h];
	call	tooltipAndButtonProc1CallAddress;

	; 塗りつぶす
	mov		rcx, tooltipAndButtonProc2TmpCharacterAddress;
	mov		cx, word ptr [rcx+1];
	mov		word ptr [rax+1], cx; 

JMP_B:
	push	tooltipAndButtonProc1ReturnAddress;
	ret;
tooltipAndButtonProc1 ENDP

;-------------------------------------------;

tooltipAndButtonProc2 PROC
	mov		edx, ebx;

	cmp		byte ptr[rax+rdx], 10h;
	jz		JMP_A;
	cmp		byte ptr[rax+rdx], 11h;
	jz		JMP_B;
	cmp		byte ptr[rax+rdx], 12h;
	jz		JMP_C;
	cmp		byte ptr[rax+rdx], 13h;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax+rdx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax+rdx + 1];
	sub		eax, 0Eh;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax+rdx + 1];
	add		eax, 900h;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax+rdx + 1];
	add		eax, 8F2h;
	jmp		JMP_F;

JMP_E:
	movzx   eax, byte ptr [rax + rdx];
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;
	add		ebx,2;
	add		edx,2;
	mov		dword ptr [rbp+6E0h- 6C0h], ebx;

	cmp		eax, 98Fh;
	ja		JMP_G;
	mov		eax, 2026h;

JMP_G:
	mov		rcx, qword ptr [r15 + rax * 8];
	mov		qword ptr [rbp + 6E0h - 640h], rcx; // 640h is lpMem

	mov		tooltipAndButtonProc2TmpCharacter, eax;

	push	tooltipAndButtonProc2ReturnAddress;
	ret;
tooltipAndButtonProc2 ENDP

;-------------------------------------------;

tooltipAndButtonProc3 PROC
	mov     ecx, ebx;
	movss   xmm10, dword ptr [r15 + 848h];

	cmp		byte ptr[rax + rcx], 10h;
	jz		JMP_A;
	cmp		byte ptr[rax + rcx], 11h;
	jz		JMP_B;
	cmp		byte ptr[rax + rcx], 12h;
	jz		JMP_C;
	cmp		byte ptr[rax + rcx], 13h;
	jz		JMP_D;
	jmp		JMP_E;

JMP_A:
	movzx	eax, word ptr[rax + rcx + 1];
	jmp		JMP_F;

JMP_B:
	movzx	eax, word ptr[rax + rcx + 1];
	sub		eax, 0Eh;
	jmp		JMP_F;

JMP_C:
	movzx	eax, word ptr[rax + rcx + 1];
	add		eax, 900h;
	jmp		JMP_F;

JMP_D:
	movzx	eax, word ptr[rax + rcx + 1];
	add		eax, 8F2h;
	jmp		JMP_F;

JMP_E:
	movzx   eax, byte ptr [rax + rcx];
	jmp		JMP_G;

JMP_F:
	movzx	eax, ax;
	add		rsi, 2;
	cmp		eax, 98Fh;
	ja		JMP_G;
	mov		eax, 2026h;

JMP_G:
	mov     r11, qword ptr [r15 + rax * 8];

	push	tooltipAndButtonProc3ReturnAddress;
	ret;
tooltipAndButtonProc3 ENDP

END