EXTERN fontBufferHeapZeroClearReturnAddress: QWORD

.CODE
fontBufferHeapZeroClear proc
	push fontBufferHeapZeroClearReturnAddress;
	ret;
fontBufferHeapZeroClear endp
END