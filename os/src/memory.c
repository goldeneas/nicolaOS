#include "memory.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define NULL_BLOCK 0x0
#define MEM_BASE 0x1000
#define MEM_LIMIT 0xFFFFF

uint64_t youngest_block = NULL_BLOCK;
uint64_t free_section = MEM_BASE;

static unsigned char get_descriptor_state(uint64_t src) {
	unsigned char* srcp = (unsigned char*) src;
	return srcp[0];
}

static void set_block_descriptor(uint64_t dest, struct block_descriptor bds) {
	unsigned char* destp = (unsigned char*) dest;
	destp[0] = bds.state;

	destp[1] = bds.a;
	destp[2] = bds.b;
	destp[3] = bds.c;
	destp[4] = bds.d;

	destp[5] = bds.e;
	destp[6] = bds.f;
	destp[7] = bds.g;
	destp[8] = bds.h;
}

static struct block_descriptor make_block_descriptor(unsigned char state, uint64_t next_block) {
	struct block_descriptor bds;
	bds.state = (uint8_t) state;
	
	bds.a = (uint8_t)(next_block & 0xFF);
	bds.b = (uint8_t)((next_block >> 8) & 0xFF);
	bds.c = (uint8_t)((next_block >> 16) & 0xFF);
	bds.d = (uint8_t)((next_block >> 24) & 0xFF);

	bds.e = (uint8_t)((next_block >> 32) & 0xFF);
	bds.f = (uint8_t)((next_block >> 40) & 0xFF);
	bds.g = (uint8_t)((next_block >> 48) & 0xFF);
	bds.h = (uint8_t)((next_block >> 56) & 0xFF);

	return bds;
}

uint64_t kmalloc(size_t size) {
	uint64_t current_block_begin = free_section;

	// we set next block to 0x0 because we're at the last current allocated block;
	// we'll have to set this property once a new block is allocated
	// TODO: maybe make this a null ptr instead, till it's changed
	struct block_descriptor current_descriptor = make_block_descriptor('U', NULL_BLOCK);
	kprinti(current_descriptor.state);
	kprint("\n");
	kprinti(current_descriptor.a);
	set_block_descriptor(current_block_begin, current_descriptor);

	// set previous block "next-address"
	if(youngest_block != NULL_BLOCK) {
		unsigned char previous_state = get_descriptor_state(youngest_block);
		struct block_descriptor previous_descriptor = make_block_descriptor(previous_state, current_block_begin);
		set_block_descriptor(youngest_block, previous_descriptor);
	}

	uint64_t usable_memory = current_block_begin + sizeof(struct block_descriptor);
	free_section = usable_memory + size;
	youngest_block = current_block_begin;

	if(free_section >= (MEM_BASE + MEM_LIMIT))
		kpanic("Exceeded maximum heap memory!");

	return usable_memory;
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

bool init_mem(void) {
	memset((void*) MEM_BASE, 0, MEM_LIMIT);
	return true;
}
