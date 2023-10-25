#define SSFN_CONSOLEBITMAP_TRUECOLOR
#include "stdio.h"
#include <stddef.h>
#include "ssfn.h"
#include "string.h"

// this symbol's name will change depending on the font's name!
extern char _binary___fonts_unifont_sfn_start;

bool is_initialized = false;

void init_io(struct limine_framebuffer* framebuffer) {
	if(is_initialized) {
		kprint("Tried initializing stdio twice!");
		return;
	}

	ssfn_src = (ssfn_font_t*) &_binary___fonts_unifont_sfn_start;
	ssfn_dst.ptr = framebuffer->address;
	ssfn_dst.w = (uint16_t) framebuffer->width;
	ssfn_dst.h = (uint16_t) framebuffer->height;
	ssfn_dst.p = (uint16_t) framebuffer->pitch;
	ssfn_dst.fg = (uint32_t) 0xffffff;
	ssfn_dst.bg = (uint32_t) 0;
	ssfn_dst.x = 20;
	ssfn_dst.y = 40;

	is_initialized = true;
}

bool is_io_initialized(void) {
	return is_initialized;
}

void put_char(uint32_t c) {
	ssfn_putc(c);
}

void kprint(const char* s) {
	size_t lenght = strlen(s);

	for(size_t i = 0; i < lenght; i++) {
		if(s[i] == '\n') {
			ssfn_dst.x = 20;
			ssfn_dst.y += 20;
			continue;
		}

		put_char((uint32_t) s[i]);
	}
}
