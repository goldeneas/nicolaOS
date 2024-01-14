#include "kernel.h"
#include <stddef.h>
#include <stdbool.h>
#include "limine.h"
#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "draw.h"
#include "gdt.h"
#include "idt.h"

void _start(void) {
	if(init_io()) kprintok("Succesfully initialized I/O\n");
	if(init_mem()) kprintok("Succesfully initialized memory\n");
	if(init_gdt()) kprintok("Succesfully setup GDT\n");
	if(init_idt()) kprintok("Succesfully setup IDT\n");

	kprint("--- nicolaOS v0.0.1 ---\n");

	// TODO: might not be working
	struct block_descriptor* a = (struct block_descriptor*) kmalloc(sizeof(struct block_descriptor));
	uint64_t* b = kmalloc(2);

	a->state = 'F';
	a->f = 300;
	kprinti(a->state);
	kprint("\n");
	kprinti(a->f);

	kfree(a);

	kprint("hi");

	abort();
}
