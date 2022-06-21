#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <Include/Common/Common.h>

#define GdtBase 0x0
#define GdtSize 0xFF

struct GdtDescriptor{
    uint16_t lim0_15;
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t access;
    uint8_t lim16_19 : 4;
    uint8_t other : 4;
    uint8_t base24_31;
} __attribute__ ((packed));

struct GdtPointer{
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed));

extern void InitGdtDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t other, struct GdtDescriptor*  Descriptor);
extern void InitGdt();

#ifdef __GDT__
	struct GdtDescriptor KernelGdt[GdtSize];
	struct GdtPointer KernelGdtPointer;
#else
	extern struct GdtDescriptor KernelGdt[];
	extern struct GdtPointer KernelGdtPointer;
#endif