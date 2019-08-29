D3META STRUCT
    dll    QWORD  ?
    Direct3DCreate9     QWORD  ?
    Direct3DCreate9Ex   QWORD  ?
D3META ENDS

EXTERN d3d9meta: STRUCT
EXTERN e: DWORD

.CODE
_Direct3DCreate9 proc
	jmp (D3META PTR d3d9meta).Direct3DCreate9
_Direct3DCreate9 endp

_Direct3DCreate9Ex proc
	jmp (D3META PTR d3d9meta).Direct3DCreate9Ex
_Direct3DCreate9Ex endp

hoge proc
	mov e,6;
	ret
hoge endp

END