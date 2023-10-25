#include "draw.h"

void draw_pixel(uint64_t x, uint64_t y, uint32_t color, struct limine_framebuffer* framebuffer) {
	volatile uint32_t* pframebuffer = framebuffer->address;
	pframebuffer[y * framebuffer->pitch + x] = color;
}

void draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color, struct limine_framebuffer* framebuffer) {
	volatile uint32_t* pframebuffer = framebuffer->address;

	for(uint64_t row = 0; row < height; row++)
		for(uint64_t col = 0; col < width; col++)
			pframebuffer[(y + row) * (framebuffer->pitch / 4) + (x + col)] = color;
}

void draw_square(uint64_t x, uint64_t y, uint64_t size, uint32_t color, struct limine_framebuffer* framebuffer) {
	draw_rectangle(x, y, size, size, color, framebuffer);
}
