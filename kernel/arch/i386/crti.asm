SECTION .init
global _init:function
_init:
    push    ebp
    mov     ebp, esp


SECTION .fini
global _fini:function
_fini:
    push    ebp
    mov     ebp, esp
