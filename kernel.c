/*
 * My operating system - C kernel
 *
 */

#include "lib/basic_types.h"
#include "lib/video_mem.h"
#include "lib/gdt.h"


void kernel_main(void* multiboot_struct, uint32_t magic_num)
{
	load_gdt();
	printf("GDT Table is loaded \n");

	printf("Hello, my awesome operating system!!");

	while(1);
}
