#pragma once
#include <stdint.h>
#include <stdlib.h>

struct interrupt_frame {
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
	uint64_t rsi, rdi, rdx, rcx, rbx, rax;
	uint64_t int_idx, err_code;
	uint64_t rip, cs, rflags, rsp, ss;
} __attribute__ ((packed));

void pic_send_eoi(unsigned char irq);
void pic_remap(uint8_t master_offset, uint8_t slave_offset);
void pic_broadcast_excp(struct interrupt_frame* f);

void excp_13(struct interrupt_frame* f);
void excp_14(struct interrupt_frame* f);
