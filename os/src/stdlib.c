#include "stdlib.h"
#include "stdio.h"

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
