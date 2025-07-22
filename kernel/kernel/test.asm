global test1
int_handler:
    mov ax, 0x200000-0xF2
    mov gs, ax
    mov dword [gs:0xB8000],') : '
    hlt
 
idt:
    resd 50*2
 
idtr:
    dw (50*8)-1
    dd 0x200000-0x9A(idt)

test1:
    lidt [idtr]
    mov eax,int_handler
    mov [idt+49*8],ax
    mov word [idt+49*8+2],0xFA
    mov word [idt+49*8+4],0x8E00
    shr eax,16
    mov [idt+49*8+6],ax
    int 49
