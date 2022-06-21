extern IsrDefault, IsrClock, IsrKeyboard
global DefaultInt, Irq0, Irq1	


DefaultInt:
	call IsrDefault
	mov al,0x20
	out 0x20,al
	iret

Irq0:
	call IsrClock
	mov al,0x20
	out 0x20,al
	iret

Irq1:
	call IsrKeyboard
	mov al,0x20
	out 0x20,al
    int 50
	iret