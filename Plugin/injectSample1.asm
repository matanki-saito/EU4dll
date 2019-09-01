
EXTERN injectSampleFunc1ReturnAddress: QWORD
EXTERN textAddress: QWORD
EXTERN textAddress2: QWORD

.CODE
injectSampleFunc1 proc
	add rcx, 260h;
	mov rdx, textAddress;
	push injectSampleFunc1ReturnAddress;
	ret;
injectSampleFunc1 endp

injectSampleFunc2 proc
	add rcx, 260h;
	mov rdx, textAddress2;
	xchg rax, [rsp];
	add rax, 8;
	xchg [rsp],rax;
	ret;
injectSampleFunc2 endp

END