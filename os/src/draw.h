#pragma once
#include <stddef.h>
#include <stdint.h>
#include "limine.h"

void draw_pixel(uint64_t x, uint64_t y, uint32_t color, struct limine_framebuffer* framebuffer);
void draw_square(uint64_t x, uint64_t y, uint64_t size, uint32_t color, struct limine_framebuffer* framebuffer);
void draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color, struct limine_framebuffer* framebuffer);
