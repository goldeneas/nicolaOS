#include "kernel.h"
#include <stddef.h>
#include "limine.h"
#include "stdlib.h"
#include "stdio.h"
#include "draw.h"
#include "gdt.h"
#include "idt.h"

void _start(void) {
	if(init_io())
		kprint("Succesfully initialized I/O\n");

	if(init_mem())
		kprint("Succesfully initialized memory\n");

	if(init_gdt())
		kprint("Succesfully setup GDT\n");

	if(init_idt())
		kprint("Succesfully setup IDT\n");

	kprint("--- nicolaOS v0.0.1 ---");

	// TODO: might not be working
	kfree(0x1000, 10);

	kprint("hi");

	abort();
}
