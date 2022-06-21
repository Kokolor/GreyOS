#include <stddef.h>
#include <stdint.h>
#include <Include/Cpu/Gdt/Gdt.h>
#include <Include/Framebuffer/Framebuffer.h>
// #include <Include/Cpu/Interrupts/Interrupts.h>

void KernelStart(multiboot_info_t* MBootInfo){
    MBInfo = MBootInfo;
    Clear(0x00222222);
    InitGdt();
    while(1);    
}

