#pragma once
#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
	uint8_t b;
	asm volatile("inb %1, %0" : "=a"(b) : "Nd"(port) : "memory");

	return b;
}

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile("outb %0, %1" :: "a"(val), "Nd"(port) : "memory");
}
