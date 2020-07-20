#include "../drivers/screen.h"
#include "../interrupts/idt.c"
#include "../interrupts/types.h"
void main() {
    /* Test the interrupts */
	init_idt();

    __asm__ __volatile__("int $0x10");
}
