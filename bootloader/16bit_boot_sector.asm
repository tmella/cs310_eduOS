; Basic Bootloader

; Indicates that we are running in 16-bit mode
bits 16

org 0x7c00 ; Tells NASM that are program is loaded at 0x7c00

; Infinate loop to avoid reading any other instruction in memory
jmp $

;; Pads the rest of the file with 0 so that he can find the magic number
;; $ is the address at which the current instruction will be assembled
;; $$: is the start
times 510 - ($ - $$) db 0

; Write the magic number at the end
dw 0xaa55