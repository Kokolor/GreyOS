#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t magic[2];
    uint8_t mode;
    uint8_t height;
} FontHeaderT;

extern uint8_t font[];
extern uint8_t font2[];
extern unsigned char* SelectedFont;