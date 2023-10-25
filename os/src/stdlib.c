#include "stdlib.h"
#include "stdio.h"

void kerror(const char* s) {
	if(is_io_initialized())
		kprint(s);

	abort();
}

void abort(void) {
	asm("cli");
	for(;;) {
		asm("hlt");
	}
}
