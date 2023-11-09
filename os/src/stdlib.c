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
uint64_t last_block_beginning = 0x0;
uint64_t free_section_beginning = MEM_BASE;

bool init_mem(void) {
	memset((void*) MEM_BASE, 0, MEM_LIMIT);
	return true;
}

/*
 *
 *	MEMORY BLOCKS LAYOUT
 *	BYTE N.			VALUE
 *	0				U/F -> U = MEMORY IN USE; F = BLOCK HAS BEEN FREED
 *
 *
 */

uint64_t kmalloc(size_t size) {
	uint64_t block_beginning = free_section_beginning;
	unsigned char* p = (unsigned char*) block_beginning;

	// this is the offset from the block's beginning to
	// the memory that can actually be used by the user
	uint16_t offset = 9;

	// set the block's state
	p[0] = 'U';

	if(last_block_beginning != 0x0) {
		p[1] = (uint8_t)(last_block_beginning & 0xFF);
		p[2] = (uint8_t)((last_block_beginning >> 8) & 0xFF);
		p[3] = (uint8_t)((last_block_beginning >> 16) & 0xFF);
		p[4] = (uint8_t)((last_block_beginning >> 24) & 0xFF);

		p[5] = (uint8_t)((last_block_beginning >> 32) & 0xFF);
		p[6] = (uint8_t)((last_block_beginning >> 40) & 0xFF);
		p[7] = (uint8_t)((last_block_beginning >> 48) & 0xFF);
		p[8] = (uint8_t)((last_block_beginning >> 56) & 0xFF);
	}

	// we add one because we want to use the first byte to show whether
	// this block is still used or not
	uint64_t usable_memory_beginning = block_beginning + offset;
	free_section_beginning = usable_memory_beginning + size;

	// set the next-block memory address of the previous block
	last_block_beginning = block_beginning;

	if(free_section_beginning >= (MEM_BASE + MEM_LIMIT))
		kpanic("Exceeded maximum heap memory!");

	return usable_memory_beginning;
}

void kfree(uint64_t base) {
	if(base < MEM_BASE || base > (MEM_BASE + MEM_LIMIT)) {
		kprint("Tried freeing an address out of bounds!");
		return;
	}

	// we subtract one because we want to modify the byte that's before the
	// address that the user will tell us
	unsigned char* p = (unsigned char*) (base - 1);
	p[0] = 'F';
}
