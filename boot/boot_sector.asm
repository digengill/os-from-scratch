[org 0x7c00]			; Telling the assembler where this code is loaded.


mov bx, HELLO_MSG		; moving string into bx
call print_string		; calling print_string

mov bx, GOODBYE_MSG
call print_string

print_string:
	mov ah, 0x0e	
	loop:
		mov al, [bx]	; move value of byte in al
		cmp al, 0	; check for null character terminator
		je exit_loop
		int 0x10
		add bx, 1	; increment to next byte
		jmp loop
	exit_loop:		; return case
		ret

HELLO_MSG:
	db 'Hello, World!', 0

GOODBYE_MSG:
	db 'Goodbye!', 0
jmp $

times 510-($-$$) db 0

dw 0xaa55
