global jump_usermode

jump_usermode:

    mov ebx, [esp+4]

    mov ax, 0x20
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax ; SS is handled by iret

    ; set up the stack frame iret expects
    mov eax, esp

    push 0x23 ; data selector
    push eax ; current esp
    pushf ; eflags
    push 0x1b ; code selector (ring 3 code with bottom 2 bits set for ring 3)
    push ebx ; instruction address to return to
    iret