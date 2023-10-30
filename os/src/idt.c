#include "idt.h"
#include "pic.h"
#include "stdio.h"
#include "string.h"

struct idt_gate idt[256];
struct idt_descriptor idt_d;

extern void load_idt(void);
extern void* isr_stub_table[];

void init_idt(void) {
	kprint("[IDT] Inizializzazione\n");

	pic_remap(0x20, 0x28);
	idt_d.size = (uint16_t) sizeof(idt) - 1;
	idt_d.offset = (uint64_t) &idt;

	for(size_t i = 0; i < 32; i++)
		set_idt_gate(i, (uint64_t) isr_stub_table[i], 0x8, 0x0, 0x8E);

	load_idt();
	kprint("[IDT] Inizializzato\n");
}

void set_idt_gate(size_t idx, uint64_t offset, uint16_t segment_selector, uint8_t ist, uint8_t type_attributes) {
	idt[idx].offset_low = (offset & 0xFFFF);
	idt[idx].offset_mid = ((offset >> 16) & 0xFFFF);
	idt[idx].offset_high = (uint32_t) ((offset >> 32) & 0xFFFFFFFF);

	idt[idx].segment_selector = segment_selector;
	idt[idx].ist = ist;
	idt[idx].type_attributes = type_attributes;
	idt[idx].reserved = 0x0;
}
