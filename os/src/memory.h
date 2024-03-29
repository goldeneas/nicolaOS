#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// TODO: maybe using a block_descriptor* instead of a->h might work as well
// and reduce complexity
struct block_descriptor {
	// current state of our memory block
	// U -> IN-USE; F -> FREED
	uint8_t state;

	// address to the next memory block
	// 64 bits, from a -> h
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t f;
	uint8_t g;
	uint8_t h;
};

bool init_mem(void);
void kfree(void* base);
void* kmalloc(size_t size);
