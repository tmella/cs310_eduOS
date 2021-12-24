
; We want this method to visible outside this file
global context_switch

; Current PCB defined in kernel/process/
extern current
extern save_current_process

; Offset from the process_control_block struct
; The value can be retrieved by calling offsetof(type, member);
;; ONLY CHANGE IF THE STRUCT CHANGES "kernel/process/process.h"
ESP_OFFSET equ 0
PD_OFFSET equ 4


context_switch:
        push  ebx
        push  esi
        push  edi
        push  ebp

        push esp
        call save_current_process
        add esp, 4

        mov esi, [esp+((4+1)*4)]
        mov [current], esi

        mov esp,[esi+ESP_OFFSET]
        mov eax,[esi+PD_OFFSET]

        mov ecx,cr3

        cmp ecx,eax
        jmp .sameVAS
        mov cr3, eax

.sameVAS:
        pop  ebx
        pop  esi
        pop  edi
        pop  ebp

        ret