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
