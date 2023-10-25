#pragma once
#include <stdbool.h>
#include "limine.h"

void init_io(struct limine_framebuffer* framebuffer);
bool is_io_initialized(void);
void kprint(const char* s);
void put_char(uint32_t c);
