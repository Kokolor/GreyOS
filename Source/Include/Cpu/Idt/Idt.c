#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Idt.h"

void DefaultInt(void);

void Isr0(void);
void Irq0(void);
void Irq1(void);

struct IdtPointer KernelIdtPointer;
struct IdtDescriptor KernelIdt[IDTSIZE];


void InitIdtDescriptor(uint16_t select, uint32_t offset, uint16_t type, struct IdtDescriptor *Descriptor)
{
	Descriptor->offset0_15 = (offset & 0xffff);
	Descriptor->select = select;
	Descriptor->type = type;
	Descriptor->offset16_31 = (offset & 0xffff0000) >> 16;
	return;
}


void InitIdt(void){
	int i;


	for (i = 0; i < IDTSIZE; i++) 
		InitIdtDescriptor(0x08, (uint32_t) DefaultInt, INTGATE, &KernelIdt[i]);

	InitIdtDescriptor(0x08, (uint32_t) Irq0, INTGATE, &KernelIdt[32]);
	InitIdtDescriptor(0x08, (uint32_t) Irq1, INTGATE, &KernelIdt[33]);


	KernelIdtPointer.limit = IDTSIZE * 8;
	KernelIdtPointer.base = IDTBASE;


	memcpy((char *) KernelIdtPointer.base, (char *) KernelIdt, KernelIdtPointer.limit);


	asm("lidtl (KernelIdtPointer)");
}

void InitPic(void){
	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	outb(0x21, 0x20);
	outb(0xA1, 0x70);

	outb(0x21, 0x04);
	outb(0xA1, 0x02);

	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

int KeyboardX = 0;
int KeyboardY = 0;

const char kbdmap[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};





