EXTERN fontBufferHeapZeroClearReturnAddress: QWORD
EXTERN fontBufferHeapZeroClearHeapJmpAddress: QWORD
EXTERN fontBufferHeapZeroClearHeepAllocJmpAddress: QWORD

.CODE
fontBufferHeapZeroClear PROC
	; Maybe you want to write 'mov rcx, qword ptr[fontBufferHeapZeroClearHeapJmpAddress]',
	; but it does not work correctly.
	mov		rcx, fontBufferHeapZeroClearHeapJmpAddress;
	mov		rcx, qword ptr [rcx];
	mov		r8,rbx;
	mov		edx,8h;
	mov		rax, fontBufferHeapZeroClearHeepAllocJmpAddress;
	call	qword ptr [rax];
	test	rax,rax;
	push	fontBufferHeapZeroClearReturnAddress;
	ret;
fontBufferHeapZeroClear ENDP
END