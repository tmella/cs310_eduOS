
bits 32

; TODO: practically the same as the idt common handler so maybe add util files

[extern irq_handler]

irq_common_handler:
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

    call irq_handler ; Call to high level C handler

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

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
    cli
    push byte 0
    push byte 32
    jmp irq_common_handler

irq1:
    cli
    push byte 0
    push byte 33
    jmp irq_common_handler

irq2:
    cli
    push byte 0
    push byte 34
    jmp irq_common_handler

irq3:
    cli
    push byte 0
    push byte 35
    jmp irq_common_handler

irq4:
    cli
    push byte 0
    push byte 36
    jmp irq_common_handler

irq5:
    cli
    push byte 0
    push byte 37
    jmp irq_common_handler

irq6:
    cli
    push byte 0
    push byte 38
    jmp irq_common_handler

irq7:
    cli
    push byte 0
    push byte 39
    jmp irq_common_handler

irq8:
    cli
    push byte 0
    push byte 40
    jmp irq_common_handler

irq9:
    cli
    push byte 0
    push byte 41
    jmp irq_common_handler

irq10:
    cli
    push byte 0
    push byte 42
    jmp irq_common_handler

irq11:
    cli
    push byte 0
    push byte 43
    jmp irq_common_handler

irq12:
    cli
    ; No need to push anything its provided by the CPU
    push byte 44
    jmp irq_common_handler


irq13:
    cli
    push byte 0
    push byte 45
    jmp irq_common_handler


irq14:
    cli
    push byte 0
    push byte 46
    jmp irq_common_handler


irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_handler

