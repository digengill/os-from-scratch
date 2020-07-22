#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"

isr_t interrupt_handlers[256];

void isr_handler(registers_t regs)
{
	char *exception_messages[] = {
    "Division By Zero",
    "Single-step interrupt",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid Task State Segment",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "Math Fault",
    "Alignment Check",
    "Machine Check",
    "Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};
	print(exception_messages[regs.int_no]);
	print("\n");
}

void irq_handler(registers_t regs)
{
	// Send an EOI (end of interrupt) signal to the PICs.
   	// If this interrupt involved the slave.
   	if (regs.int_no >= 40)
   	{
       		// Send reset signal to slave.
       		port_byte_out(0xA0, 0x20);
   	}
   	// Send reset signal to master. (As well as slave, if necessary).
   	port_byte_out(0x20, 0x20);

   	if (interrupt_handlers[regs.int_no] != 0)
   	{
       		isr_t handler = interrupt_handlers[regs.int_no];
       		handler(regs);
   	}

}

void register_interrupt_handler(u8 n, isr_t handler)
{
	char str[100];
	interrupt_handlers[n] = handler;
	print(itoa(n,str,10));
}
