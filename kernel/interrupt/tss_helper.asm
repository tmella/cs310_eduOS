bits 32

global flush_tss
flush_tss:
	mov ax, 0x28 ; Sixth element of GDT
	ltr ax
	ret