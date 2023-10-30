#include "kernel.h"
#include <stddef.h>
#include "limine.h"
#include "stdlib.h"
#include "stdio.h"
#include "draw.h"
#include "gdt.h"
#include "idt.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};

static volatile struct limine_paging_mode_request paging_request = {
	.id = LIMINE_PAGING_MODE_REQUEST,
	.mode = LIMINE_PAGING_MODE_DEFAULT,
	.revision = 0
};

void _start(void) {
	uint64_t paging_mode = paging_request.response->mode;
	if(paging_request.response == NULL
			|| paging_mode != LIMINE_PAGING_MODE_DEFAULT) {
		abort();
	}

	struct limine_framebuffer* framebuffer = framebuffer_request.response->framebuffers[0];
	if(framebuffer_request.response == NULL
			|| framebuffer_request.response->framebuffer_count < 1) {
		abort();
	}

	
	init_io(framebuffer);
	kprint("nicolaOS - (v0.0.1)\n");
	kprint("-------------------\n");
	
	init_gdt();
	init_idt();

	abort();
}
