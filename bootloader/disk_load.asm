; THIS FILE WORKS


bits 16

; Here we make the most of the BIOS interrupt to load from disk

disk_load:
    push dx

    mov ah, 0x02 ; Set to read
    mov al, dh ; Al stores number of sector to use
    mov ch, 0x00 ; cylinder
    mov dh, 0x00 ; Head
    mov cl, 0x02 ; Sector from which to start

    int 0x13

    jc disk_error_1 ; Carry bit will be added in case of error

    pop dx

    cmp dh, al ; If not all expected sectors have been read
    jne disk_error_2
    ret

disk_error_1:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

disk_error_2:
    mov bx, DISK_ERROR_MSG_2
    call print_string
    jmp $

DISK_ERROR_MSG db "Disk read error one!", 0
DISK_ERROR_MSG_2 db "Disk read error two !", 0