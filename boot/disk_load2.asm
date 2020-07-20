disk_load:
  mov  [SECTORS], dh
  mov  ch, 0x00      ;C=0
  mov  dh, 0x00      ;H=0
  mov  cl, 0x02      ;S=2
 next_group:
  mov  di, 5         ;Max 5 tries
 again: 
  mov  ah, 0x02      ;Read sectors
  mov  al, [SECTORS]
  int  0x13
  jc   maybe_retry
  sub  [SECTORS], al ;Remaining sectors
  jz  ready
  mov  cl, 0x01      ;Always sector 1
  xor  dh, 1         ;Next head on diskette!
  jnz  next_group
  inc  ch            ;Next cylinder
  jmp  next_group
 maybe_retry:
  mov  ah, 0x00      ;Reset diskdrive
  int  0x13
  dec  di
  jnz  again
  jmp  disk_error
 ready:
  ret

disk_error:
  mov  si, DISK_ERROR_MSG 
  call print_string 
  jmp  $

DISK_ERROR_MSG db "Disk read error!", 0
SECTORS db 0
