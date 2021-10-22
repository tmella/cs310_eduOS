;
;bits 16
;org 0x7c00
;
;KERNEL_OFFSET equ 0x1000
;
;mov [BOOT_DRIVE], dl ; BIOS stores the boot drive in dl best to have for later
;
;mov bp, 0x9000
;mov sp, bp
;
;;call load_kernel_code
;call switch_to_pm
;
;jmp $
;
;%include "gdt.asm"
;
;%include "disk_load.asm"
;
;switch_to_pm:
;    cli ;Switch off all interrupts
;    lgdt [gdt_descriptor]
;
;    mov eax, cr0
;    or eax, 0x1
;    mov cr0, eax
;
;    jmp CODE_SEG:init_pm
;
;
;;load_kernel_code:
;;    mov bx, KERNEL_OFFSET
;;    mov dh, 15
;;    mov dl, [BOOT_DRIVE]
;;    call disk_load
;;
;;    ret
;
;bits 32
;init_pm:
;    mov ax, DATA_SEG
;    mov ds, ax
;    mov ss, ax
;    mov es, ax
;    mov fs, ax
;    mov gs, ax
;
;    mov ebp, 0x90000
;    mov esp, ebp
;
;    call init_pro_mode


bits 16
org 0x7c00

KERNEL_OFFSET equ 0x1000

BOOT_DRIVE: db 0
mov [BOOT_DRIVE], dl

mov bp, 0x9000 ; Set-up the stack.
mov sp, bp

;call load_kernel

call switch_to_pm


switch_to_pm:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:start_protected_mode


%include "print_string_pm.asm"
%include "gdt.asm"

bits 32
start_protected_mode:
    mov ebx, MSG_LOAD_KERNEL
    call print_string_pm

    ; Start KERNEL

    jmp $


; Global variable
MSG_LOAD_KERNEL: db "Loading kernel into memory", 0
MSG_PROT_MODE: db "Successfully landed in 32-bit Protected Mode", 0


times 510-($-$$) db 0
dw 0xaa55