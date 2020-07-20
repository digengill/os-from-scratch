#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
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



