
.CODE
make_reg_pack_and_call proc

; Construct the reg_pack structure on the stack
pushfq              ; Pushes EFLAGS to reg_pack
;pushad              ; Pushes general purposes registers to reg_pack
;add dword ptr[esp+12], 8     ; Add 4 to reg_pack::esp 'cuz of our return pointer, let it be as before this func is called

; Call wrapper sending reg_pack as parameter
;push esp
;call W::call
;add esp, 4

; Destructs the reg_pack from the stack
;sub dword ptr[esp+12], 8   ; Fix reg_pack::esp before popping it (doesn't make a difference though) (+4 because eflags)
;popad
popfq               ; Warning: Do not use any instruction that changes EFLAGS after this (-> sub affects EF!! <-)


; Back to normal flow
ret
make_reg_pack_and_call endp
END