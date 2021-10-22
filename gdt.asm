; ------------------------------------------------ ;
;        Definition for the GDT Table
; ----------------------------------------------- ;

gdt_start:

gdt_null:
    dd 0x0 ;’dd’ means define double word (i.e. 4 bytes)
    dd 0x0

gdt_code:
    dw 0xffff ; Limit
    dw 0x0 ; Base
    db 0x0 ; Base (0-23 bits)
    db 10011010b ; Type flags
    db 11001111b ; Type flags
    db 0x0 ; Base

gdt_data:
    dw 0xffff ; Limit
    dw 0x0 ; Base
    dd 0x0 ; Base (0-23 bits)
    db 10010010b ; Type flags
    db 11001111b ; Type flags
    db 0x0 ; Base

gdt_end:
   ; Needed to calculate the size
   ; We dont actually need to write anything


gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size of the table
    dd gdt_start                ; Start position

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start