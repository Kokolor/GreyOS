#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Framebuffer.h"

int CursorX;
int CursorY;
int FramebufferX;
int FramebufferY;

void PutPixel(int X, int Y, unsigned int Color){
    unsigned *line = (unsigned *)(MBInfo->framebuffer_addr + Y * MBInfo->framebuffer_pitch);
    line[X] = Color;
}

void Clear(unsigned Color){
    CursorX = 0;
    CursorY = 0;
    for(unsigned Y = 0; Y < MBInfo->framebuffer_height; ++Y)
    {
        for(unsigned X = 0; X < MBInfo->framebuffer_width; ++X)
            PutPixel(X, Y, Color);
    }
}

void PutRect(int X, int Y, int Width, int Height, unsigned int Color){
    int EndX = X + Width;
    int EndY = Y + Height;

    for (int I = X; I < EndX; I++)
    {
        for (int J = Y; J < EndY; J++)
        {
            PutPixel(I, J, Color);
        }
    }
}

void PutChar(char C, int X, int Y, unsigned int Color){
    uint8_t* offset = SelectedFont + sizeof(FontHeaderT) + 16 * C;

    switch (C){
        case '\n':
        {
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorY++;
            CursorX = 0;
            FramebufferY = CursorY;
            FramebufferX = CursorX;
            return;
        }
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            if (offset[i] & (1 << j)) {
                PutPixel(X + 8 - j, Y + i, Color);
            }
        }
    }

    // if (C != '\n')
    // {
    //     CursorX++;
    //     CursorX++;
    //     CursorX++;
    //     CursorX++;
    //     CursorX++;
    //     CursorX++;
    //     CursorX++;
    //     CursorX++;
    //     CursorX = 0;
    // }
}


void PutString(char *String, unsigned int Color){
    FramebufferX = CursorX;
    FramebufferY = CursorY;
    size_t Len = strlen(String);
    for (size_t i = 0; i < Len; i++) {
        PutChar(String[i], FramebufferX + 8 * i, FramebufferY, Color);
    }
}

