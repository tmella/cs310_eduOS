bits 16
org 0x7c00

KERNEL_OFFSET equ 0x1000

BOOT_DRIVE: db 0
mov [BOOT_DRIVE], dl

mov bp, 0x9000 ; Set-up the stack.
mov sp, bp

call load_kernel
call switch_to_protected

jmp $


%include "bootloader/disk_load.asm"
%include "bootloader/gdt.asm"
%include "bootloader/protected-switch.asm"
%include "bootloader/print_string.asm"
%include "bootloader/print_string_pm.asm"


bits 16
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET
    mov dh , 15
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret


bits 32
start_protected_mode:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    ; This causes it to flash
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call KERNEL_OFFSET

    jmp $

; Global variable
MSG_REAL_MODE: db "Started in 16-bit Real Mode", 0
MSG_LOAD_KERNEL: db "Loading kernel into memory", 0
MSG_PROT_MODE: db "Successfully landed in 32-bit Protected Mode", 0


times 510-($-$$) db 0
dw 0xaa55