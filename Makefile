SRCS := $(shell find Source/ -name '*.c') 
OBJS := $(SRCS:.c=.o)

.SUFFIXE: .c
%.o: %.c
	i686-elf-gcc -ISource -ffreestanding -g -c $< -o $@

Kernel.elf: $(OBJS)
	make asm
	i686-elf-gcc -std=gnu99 -ffreestanding -nostdlib -T Source/Linker.ld $(OBJS) Boot.o -o $@ -lgcc

Kernel.bin: $(OBJS)
	make asm
	i686-elf-gcc -std=gnu99 -ffreestanding -nostdlib -T Source/Linker.ld $(OBJS) Boot.o Interrupts.o -o $@ -lgcc

clean:
	rm -f $(OBJS)
	rm -f Root/boot/Kernel.elf
	rm -f *.o
	rm -f *.elf
	rm -f *.iso

iso:
	cp Kernel.elf Root/boot/
	grub2-mkrescue Root -o Colored.iso

asm:
	# i686-elf-gcc -std=gnu99 -ffreestanding -g -c Source/Boot/Boot.s -o Boot.o
	nasm -f elf Source/Boot/Boot.asm -o Boot.o
	# nasm -f elf Source/Include/Cpu/Interrupts/Interrupts.asm -o Interrupts.o

run: $(KERNEL_DISK)
	make iso
	qemu-system-i386 -m 256M -enable-kvm -cdrom ./Colored.iso

debug:
	qemu-system-i386 -cdrom Colored.iso -s -S &
	gdb
	target remote localhost:1234
	symbol-file Kernel.elf

bochs:
	bochs