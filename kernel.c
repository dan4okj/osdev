/*
 * My operating system - C kernel
 *
 * Last Modified 11/06/2017
 */

#include "lib/basic_types.h"
#include "lib/gdt.h"


// Start address of video memory in RAM
#define V_M_A 0xb8000;

#define V_M_A_WHITE 0xFF00

//Puts characters in video memory, along with a color
void printf(char* str) {
	uint16_t* vma = (uint16_t*) V_M_A;
	
	for (int i = 0; str[i] != '\0'; ++i) 
		vma[i] = (vma[i] & V_M_A_WHITE) | str[i];
}

void kernel_main(void* multiboot_struct, uint32_t magic_num) {
	load_gdt();
	printf("Hello, my awesome operating system!! GDT Table is loaded");


	while(1);
}

