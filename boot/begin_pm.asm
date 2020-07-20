[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000


xor ax, ax
mov ds, ax
mov es, ax

mov [BOOT_DRIVE], dl

mov ax, 0x07E0
cli
mov ss, ax
mov sp, 0x1200
sti


mov bx, MSG_REAL_MODE
call print_string

call load_kernel

call switch_to_pm

jmp $

%include "print_string.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "print_string_32.asm"
%include "switch_to_pm.asm"

[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print_string

	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]

BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	call KERNEL_OFFSET
	jmp $

BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Switched to 32-bit Protected mode", 0
MSG_LOAD_KERNEL db "Loading Kernel."

times 510-($-$$) db 0
dw 0xaa55
