/*
 * My operating system - C kernel
 *
 */

#include "basic_types.h"
#include "video_mem.h"
#include "gdt.h"


void kernel_main(void* multiboot_struct, uint32_t magic_num)
{
	load_gdt();
	printf("GDT Table is loaded \n");

	printf("Hello, my awesome operating system!!");

	while(1);
}
