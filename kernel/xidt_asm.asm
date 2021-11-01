bits 32

; Reasoning behind the need for global
;https://stackoverflow.com/questions/17898989/what-is-global-start-in-assembly-language

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; Each "section" pushes the interrupt number and the error code onto the stack

isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_handler

isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_handler

isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_handler

isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_handler

isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_handler

isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_handler

isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_handler

isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_handler

isr8:
    cli
    push byte 0
    push byte 8
    jmp isr_common_handler

isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_handler

isr10:
    cli
    push byte 0
    push byte 10
    jmp isr_common_handler

isr11:
    cli
    push byte 0
    push byte 11
    jmp isr_common_handler

isr12:
    cli
    ; No need to push anything its provided by the CPU
    push byte 12
    jmp isr_common_handler


isr13:
    cli
    push byte 0
    push byte 13
    jmp isr_common_handler


isr14:
    cli
    push byte 0
    push byte 14
    jmp isr_common_handler


isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_handler


isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_handler

isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_handler

isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_handler

isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_handler

isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_handler

isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_handler

isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_handler

isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_handler

isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_handler

isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_handler

isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_handler

isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_handler

isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_handler

isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_handler

isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_handler

isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_handler




extern isr_handler

; ------------------------------- ;
; Common error handler for Interrupt Service Routines
; A function in C will be defined to handle each case (reword if necessary)
; ------------------------------- ;
isr_common_handler:
    pusha

    mov ax, ds
    push eax

    ; use kernel data segment
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp ; Push stack

    call isr_handler ; Call to high level C handler

    pop eax ; Pop stack pointer

    ; restore original segment pointers segment
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa ; Restore the registers

    add esp, 8 ; Remove error code and interrupt number from the stack

    iret ; Special return method for interrupt handling








