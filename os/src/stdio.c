#define SSFN_CONSOLEBITMAP_TRUECOLOR
#include "stdio.h"
#include <stddef.h>
#include "ssfn.h"
#include "string.h"
#include "stdlib.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
			.id = LIMINE_FRAMEBUFFER_REQUEST,
			.revision = 0
};

// this symbol's name will change depending on the font's name!
extern char _binary___fonts_unifont_sfn_start;

bool init_io(void) {
	struct limine_framebuffer* framebuffer = framebuffer_request.response->framebuffers[0];
	if(framebuffer_request.response == NULL
			|| framebuffer_request.response->framebuffer_count < 1) {
		abort();
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

	return true;
}

void kprint(const char* s) {
	size_t lenght = strlen(s);

	for(size_t i = 0; i < lenght; i++) {
		if(s[i] == '\n') {
			ssfn_dst.x = 20;
			ssfn_dst.y += 20;
			continue;
		}

		ssfn_putc((uint32_t) s[i]);
	}
}

void kprinti(int n) {
	// TODO: kinda ugly
	// 0 will not be printed because the while loop doesn't even begin
	if(n == 0) {
		kprint("0");
		return;
	}

	int i = 0;
	int temp = n;
	int digits[10];

	while(temp) {
		digits[i] = temp % 10;
		temp /= 10;
		i++;
	}

	for(int j = (i - 1); j >= 0; j--) {
		int num_char = digits[j] + '0';
		ssfn_putc((uint32_t) num_char);
	}
}

void kprintok(const char* s) {
	kprint("[OK] ");
	kprint(s);
}
