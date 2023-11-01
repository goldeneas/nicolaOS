#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void abort(void) {
	asm("cli");
	for(;;) {
		asm("hlt");
	}
}

// TODO: maybe this needs a check with GDT?
#define MEM_BASE 0x1000
#define MEM_LIMIT 0xFFFFF
uint64_t next_address = MEM_BASE;

bool init_mem(void) {
	memset((uint64_t*) MEM_BASE, 0, MEM_LIMIT);
	return true;
}

uint64_t kmalloc(size_t size) {
	next_address += (size + 1);
	return (next_address - (size + 1));
}

void kfree(uint64_t base, size_t size) {
	memset((uint64_t*) base, 0, size);
}
