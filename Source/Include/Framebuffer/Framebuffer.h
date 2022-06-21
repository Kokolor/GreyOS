#include <stddef.h>
#include <stdint.h>
#include <Multiboot/Multiboot.h>
#include <Boot/BootInfo.h>
#include <Include/Common/Common.h>
#include "Font.h"

extern int CursorX;
extern int CursorY;

#define Black      0x00000000 
#define White      0x00FFFFFF 
#define DarkGrey  0x00222222
#define LightGrey 0xC0C0C0
#define Red        0xFF0000 
#define Green      0x008000 
#define LightGreen      0x00FF00
#define Blue       0x0000FF 
#define LightBlue           0x268BD2
#define Yellow     0xFFFF00
#define Purple     0x800080

extern void FramebufferInit();
extern void PutPixel(int X, int Y, unsigned int Color);
extern void Clear(unsigned Color);
extern void PutRect(int X, int Y, int Width, int Height, unsigned int Color);
extern void NewLine();
extern void Shell();
extern void PutChar(char C, int X, int Y, unsigned int Color);
extern void PutString(char *String, unsigned int Color);
extern void BackSpace();