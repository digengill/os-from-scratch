print_string:
	pusha
	mov ah, 0x0e
	loop:
		mov al, [bx]
		cmp al, 0
		je null_found
		int 0x10
		add bx, 1
		jmp loop
	null_found:
		popa
		ret
