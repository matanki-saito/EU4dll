
.CODE
inline_make_reg_pack_and_call macro
procbeg:
	pushfq;
	push	r15;
	push	r14;
	push	r13;
	push	r12;
	push	r11;
	push	r10;
	push	r9;
	push	r8;
	push	rax;
	push	rcx;
	push	rdx;
	push	rbx;
	push	rsp;
	push	rbp;
	push	rsi;
	push	rdi;

;add dword ptr[esp+12], 8     ; Add 4 to reg_pack::esp 'cuz of our return pointer, let it be as before this func is called

; Call wrapper sending reg_pack as parameter
	push rsp
;call W::call
	add rsp, 8

	pop	rdi;
	pop	rsi;
	pop	rbp;
	pop	rsp;
	pop	rbx;
	pop	rdx;
	pop	rcx;
	pop	rax;
	pop	r8;
	pop	r9;
	pop	r10;
	pop	r11;
	pop	r12;
	pop	r13;
	pop	r14;
	pop	r15;
	popfq;

	ret

ENDM inline_make_reg_pack_and_call
END