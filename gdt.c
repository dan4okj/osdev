/*
 * Global Descriptor Table implementation
 *
 */

#include "lib/gdt.h"


struct SEGMENT_DESCRIPTOR gdt[3];
struct GDT_PTR gp;

extern void gdt_flush();

void gdt_set_gate(
	int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt[num].base_lo = (base & 0xFFFF);
	gdt[num].base_hi = (base >> 16) & 0xFF;
	gdt[num].base_vhi = (base >> 24) & 0xFF;
	gdt[num].limit_lo = (limit & 0xFFFF);
	gdt[num].limit_hi = (limit >> 16) & 0x0F;

	gdt[num].limit_hi |= (gran & 0xF0);
	gdt[num].type = access;
}

void load_gdt()
{
	gp.limit = (sizeof(struct SEGMENT_DESCRIPTOR) * 3) - 1;
	gp.base = &gdt;

	// null descriptor
	gdt_set_gate(0, 0, 0, 0, 0);

	// Code descriptor
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	// Data descriptor
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	gdt_flush();

}
