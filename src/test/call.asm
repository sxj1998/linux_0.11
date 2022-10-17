[bits 32]

extern exit

global main
main:
    push 5
    push 10

    pop ebx
    pop ecx
    