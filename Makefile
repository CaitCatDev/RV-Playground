.SUFFIXES: .c .s .o
CC=clang
LD=clang
AS=clang

TARGET=riscv64-elf

OUTPUT=virt.elf

COBJS=./src/arch/riscv/start.o ./src/arch/riscv/main.o ./src/stdio.o ./src/serial.o ./src/arch/riscv/io.o ./src/drivers/uart_8250.o


CINCS=-I ./includes/ -I ./includes/arch/risc-v/

virt.elf: $(COBJS)
	$(LD) --target=$(TARGET) -o $@ $(COBJS) $(CINCS) -ffreestanding -mcmodel=medium -nostdlib -v -Wl,-T./ld-scripts/rv.ld,--defsym=CATBOOT_TEXT_BASE=0x80000000

vf2.bin: vf2.elf
	@echo "I would recommend not running this code on real Hardware I have run it on my VF2 if you do want to run this find SPL tool for VF2 and flash it to a sdcard."
	llvm-objcopy -O binary vf2.elf vf2.bin

vf2.elf: $(COBJS)
	$(LD) --target=$(TARGET) -o $@ $(COBJS) $(CINCS) -ffreestanding -mcmodel=medium -nostdlib -v -Wl,-T./ld-scripts/rv.ld,--defsym=CATBOOT_TEXT_BASE=0x8000000

.c.o:
	$(CC) --target=$(TARGET) $(CFLAGS) -c -o $@ $< $(CINCS) -ffreestanding -mcmodel=medium

.s.o:
	$(AS) --target=$(TARGET) -c -o $@ $<

clean:
	rm $(COBJS) virt.elf vf2.elf vf2.bin
