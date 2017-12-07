# and don't touch the rest unless you know what you're doing.
CROSS_COMPILE ?= /opt/riscv32i/bin/riscv32-unknown-elf-
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkfile_path)))
headers_dir := $(current_dir)/../headers

CC      =	$(CROSS_COMPILE)gcc
LD      =	$(CROSS_COMPILE)ld
OBJDUMP =	$(CROSS_COMPILE)objdump
OBJCOPY =	$(CROSS_COMPILE)objcopy
SIZE    =	$(CROSS_COMPILE)size

BSP           = ../anthill_hwlib
BSP_INCLUDE   = $(BSP)/periph_hwlib/include \
                $(BSP)/urv_hwlib/include
BOARD_INCLUDE = ../headers

OBJS = boot.o\
       $(BSP)/urv_hwlib/crt_boot.o\
       $(BSP)/urv_hwlib/irq.o\
       $(BSP)/urv_hwlib/urv_time.o\
       $(BSP)/periph_hwlib/uart.o\

LDS_EMB = $(BSP)/urv_hwlib/user_emb.ld
OUTPUT = uart_bootloader

.PHONY: all
all: clean embedded

.PHONY: embedded
embedded: $(OUTPUT).bin
$(OUTPUT).elf $(OUTPUT).bin: $(LDS_EMB) $(OBJS)
	${CC} $(INCLUDE:%=-I%) $(BSP_INCLUDE:%=-I%) $(BOARD_INCLUDE:%=-I%) -flto -O2 -Wl,--gc-sections -o $(OUTPUT).elf -nostartfiles $(OBJS) -lm -T $(LDS_EMB) -lc
	${OBJCOPY} -O binary $(OUTPUT).elf $(OUTPUT).bin
	$(SIZE) $(OUTPUT).elf

.PHONY: disasm
disasm: $(OUTPUT).elf
	${OBJDUMP} -D $(OUTPUT).elf > disasm_emb.S

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(OUTPUT).elf
	rm -f $(OUTPUT).bin
	rm -f disasm.S disasm_debug.S disasm_emb.S

%.o:%.S
	${CC} -c $^ -o $@

%.o:	%.c
	${CC} $(INCLUDE:%=-I%) $(BSP_INCLUDE:%=-I%) $(BOARD_INCLUDE:%=-I%) -c $^ -o $@
