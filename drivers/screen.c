#include "screen.h"
#include "../kernel/ports.h"
void print_char ( char character , int col , int row , char attribute_byte );
int get_cursor();
void set_cursor(int offset);
int get_screen_offset(int col,int row);
void print_at ( char * message , int col , int row ) {
// Update the cursor if col and row not negative .
	if ( col >= 0 && row >= 0) 
	{
	set_cursor ( get_screen_offset ( col , row ));
	}
	// Loop through each char of the message and print it .
	int i = 0;
	while ( message [ i ] != 0) 
	{
		print_char ( message [ i++] , col , row , WHITE_ON_BLACK);
		col++;
	}
}
void print( char *message)
{
	print_at(message, -1, -1);
}

void clear_screen()
{
	for (int i = 0 ; i < MAX_ROWS; i++)
	{
		for (int j = 0; j< MAX_COLS; j++)
		{
			print_char(' ', j, i, WHITE_ON_BLACK);
		}

	}

	set_cursor(get_screen_offset(0,0));
}

void print_char ( char character , int col , int row , char attribute_byte ) {
	/* Create a byte ( char ) pointer to the start of video memory */
	unsigned char * vidmem = ( unsigned char *) VIDEO_ADDRESS ;
	/* If attribute byte is zero , assume the default style . */
	if (!attribute_byte ) {
		attribute_byte = WHITE_ON_BLACK ;
	}
	/* Get the video memory offset for the screen location */
	int offset ;
	/* If col and row are non - negative , use them for offset . */
	if ( col >= 0 && row >= 0) {
		offset = get_screen_offset( col , row );
	/* Otherwise , use the current cursor position . */
	} 
	else {
		offset = get_cursor ();
	}
	if ( character == '\n') {
		int rows = offset / (2* MAX_COLS );
		offset = get_screen_offset(79 , rows );
	// Otherwise , write the character and its attribute byte to
	// video memory at our calculated offset .
	} else {
		vidmem [offset] = character ;
		vidmem [offset +1] = attribute_byte ;
	}
	// Update the offset to the next character cell , which is
	// two bytes ahead of the current cell .
	offset += 2;
	// Make scrolling adjustment , for when we reach the bottom
	// of the screen .
	offset = handle_scrolling(offset);
	// Update the cursor position on the screen device .
	set_cursor ( offset );

}

int get_cursor()
{
	port_byte_out( REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out( REG_SCREEN_CTRL , 15);
	offset += port_byte_in(REG_SCREEN_DATA);

	return offset*2;

}

void set_cursor(int offset)
{
	offset /= 2;
	port_byte_out ( REG_SCREEN_CTRL , 14);
	port_byte_out ( REG_SCREEN_DATA , ( unsigned char )( offset >> 8));
	port_byte_out ( REG_SCREEN_CTRL , 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}
int get_screen_offset(int col,int row)
{
	return ((row*80)+ col) *2;

}

int handle_scrolling(int cursor_offset)
{
	// if cursor is still within screen, return normally.
	if (cursor_offset < MAX_ROWS*MAX_COLS*2)
	{
		return cursor_offset;
	}
	// Shift each row 1 row up.	
	for (int i = 1 ; i < MAX_ROWS; i++)
	{
		memory_copy(get_screen_offset(0,i) + VIDEO_ADDRESS, get_screen_offset(0,i-1)+VIDEO_ADDRESS, MAX_COLS*2);
	
	}

	char * last_line = get_screen_offset(0 , MAX_ROWS -1) + VIDEO_ADDRESS ;
	for (int i =0; i < MAX_COLS *2; i ++) {
		last_line [ i ] = 0;
	}
	cursor_offset -= 2* MAX_COLS ;
	return cursor_offset;
}
