#ifndef __GDT_H
#define __GDT_H

#include "basic_types.h"


struct SEGMENT_DESCRIPTOR {
	uint16_t limit_lo;
	uint16_t base_lo;

	uint8_t base_hi;
	uint8_t type;
	uint8_t limit_hi;
	uint8_t base_vhi;
} __attribute__((packed));


struct GDT_PTR { 
    uint8_t limit; 
    uint32_t base; 
} __attribute__((packed)); 


void gdt_flush();


void gdt_set_gate(
	int num, 
	uint32_t base,
	uint32_t limit,
	uint8_t access,
	uint8_t gran);


void load_gdt();


#endif
