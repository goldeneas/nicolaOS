#include "stdlib.h"
#include "stdio.h"

void abort(void) {
	asm("cli");
	for(;;) {
		asm("hlt");
	}
}
