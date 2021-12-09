global _start

bits 32

_start:
    [extern main]
    call main

    jmp $