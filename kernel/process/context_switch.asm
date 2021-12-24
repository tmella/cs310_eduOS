
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

; This Assembly routine takes care of the following:
;       - Save the current process
;       - Update the current process to the value passed as a param
;       - Restore state
context_switch:
        ; Save the registers we plan to modify in this section
        push  ebx
        push  esi
        push  edi
        push  ebp

        ; Delegate the saving of the current process to a C routing
        ; It will be easier to define later on when we want multiple registers to be restored
        push esp
        call save_current_process
        add esp, 4 ; Remove from the stack the value with passed

        ; We expect the value passed as a param to this method
        mov esi, [esp+((4+1)*4)]
        mov [current], esi

        ; Add the top of stack value and cr3 value from PCB struct
        mov esp,[esi+ESP_OFFSET]
        mov eax,[esi+PD_OFFSET]

        ; Checks if the CR3 (page directory addr) needs to be refreshed
        ; it avoids unnecessary cache flushes
        mov ecx,cr3
        cmp ecx,eax
        jmp .sameVAS
        mov cr3, eax

.sameVAS:
        ; Restore the state
        pop  ebx
        pop  esi
        pop  edi
        pop  ebp

        ret