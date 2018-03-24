CC := arm-none-eabi-gcc
CFLAGS = -fno-common -O0 \
	 -mcpu=cortex-m3 -mthumb \
	 -T ldscripts/kernel.ld -nostartfiles \

NAME=k-os
ELF=dist/$(NAME).elf
BIN=dist/$(NAME).bin
LST=dist/$(NAME).list

all: $(BIN)

$(BIN): src/k-os.c src/startup.c src/context.s src/usart.c
	mkdir -p dist
	$(CC) $(CFLAGS) $^ -o $(ELF)
	arm-none-eabi-objcopy -Obinary $(ELF) $(BIN)
	arm-none-eabi-objdump -S $(ELF) > $(LST)

run: $(BIN)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -M stm32-p103 -nographic -kernel $(BIN)

clean:
	rm -f *.o
	rm -rf dist
