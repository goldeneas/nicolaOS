#include "pic.h"
#include "cpu.h"
#include "stdio.h"
#include "stdlib.h"

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC2_COMMAND PIC2
#define PIC1_DATA (PIC1 + 1)
#define PIC2_DATA (PIC2 + 1)

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04	/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08	/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C	/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define EOI 0x20

void pic_remap(uint8_t master_offset, uint8_t slave_offset) {
	kprint("Starting PIC remap...\n");

	unsigned char master_masks, slave_masks;

	master_masks = inb(PIC1_DATA);
	slave_masks = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();

	outb(PIC1_DATA, master_offset);
	io_wait();
	outb(PIC2_DATA, slave_offset);
	io_wait();

	outb(PIC1_DATA, 4);
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();

	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, master_masks);
	outb(PIC2_DATA, slave_masks);

	kprint("Succesfully remapped PIC\n");
}

void pic_send_eoi(unsigned char irq) {
	if(irq >= 8)
		outb(PIC2_COMMAND, EOI);

	outb(PIC1_COMMAND, EOI);
}

void pic_broadcast_excp(struct interrupt_frame* f) {
	switch(f->int_idx) {
		case 13:
			excp_13(f);
			break;

		case 14:
			excp_14(f);
			break;
	}
}

void excp_13(struct interrupt_frame* f) {
	kpanic("General Protection Fault was thrown!");
}

void excp_14(struct interrupt_frame* f) {
	kpanic("Page Fault was thrown!");
}
