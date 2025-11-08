# nicolaOS
`nicolaOS` is a hobby x86-64 operating system. This is a foundational project that successfully boots, initializes core system structures, and demonstrates basic kernel-level functionality.

After booting, the kernel initializes its components, prints a welcome message and status updates to the framebuffer, allocates and frees a small block of memory to test the heap, and then deliberately halts.

## Features

* **Bootloader:** Uses the [Limine boot protocol](https://github.com/limine-bootloader/limine).
* **Core Structures:**
    * **Global Descriptor Table (GDT):** Sets up a basic 64-bit GDT with null, code, and data segments.
    * **Interrupt Descriptor Table (IDT):** Initializes a 256-entry IDT and loads it.
* **Interrupt Handling:**
    * Remaps the **PIC (Programmable Interrupt Controller)**.
    * Provides assembly stubs for the first 32 CPU exceptions.
    * Includes basic panic handlers for General Protection Faults (Exception 13) and Page Faults (Exception 14).
* **Memory Management:**
    * A custom, basic heap allocator (`kmalloc`/`kfree`) implemented in `os/src/memory.c`.
* **Display:**
    * Basic framebuffer output via Limine.
    * Font rendering using [SSFN (Scalable Screen Font)](https://gitlab.com/bztsrc/scalable-font2).
* **Standard Library:**
    * Minimal, custom implementations for `string.h` (`strlen`, `memset`, etc.) and `stdlib.h` (`abort`, `kpanic`).

## Building and Running

### Prerequisites

You will need the following tools to build and run `nicolaOS`:

* A GNU/Linux environment
* `make`
* `git`
* `qemu` (specifically `qemu-system-x86_64`)
* `xorriso`
* `nasm`
* An x86-64 ELF cross-compiler (e.g., `x86_64-elf-gcc`, `x86_64-elf-ld`).

### 1. Setup

First, you must fetch the Limine bootloader:

```bash
make limine
```

This will clone the Limine repository into a local limine/ directory

### 2. Build and Run
To compile the kernel, create the bootable ISO, and launch QEMU, run:

```bash
make boot
```
