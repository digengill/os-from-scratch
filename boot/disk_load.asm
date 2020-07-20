disk_load:
	push dx
	
	mov ah, 0x02
	mov al, dh
	mov ch, 0x00
	mov dh, 0x00
	mov cl, 0x02

	int 0x13
	jc disk_error1

	pop dx
	cmp dh, al
	jne disk_error2
	ret
disk_error1:
	mov bx, disk_error_msg1
	call print_string
	jmp $
disk_error2:
	mov bx, disk_error_msg2
	call print_string
	jmp $
disk_error_msg1 db "Disk read error! (err1)", 0
disk_error_msg2 db "Disk read error! (err2)", 0
