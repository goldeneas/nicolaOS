#include "kernel.h"
#include <stdbool.h>
#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "gdt.h"
#include "idt.h"

void _start(void) {
	if(init_io()) kprintok("Succesfully initialized I/O\n");
	if(init_mem()) kprintok("Succesfully initialized memory\n");
	if(init_gdt()) kprintok("Succesfully setup GDT\n");
	if(init_idt()) kprintok("Succesfully setup IDT\n");

	kprint("--- nicolaOS v0.0.1 ---\n");

	uint64_t* a = kmalloc(2);
	kfree(a);

	kprint("hi");
	abort();
}
