global	load_gdt
extern	gdt_d

load_gdt:
	cli
	lgdt [gdt_d]

reload_segments:
	push 0x08 			; 0x08 code segment
	lea rax, [rel .reload_cs]
	push rax
	retfq
.reload_cs:
	mov ax, 0x10		; 0x10 data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
