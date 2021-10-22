; ------------------------------------------------ ;
;        Boot loader for protected mode
; ----------------------------------------------- ;

bits 16
org 0x7c00 ; Tells NASM that are program is loaded at 0x7c00

; Here we could define the Kernel offset

switch_to_pm:
    cli ; Disable interrupts
    lgdt [gdt_descriptor]

    mov eax , cr0 ; Move the content of CR0 to General register EAX
    or eax, 0x1 ; Perform an or on the content
    mov cr0 , eax ; Move back

    jmp CODE_SEG:init_pro_mode


; The order matters this has to be after the 16 bit section
%include "gdt.asm"

bits 32
init_pro_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; Update stack position so that its at the top of the free space
    mov esp , ebp

    jmp $



times 510-($-$$) db 0 ; Padding

dw 0xaa55 ; Magic number