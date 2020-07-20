C_SOURCES = $(wildcard kernel/*.c drivers/*.c interrupts/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h interrupts/*.h)

OBJ = ${C_SOURCES:.c=.o interrupts/interrupt.o}

all: os-image.bin #disk.img

run: all
	qemu-system-i386 -fda os-image.bin
#disk.img: os-image.bin
#	dd if=/dev/zero of=$@ bs=1024
#	dd if=$< of=$@ conv=notrunc

os-image.bin: boot/begin_pm.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld -m elf_i386 -s -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@
	

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -I 'boot/' -o $@
# Clear all generated files
clean:
	rm -fr *.bin boot/*.bin *.dis kernel/*.o interrupts/*.o os-image os-image.bin *.map
# Dissassemble the kernel- for debugging.
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@
