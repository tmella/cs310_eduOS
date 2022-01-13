; ------------------------------------------------ ;
;        Definition for the GDT Table
; ----------------------------------------------- ;

global gdt_start

gdt_start:

gdt_null:
    dd 0x0 ;’dd’ means define double word (i.e. 4 bytes)
    dd 0x0

ring1_code:
    dw 0xffff ; Limit
    dw 0x0 ; Base
    db 0x0 ; Base (0-23 bits)
    db 10011010b ; Type flags
    db 11001111b ; Type flags
    db 0x0 ; Base

ring1_data:
    dw 0xffff ; Limit
    dw 0x0 ; Base
    db 0x0 ; Base (0-23 bits)
    db 10010010b ; Type flags
    db 11001111b ; Type flags
    db 0x0 ; Base

ring3_code:
    dw 0xffff ; Limit
    dw 0x0 ; Base
    db 0x0 ; Base (0-23 bits)
    db 11111010b ; Type flags
    db 11001111b ; Type flags
    db 0x0 ; Base

ring3_data:
    dw 0xffff ; Limit           ; 16
    dw 0x0 ; Base               ; 16
    db 0x0 ; Base (0-23 bits)   ; 1
    db 11110010b ; Type flags   ; 1
    db 11001111b ; Type flags   ; 1
    db 0x0 ; Base               ; 1

tss:
    dw 0x68 ; Limit (sizeof tss)
    dw 0x0 ; Base
    db 0x0 ; Base (0-23 bits)
    db 10001001b ; Type flags
    db 11001111b ; Type flags
    db 0x0 ; Base

gdt_end:
   ; Needed to calculate the size
   ; We dont actually need to write anything


gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size of the table
    dd gdt_start                ; Start position

CODE_SEG equ ring1_code - gdt_start
DATA_SEG equ ring1_data - gdt_start