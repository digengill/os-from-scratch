[org 0x7c00]

mov dx, 0x1fb6
call print_hex

%include "print_string.asm"

print_hex:
	popa
	mov bx, HEX_OUT
	mov ax, HEX_OUT+5	
	mov cx, 0
	loop2:
		cmp cx, 16
		je goto_end
		mov bx, dx
		shr bx, cl
		and bx, 0x000f
		add bl, 48
		cmp bl, 57
		jle next_step
		add bl, 7		

		next_step: 
		mov [ax], bl
		sub ax, 1
		add cx, 4
		jmp loop2	

	goto_end:
		pusha
		call print_string
		ret

HEX_OUT: db '0x0000', 0
STRING_1: db 'Hello', 0

jmp $

times 510-($-$$) db 0
; Magic number
dw 0xaa55 
