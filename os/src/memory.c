#include "memory.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/*
 *	BASE BLOCK ADDRESS = beginning of a block INCLUDING its block descriptor
 *	USABLE MEMORY ADDRESS = beginning of a block EXCLUDING its block descriptor
 */

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

void* kmalloc(size_t size) {
	uint64_t current_block_begin = free_section;

	// when calling make_block_descriptor on a new block, we pass a NULL_BLOCK as a next_block parameter.
	// this is because we don't know if there will ever be a new block of memory, since we assume that
	// the one we're creating is the youngest one.
	// this means that when creating e.g. block C, we have to change the next_address for block B
	// to be block C's base block address.
	struct block_descriptor current_descriptor = make_block_descriptor('U', NULL_BLOCK);
	set_block_descriptor(current_block_begin, current_descriptor);

	// here we set our previous block property as stated in the previous comment.
	// however this is only done if THERE IS a previous block to be changed, otherwise
	// a page fault could be thrown.
	if(youngest_block != NULL_BLOCK) {
		unsigned char previous_state = get_descriptor_state(youngest_block);
		struct block_descriptor previous_descriptor = make_block_descriptor(previous_state, current_block_begin);
		set_block_descriptor(youngest_block, previous_descriptor);
	}

	// we need to convert our base block address to an usable memory address for the user
	// this is simply done by adding the size of the descriptor and then returning it
	uint64_t usable_memory = current_block_begin + sizeof(struct block_descriptor);
	free_section = usable_memory + size;
	youngest_block = current_block_begin;

	if(free_section >= (MEM_BASE + MEM_LIMIT))
		kpanic("Exceeded maximum heap memory!");

	return (void*)usable_memory;
}

void kfree(void* base) {
	if((uint64_t)base < MEM_BASE || (uint64_t)base > (MEM_BASE + MEM_LIMIT)) {
		kprint("\nTried freeing an address out of bounds!");
		kprint("\nAddress was: ");
		kprinti((uint64_t) base);
		kprint("\n");
		return;
	}

	// we need to convert our "usable address" to get the base address of the block
	// in order to change its state
	unsigned char* p = (unsigned char*) (base - sizeof(struct block_descriptor));
	p[0] = 'F';
}

bool init_mem(void) {
	memset((void*) MEM_BASE, 0, MEM_LIMIT);
	return true;
}
