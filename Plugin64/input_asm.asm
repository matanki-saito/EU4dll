EXTERN	inputProc1ReturnAddress1	:	QWORD
EXTERN	inputProc1ReturnAddress2	:	QWORD
EXTERN	inputProc1CallAddress		:	QWORD
EXTERN	inputProc2ReturnAddress		:	QWORD

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
	inputProc1Var1	DB		03,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
	inputProc1Tmp	DQ		0
	inputProc2Tmp	DQ		0

.CODE
inputProc1 PROC
	; eaxにはIMEからutf8の文字が渡されてくる
	mov		eax, dword ptr [rbp + 120h - 198h + 0Ch];
	; ahが0であればa-zなどの1byteで収まる文字なので、変換処理は必要ない
	cmp		ah, 0;
	jnz		JMP_A;
	xor		bl, bl;

	; JMP_X,Yについての説明。MakeJMPでコードが破壊されてしまうため、処理を丸ごとコピーしてきている。
	; ここで80hと比較しているのはUTF8でU+0000 … U+007Fかどうか確認するため
	; https://ja.wikipedia.org/wiki/UTF-8
	cmp		al, 80h;
	jnb		JMP_X;
	mov		ebx, eax;
	jmp     JMP_Y;

JMP_X:
	cmp		al, 0E0h;
	jnb		JMP_Y;
	movzx	ebx, byte ptr [rbp + 120h - 198h + 0Dh];
	and		bl, 3Fh;
	shl		al, 6;
	or		bl, al;

JMP_Y:
	push	inputProc1ReturnAddress1;
	ret;

JMP_A:
	lea		rcx,[rbp + 120h - 198h + 0Ch];
	call	inputProc1CallAddress;
	; 変換したエスケープ済みテキストアドレスを保存。 10 81 82のようになる
	mov		inputProc2Tmp, rax;
	;カウンタとして使うのでもともとあったものは保存
	mov		inputProc1Tmp,rsi;
	xor		rsi,rsi;

JMP_B:
	; そのままコピーした
	mov		rax, [r14];
	lea     rdx, [rsp+200h - 1D0h];
	xorps	xmm0, xmm0;
	mov		qword ptr [rsp+200h - 1D0h], 0;
	movdqu	xmmword ptr [rsp + 200h - 1C0h], xmm0;
	mov		rcx, r14;
	mov		dword ptr [rsp + 200h + 1C8h], edi;
	movdqa  xmm0, xmmword ptr [inputProc1Var1];
	movdqu  xmmword ptr [rsp + 200h - 198h], xmm0;

	; １byte取り出す
	mov		rbx, inputProc2Tmp;
	mov		bl, byte ptr [rbx + rsi];

	; null文字チェック
	cmp		bl,0;
	jz		JMP_C;

	mov		byte ptr [rsp + 200h - 1C4h], bl;
	mov		qword ptr [rsp + 200h - 1B0h], 0;
	mov		dword ptr [rsp + 200h - 1A8h], edi;
	mov		qword ptr [rsp + 200h - 1A0h], rdi;
	mov		dword ptr [rsp + 200h - 188h], edi;
	mov		dword ptr [rbp + 120h - 1A0h], 2;
	mov		word ptr [rbp + 120h - 1A0h + 4], di;
	mov		byte ptr [rbp + 120h - 1A0h + 6], 0;
	call	qword ptr [rax + 18h];

	; 1byte進める
	inc		rsi;
	jmp		JMP_B;

JMP_C:
	;戻す
	mov		rsi, inputProc1Tmp;

	push	inputProc1ReturnAddress2;
	ret;
inputProc1 ENDP

;-------------------------------------------;

; 下記はqword ptr [rax+138h];の関数（40 57 48 83 EC 20 48 8B 01 48 8B F9 48 8B 90 68 01 00 00）から割り出した
; rdi+54h : キャレット位置
; rdi+40h : 文字列長さ
; rdi+30h : 文字列アドレス

inputProc2 PROC
	mov		rax, qword ptr [rdi];
	mov		rcx, rdi;
	test	ebx, ebx;
	jz		JMP_A;
	call	qword ptr [rax+140h];
	jmp		JMP_B;

JMP_A:
	call	qword ptr [rax+138h];

JMP_B:
	push	inputProc2ReturnAddress;
	ret;
inputProc2 ENDP
END