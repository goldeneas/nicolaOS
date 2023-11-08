#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void abort(void) {
	asm("cli");
	for(;;) {
		asm("hlt");
	}
}

void kpanic(const char* s) {
	kprint("[PANIC PANIC PANIC] ");
	kprint(s);

	abort();
}

// TODO: maybe this needs a check with GDT?
#define MEM_BASE 0x1000
#define MEM_LIMIT 0xFFFFF
uint64_t current_free_addr = MEM_BASE;

bool init_mem(void) {
	memset((void*) MEM_BASE, 0, MEM_LIMIT);
	return true;
}

uint64_t kmalloc(size_t size) {
	//if(next_address >= (MEM_BASE + MEM_LIMIT))
	//	kpanic("Exceeded maximum heap memory!");
	memset((void*) current_free_addr, 255, 65);

	if(current_free_addr != MEM_BASE) {
		
	}

	return 0;
}

/*
 *
 *	POSSIBLE MEMORY LAYOUT
 *	0 0000000000000000000000000000
 *
 *	bit 0: is used?
 *	bits 1/65: address to next block
 *
 */

void kfree(uint64_t base, size_t size) {
	if(base < MEM_BASE || base > (MEM_BASE + MEM_LIMIT)) {
		kprint("Tried freeing an address out of bounds!");
		return;
	}

	if(size < 7) {
		kprint("Could not free address: size is too small for descriptor");
		return;
	}
	
	// remember: memset sets byte rappresentation of a number
	memset((void*) base, 0, 10);
}
