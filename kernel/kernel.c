#include "../drivers/screen.h"
#include "../interrupts/idt.c"
#include "../interrupts/types.h"
#include "../interrupts/timer.h"
#include "../drivers/keyboard.h"
#include "helper.h"
void main() {
    /* Test the interrupts */
	init_idt();
	asm volatile("sti");
	//init_timer(50);
	init_keyboard();
	char str[10];
	print("\n");
	print(itoa(100, str,10));
  //  __asm__ __volatile__("int $0x10");
}
