#pragma once
#include <stdint.h>
#include <stdlib.h>

struct interrupt_frame {
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
	uint64_t rsi, rdi, rdx, rcx, rbx, rax;
	uint64_t err_code, int_idx;
	uint64_t rip, cs, rflags, rsp, ss;
} __attribute__ ((packed));

void pic_send_eoi(unsigned char irq);
void pic_remap(uint8_t master_offset, uint8_t slave_offset);
void pic_broadcast_excp(struct interrupt_frame* f);

static inline void pic_unmask_interrupts(void) {
	asm volatile("sti");
}

static inline void pic_mask_interrupts(void) {
	asm volatile("cli");
}

__attribute__ ((interrupt)) void excp_0(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_1(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_2(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_3(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_4(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_5(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_6(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_7(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_8(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_9(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_10(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_11(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_12(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_13(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_14(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_15(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_16(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_17(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_18(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_19(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_20(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_21(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_22(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_23(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_24(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_25(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_26(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_27(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_28(struct interrupt_frame* p);
__attribute__ ((interrupt)) void excp_29(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_30(struct interrupt_frame* p, unsigned long err_code);
__attribute__ ((interrupt)) void excp_31(struct interrupt_frame* p);
