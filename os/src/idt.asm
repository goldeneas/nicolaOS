global load_idt
extern idt_d

load_idt:
	lidt [idt_d]
