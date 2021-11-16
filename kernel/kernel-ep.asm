global _start

bits 32

; Start in not strictly needed but the linker will complain if missing
_start:
    [extern main]
    call main

    jmp $