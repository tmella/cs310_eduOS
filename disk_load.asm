
bits 16

disk_load:
    push dx

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13

    jc disk_error

    pop dx

    cmp dh, al ; If not all expected sectors have been read
    jne disk_error
    ret

disk_error:
    jmp $