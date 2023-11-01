#include "gdt.h"
#include <stddef.h>
#include "stdio.h"

struct gdt_entry gdt[3];
struct gdt_descriptor gdt_d;

extern void load_gdt(void);

bool init_gdt(void) {
	gdt_d.size = sizeof(gdt) - 1;
	gdt_d.offset = (uint64_t) &gdt;

	// null segment
	set_gdt_entry(0, 0, 0, 0, 0);

	// code segment
	set_gdt_entry(1, 0x0, 0xFFFFF, 0x9A, 0xA);

	// data segment
	set_gdt_entry(2, 0x0, 0xFFFFF, 0x92, 0xC);

	// task state segment
	// TODO: implement

	load_gdt();
	return true;
}

void set_gdt_entry(size_t idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	if(limit > 0xFFFFF) {
		kprint("Cannot set a limit greater than 0xFFFFF!");
		return;
	}

	gdt[idx].base_low = (base & 0xFFFF);
	gdt[idx].base_mid = ((base >> 16) & 0xFF);
	gdt[idx].base_high = (uint8_t) ((base >> 24) & 0xFF);

	gdt[idx].limit_low = (limit & 0xFFFF);
	gdt[idx].limit_flags_mid = ((limit >> 16) & 0xF);

	gdt[idx].access = access;
	gdt[idx].limit_flags_mid |= ((flags & 0xF) << 4);
}
