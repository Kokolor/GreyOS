#include <stddef.h>
#include <stdint.h>
#include "Common.h"

void delay(int x){
    int i = 10000;
    while (--i)
    {
        int j = 10 * x;
        while (--j);
    }
}

void *memcpy(char *dst, char *src, int n){
	char *p = dst;
	while (n--)
		*dst++ = *src++;
	return p;
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm("inb %%dx, %%al" : "=a"(ret) : "d"(port));
    return ret;
}

uint16_t inw(uint16_t port) {
    uint16_t ret;
    asm("inw %%dx, %%ax" : "=a"(ret) : "d"(port));
    return ret;
}

uint32_t ind(uint16_t port) {
    uint32_t ret;
    asm("inl %%dx, %%eax" : "=a"(ret) : "d"(port));
    return ret;
}

void outb(uint16_t port, uint8_t data) {
    asm("outb %%al, %%dx" : : "a"(data), "d"(port));
}

void outw(uint16_t port, uint16_t data) {
    asm("outw %%ax, %%dx" : : "a"(data), "d"(port));
}

void outd(uint16_t port, uint32_t data) {
    asm("outl %%eax, %%dx" : : "a"(data), "d"(port));
}


size_t strlen(const char* str){
    size_t len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

void append(char s[], char n){
    int len = strlen(s);
    s[len] = n;
    s[len + 1] = '\0';
}