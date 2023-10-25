#pragma once
#include <stddef.h>
#include <stdint.h>

struct idt_gate {
	uint16_t offset_low;
	uint16_t segment_selector;
	uint8_t ist;				// bits 0..2 hold IST, rest is reserved
	uint8_t type_attributes;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t reserved;
} __attribute__ ((packed));

struct idt_descriptor {
	uint16_t size;
	uint64_t offset;
} __attribute__ ((packed));

void init_idt(void);
void set_idt_gate(size_t idx, uint64_t offset, uint16_t segment_selector, uint8_t ist, uint8_t type_attributes); 
