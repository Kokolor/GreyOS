#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <Include/Cpu/Idt/Idt.h>

static char key_buffer[256];

void IsrDefault(void)
{
	// PutString("Interrupts enabled", SolarizedBlue);
}

void IsrClock(void)
{
	static int tic = 0;
	static int sec = 0;
	tic++;
	if (tic % 100 == 0) {
		sec++;
		tic = 0;
	}
}

void IsrKeyboard(void){
	uint8_t scancode = inb(0x60);
    if (scancode > SC_MAX) return;

     /*if (scancode == BACKSPACE) {
        BackSpace();
    } */if (scancode == ENTER) {
        ExecuteCommand(key_buffer);
        key_buffer[0] = '\0';
		PutRect(16, 752, 1000, 16, DarkGrey);
		KeyboardX = 16;
    } else {
        char letter = kbdmap[(int) scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
		PutChar(letter, KeyboardX, KeyboardY, White);
		KeyboardX++;
		KeyboardX++;
		KeyboardX++;
		KeyboardX++;
		KeyboardX++;
		KeyboardX++;
		KeyboardX++;
		KeyboardX++;
    }


}

void Shell(){
	KeyboardX = 16;
	KeyboardY = 752;
	PutChar('$', 0, 752, White);
}

int CompareString(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

void ExecuteCommand(char *input) {
    if (CompareString(input, "shutdown") == 0) {
        PutString("\nStopping the CPU. Bye!", Blue);
        asm volatile("cli");
		outw(0xB004, 0x2000);
		outw(0x604, 0x2000);
		outw(0x4004, 0x3400);
		asm volatile("hlt");
    }

	else if (CompareString(input, "help") == 0) {
		SelectedFont = font;
		PutString("config	//help config for mor informations\n", LightBlue);
		PutString("clear	// clear screen\n", LightBlue);
		Shell();
		// PutString("$ ", White);
		// KeyboardX = 16;
		// KeyboardY = 752;
    }
	// Config
	else if (CompareString(input, "help config") == 0) {
		SelectedFont = font;
		PutString("config:\n", LightBlue);
		PutString("		font: normal/bold		//Exemple: config font normal\n", LightBlue);
		Shell();
		// PutString("$ ", White);
		// KeyboardX = 16;
		// KeyboardY = 752;
    }

	else if (CompareString(input, "config font normal") == 0) {
		SelectedFont = font;
		Clear(0x00222222);
		PutString("Font changed!\n", LightBlue);
		Shell();
		// PutString("$ ", White);
		// KeyboardX = 16;
		// KeyboardY = 752;
    }
	else if (CompareString(input, "config font bold") == 0) {
		SelectedFont = font2;
		Clear(0x00222222);
		PutString("Font changed!\n", LightBlue);
		Shell();
		// PutString("$ ", White);
		
    }
	else if (CompareString(input, "clear") == 0) {
		Clear(0x00222222);
		Shell();
		
    }
	else{
		PutString("Unknow command\n", Red);
		Shell();
	}
}