
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
CFLAGS = -Wall -Wextra -O2 -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -g -O0

BUILD_DIR = build
SRC_DIR = src
HEADER_DIR = inc

FILES = $(wildcard $(SRC_DIR)/*.c)
LINKER_FILES = $(FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

out: $(LINKER_FILES)
	$(LD) -T linker.ld -nostdlib -o $(BUILD_DIR)/output.elf $(LINKER_FILES)
	sh readElf.sh
	sh dumpElf.sh

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -nostdlib -Iinc -S $< -o $(BUILD_DIR)/$*.s
	$(AS) $(BUILD_DIR)/$*.s -o $(BUILD_DIR)/$*.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.s $(BUILD_DIR)/output.elf