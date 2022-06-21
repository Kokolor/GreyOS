#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#define __GDT__
#include "Gdt.h"

void InitGdtDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t other, struct GdtDescriptor*  Descriptor){
    Descriptor->lim0_15 = (limit & 0xffff);
    Descriptor->base0_15 = (base & 0xffff);
    Descriptor->base16_23 = (base & 0xff0000) >> 16;
    Descriptor->access = access;
    Descriptor->lim16_19 = (limit & 0xf0000) >> 16;
    Descriptor->other = (other & 0xf);
    Descriptor->base24_31 = (base & 0xff000000) >> 24;
    return;
}

void InitGdt(){
    InitGdtDescriptor(0x0, 0x0, 0x0, 0x0, &KernelGdt[0]);
    InitGdtDescriptor(0x0, 0xFFFFF, 0x9B, 0x0D, &KernelGdt[1]);
    InitGdtDescriptor(0x0, 0xFFFFF, 0x93, 0x0D, &KernelGdt[2]);
    InitGdtDescriptor(0x0, 0x0, 0x97, 0x0D, &KernelGdt[3]);

    KernelGdtPointer.limit = GdtSize * 8;
    KernelGdtPointer.base = GdtBase;

    memcpy((char*) KernelGdtPointer.base, (char*) KernelGdt, KernelGdtPointer.limit);

    asm("lgdtl (KernelGdtPointer)");

    asm("   movw $0x10, %ax \n \
        movw %ax, %ds       \n \
        movw %ax, %es       \n \
        movw %ax, %fs       \n \
        movw %ax, %gs       \n \
        ljmp $0x08, $next   \n \
        next:               \n");
}