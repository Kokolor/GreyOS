
#include <stddef.h>
#include <stdint.h>

extern void *memcpy(char *dst, char *src, int n);
#define cli asm("cli"::)

#define sti asm("sti"::)

#define outbp(port,value) \
        asm volatile ("outb %%al, %%dx; jmp 1f; 1:" :: "d" (port), "a" (value));

extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);
extern uint32_t ind(uint16_t port);
extern void outb(uint16_t port, uint8_t data);
extern void outw(uint16_t port, uint16_t data);
extern void outd(uint16_t port, uint32_t data);
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t data);
extern size_t strlen(const char* str);
extern uint16_t inw (uint16_t port);
extern void append(char s[], char n);