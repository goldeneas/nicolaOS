# PATHS/NAMES
OS_NAME = nicolaOS
SRC_PATH = ./src
BUILD_PATH = ./build

FONT_NAME = unifont
FONT_PATH = ./fonts

# COMMANDS/FLAGS
OBJCOPY = x86_64-elf-objcopy

CC = x86_64-elf-gcc
CC_FLAGS = -ffreestanding -g -Wall -Wextra -pedantic -Wshadow -Wpointer-arith \
		   -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls \
		   -Wnested-externs -Winline -Wno-long-long -Wconversion -Wstrict-prototypes -fPIC

LD = x86_64-elf-ld
LD_FLAGS = -T linker.ld -m elf_x86_64 -nostdlib -z text -z max-page-size=0x1000

NASM = nasm
NASM_FLAGS = -f elf64

# FILES
SRC_FILES := $(shell cd $(SRC_PATH) && find -L * -type f -name '*.c')
ASM_FILES := $(shell cd $(SRC_PATH) && find -L * -type f -name '*.asm')
OBJ_FILES := $(SRC_FILES:%.c=%.o) $(ASM_FILES:%.asm=asm_%.o)

#RECIPES
.PHONY=os
os: font $(OBJ_FILES)
	$(LD) $(LD_FLAGS) $(addprefix $(BUILD_PATH)/, $(OBJ_FILES)) $(BUILD_PATH)/$(FONT_NAME).o -o $(BUILD_PATH)/$(OS_NAME).elf

.PHONY=font
font:
	$(OBJCOPY) -O elf64-x86-64 -I binary $(FONT_PATH)/$(FONT_NAME).sfn $(BUILD_PATH)/$(FONT_NAME).o

%.o: $(SRC_PATH)/%.c
	$(CC) $(CC_FLAGS) -I$(dir $<) -c $< -o $(BUILD_PATH)/$@

asm_%.o: $(SRC_PATH)/%.asm
	$(NASM) $(NASM_FLAGS) $< -o $(BUILD_PATH)/$@

.PHONY=clean
clean:
	cd $(BUILD_PATH) && rm -rf *

