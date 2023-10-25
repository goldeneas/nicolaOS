OUTPUT_FORMAT(elf64-x86-64)

OUTPUT_ARCH(i386:x86-64)
 
ENTRY(_start)
 
PHDRS
{
    text    PT_LOAD    FLAGS((1 << 0) | (1 << 2)) ; /* Execute + Read */
    rodata  PT_LOAD    FLAGS((1 << 2)) ;            /* Read only */
    data    PT_LOAD    FLAGS((1 << 1) | (1 << 2)) ; /* Write + Read */
    dynamic PT_DYNAMIC FLAGS((1 << 1) | (1 << 2)) ; /* Dynamic PHDR for relocations */
}
 
SECTIONS
{
	/* Limine mandates that our kernel resides in the topmost 2GiB */
    . = 0xffffffff80000000;
 
    .text : {
        *(.text .text.*)
    } :text
 
	/* Move to the next page */
    . += CONSTANT(MAXPAGESIZE);
 
    .rodata : {
        *(.rodata .rodata.*)
    } :rodata
 
	/* Move to the next page */
    . += CONSTANT(MAXPAGESIZE);
 
    .data : {
        *(.data .data.*)
    } :data
 
    .dynamic : {
        *(.dynamic)
    } :data :dynamic
 
    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } :data
 
    /DISCARD/ : {
        *(.eh_frame)
        *(.note .note.*)
    }
}
