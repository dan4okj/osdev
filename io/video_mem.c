#include "basic_types.h"
#include "video_mem.h"


// Characters in video memory
static uint16_t* VM = (uint16_t*) V_M_BASE_ADDR;

// Horizontal and vertical positions of cursor
static uint8_t x = 0;
static uint8_t y = 0;


// Moves cursor to next line
void new_line() 
{
	x = 0;
	y++;
}


// Moves cursor along x
void next_col() 
{
	x++;
}


// Sets the cursor at position (0, 0)
void reset_cursor() 
{
	y = 0;
	x = 0;
}


// Puts a character in video memory
void put_char(uint8_t x_pos, uint8_t y_pos, uint16_t color, char ch) 
{
	VM[V_M_SCREEN_WIDTH*y+x] = (VM[V_M_SCREEN_WIDTH*y+x] & color) | ch;
}


void clear_vm() 
{
	for (int32_t clear_y = 0; y < V_M_SCREEN_LENGTH; y++)
		for (int32_t clear_x = 0; x < V_M_SCREEN_WIDTH; x++)
			put_char(clear_x, clear_y, V_M_WHITE, ' ');
}


//Puts characters in video memory, along with a color
void printf(char* str) 
{

	for (int32_t i = 0; str[i] != '\0'; ++i) 
	{	
		if (str[i] == '\n') 
		{
			new_line();
		} 
		else 
		{
			put_char(x, y, V_M_WHITE, str[i]);
			x++; 
		}

		if (x >= V_M_SCREEN_WIDTH) {
			new_line();
		}

		if (y >= V_M_SCREEN_LENGTH) {
			clear_vm();
			reset_cursor();
		}

	}
}

