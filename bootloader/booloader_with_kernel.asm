bits 16
org 0x7c00

; This file is a combination of BHam How to Write an OS, os dev tutorials and a lot of trial and error

; If memory issues occur remember that the Kernel is loaded at 0x10000.
; If its too large could it potentially write over any needed addresses?
; Consider the need to relocate the kernel (os dev forum) investigate rep movsb
; https://wiki.osdev.org/Higher_Half_Kernel

; This will lead to the kernel being loaded into 0x10000 (check why?)
; A full explanation can be found at https://wiki.osdev.org/Rolling_Your_Own_Bootloader
KERNEL_SEG equ 0x1000
KERNEL_OFFSET equ 0x0
READ_DISKS equ 127
REAL_STACK equ 0x9000
KERNEL_STACK equ 0x90000


BOOT_DRIVE: db 0
mov [BOOT_DRIVE], dl

; Set up the stack
mov bp, REAL_STACK
mov sp, bp

call load_kernel
call switch_to_protected

; Should be unreachable
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

    ; Rather than just set bx to offset (like in bham guide)
    ; Use implementation from here, will help down the line. Changed to fix mem issue
    mov ax, KERNEL_SEG
    mov es, ax
    mov bx, KERNEL_OFFSET
    mov dh, READ_DISKS
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

    ; Set up kernel stack
    mov ebp, KERNEL_STACK
    mov esp, ebp

    call KERNEL_OFFSET

    jmp $

; Global variable
MSG_REAL_MODE: db "Started in 16-bit Real Mode", 0
MSG_LOAD_KERNEL: db "Loading kernel into memory", 0
MSG_PROT_MODE: db "Successfully landed in 32-bit Protected Mode", 0


times 510-($-$$) db 0
dw 0xaa55