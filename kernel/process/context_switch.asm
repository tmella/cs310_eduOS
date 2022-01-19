
; We want this method to visible outside this file
global context_switch

; Current PCB defined in kernel/process/
extern current
extern save_current_process
extern set_process_running

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

        ret