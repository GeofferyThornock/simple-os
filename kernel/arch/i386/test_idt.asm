int_handler:
    mov ax, 0x08:0x92
    mov gs, ax
    mov dword [gs:0xB8000],') : '
    hlt
 
idt:
    resd 50*2
 
idtr:
    dw (50*8)-1
    dd [esp+4](idt)

[GLOBAL test1]
test1:
    lidt [idtr]
    mov eax,int_handler
    mov [idt+49*8],ax
    mov word [idt+49*8+2],0x08:0x9A
    mov word [idt+49*8+4],0x8E00
    shr eax,16
    mov [idt+49*8+6],ax
    int 49
