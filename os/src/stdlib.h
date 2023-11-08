#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void abort(void);
void kpanic(const char* s);

bool init_mem(void);
void kfree(uint64_t base, size_t size);
uint64_t kmalloc(size_t size);
