bits    32
section .text
   align 4
   
   dd 0x1BADB002
   dd 0x04
   dd -(0x1BADB002 + 0x04)
   
   dd 0
   dd 0
   dd 0
   dd 0
   dd 0
   
   dd 0
   dd 1024
   dd 768
   dd 32
       
global start
extern KernelStart
start:
    mov esp, stack.end
    push ebx
    call KernelStart
    pop ebx

    hlt

stack: resb 4096
.end: