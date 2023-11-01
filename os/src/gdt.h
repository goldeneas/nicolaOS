#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_flags_mid;  // 0000; 0000 -> flags; limit
	uint8_t base_high;
} __attribute__((packed));

struct gdt_descriptor {
	uint16_t size;
	uint64_t offset;
} __attribute__((packed));
bool init_gdt(void);
void set_gdt_entry(size_t idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
