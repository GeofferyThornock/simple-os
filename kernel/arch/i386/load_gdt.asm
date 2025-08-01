global load_gdt

load_gdt:
    MOV     EAX, [ESP + 4]  ; get gdt pointer
    LGDT    [EAX]          ; load gdt

    MOV     AX, 0x10    ; kernel data segment
    MOV     DS, AX
    MOV     ES, AX
    MOV     FS, AX
    MOV     GS, AX
    MOV     SS, AX

    CLI             ; clear interrupts
    MOV     EAX, cr0    ; set bit 0 in cr0 to enter protected mode
    OR      EAX, 1
    MOV	    CR0, EAX

    JMP     0x08:far_jump   ; jump to far with code data segment
far_jump:
    ret


