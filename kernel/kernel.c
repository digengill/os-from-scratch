#include "../drivers/screen.h"
#include "../interrupts/idt.c"
#include "../interrupts/types.h"
#include "../interrupts/timer.h"
#include "../drivers/keyboard.h"
#include "helper.h"
#include "../interrupts/types.h"
void main() {
    /* Test the interrupts */
	init_idt();
	asm volatile("sti");
//	init_timer(50);
	init_keyboard();
//	print(itoa(30, str,16));
//	initialise_paging();
 //   	u32 *ptr = (u32*)0xA000000;
//	u32 do_page_fault = *ptr;
	//	__asm__ __volatile__("int $0x07");
}
