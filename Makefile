LIMINE_PATH = ./limine

QEMU = qemu-system-x86_64

ISO_NAME = image
BUILD_PATH = ./build

OS_NAME = nicolaOS
OS_PATH = ./os/build

.PHONY=iso
iso: clean setup-iso
	xorriso -as mkisofs -b limine-bios-cd.bin -no-emul-boot -boot-load-size 4 \
		-boot-info-table --efi-boot limine-uefi-cd.bin -efi-boot-part \
		--efi-boot-image --protective-msdos-label $(BUILD_PATH) -o $(BUILD_PATH)/$(ISO_NAME).iso
	$(LIMINE_PATH)/limine bios-install $(BUILD_PATH)/$(ISO_NAME).iso

.PHONY=setup-iso
setup-iso: compile-os
	cp $(OS_PATH)/$(OS_NAME).elf limine.cfg $(LIMINE_PATH)/limine-bios.sys $(LIMINE_PATH)/limine-bios-cd.bin \
		$(LIMINE_PATH)/limine-uefi-cd.bin $(BUILD_PATH)
	mkdir -p $(BUILD_PATH)/EFI/BOOT
	cp $(LIMINE_PATH)/BOOTX64.EFI $(BUILD_PATH)/EFI/BOOT
	cp $(LIMINE_PATH)/BOOTIA32.EFI $(BUILD_PATH)/EFI/BOOT

.PHONY=compile-os
compile-os:
	make -C os

.PHONY=boot
boot: iso
	$(QEMU) -cdrom $(BUILD_PATH)/$(ISO_NAME).iso -gdb tcp::26000

.PHONY=limine
limine:
	mkdir -p $(LIMINE_PATH)
	git clone https://github.com/limine-bootloader/limine.git --branch=v5.x-branch-binary --depth=1
	make -C limine
	link limine/limine.h os/src/limine.h

.PHONY=clean
clean:
	cd $(BUILD_PATH) && rm -rf *
	make clean -C os
