[bits 32]

extern kernel_init
global _start
_start:
    call kernel_init
    xchg bx,bx
    int 0x80
    jmp $