#include "excp_handler.h"
#include "stdio.h"

__attribute__ ((noreturn)) void excp_handler(void) {
	kprint("[EXCP_HANDLER] OMAGAD WE BOUTA CRASH AAA\n");
	asm volatile ("cli; hlt");
}
