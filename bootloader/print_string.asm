bits 16

print_string:
    pusha
    mov ah, 0x0e

print_string_loop:
    mov al, [bx]
    int 0x10

    cmp al, 0
    je print_string_pm_done

    add bx, 1

    jmp print_string_loop


print_string_done:
    mov al, 'I'
    int 0x10
    popa
    ret
