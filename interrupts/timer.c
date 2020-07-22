#include "timer.h"
#include "isr.h"
#include "../drivers/screen.h"
#include "../kernel/helper.h"
u32 tick = 0;

static void timer_callback(registers_t regs)
{
	char str[10];
	tick++;
	print("Tick:");
	print(itoa(tick,str,10));
	print("\n");
}

void init_timer(u32 frequency)
{
	register_interrupt_handler(IRQ0, timer_callback);

	u32 divisor = 1193180 / frequency;

	u8 l = (u8) (divisor & 0xFF);
	u8 h = (u8) ((divisor >> 8) & 0xFF);

	port_byte_out(0x43, 0x36);
	port_byte_out(0x40, l);
	port_byte_out(0x40, h);

}
