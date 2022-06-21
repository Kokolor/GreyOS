#include <stddef.h>
#include <stdint.h>
#include <Include/Cpu/Gdt/Gdt.h>
#include <Include/Cpu/Idt/Idt.h>

void KernelStart(multiboot_info_t* MBootInfo){
    MBInfo = MBootInfo;
    Clear(0x00222222);
    KeyboardX = 16;
	KeyboardY = 752;
	PutChar('$', 0, 752, White);
    CursorY = 0;
    InitGdt();
    InitIdt();
    InitPic();
    sti;
    while(1);
}

