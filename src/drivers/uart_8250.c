#include <serial.h>
#include <types.h>
#include <io.h>

#define UART_REG_RBR_OFFSET 0
#define UART_REG_RHR_OFFSET 0
#define UART_REG_DLL_OFFSET 0
#define UART_REG_DLH_OFFSET 1
#define UART_REG_IER_OFFSET 1
#define UART_REG_IIR_OFFSET 2 /*R*/
#define UART_REG_FCR_OFFSET 2 /*W*/
#define UART_REG_LCR_OFFSET 3 /*RW*/
#define UART_REG_MCR_OFFSET 4 /*RW*/
#define UART_REG_LSR_OFFSET 5 /*R*/
#define UART_REG_MSR_OFFSET 6 /*R*/
#define UART_REG_SCR_OFFSET 7 /*RW*/


#define UART_LSR_THRE 0x20
#define UART_LSR_DR 0x01
#define UART_DIVSIOR_LATCH 0x80

static inline uint32_t get_uart_register(uint32_t reg, uint32_t shift, uint32_t off, uint32_t width, volatile void *base) {
	volatile void *address = ((base + off) + (reg << shift));
	switch(width) {
		case 1:
			return read8(address);
		case 2:
			return read16(address);
		case 4:
			return read32(address);
		default:
			/*Uhhhh TODO: Error stuff*/
			return 0;
	}
}

static void set_uart_register(uint32_t reg, uint32_t shift, uint32_t off, uint32_t width, volatile void *base, uint32_t data) {
	volatile void *address = ((base + off) + (reg << shift));
	switch(width) {
		case 1:
			write8(address, data);
			break;
		case 2:
			write16(address, data);
			break;
		case 4:
			write32(address, data);
			break;
		default:
			/*Uhhhh TODO: Error stuff*/
			return;
	}
}


int8_t uart_getch(volatile uart_device_t *dev) {
	volatile uint8_t *base = dev->base + dev->roff;
	if((read8(base + (UART_REG_LSR_OFFSET << dev->rshift)) & UART_LSR_DR))	{
		return read8(base + (UART_REG_RBR_OFFSET << dev->rshift));
	}	

	return -1;
}

void uart_putch(volatile uart_device_t *dev, uint8_t ch) {
	volatile uint8_t *uart_dr = dev->base + dev->roff;

	while ((read8(dev->base + (UART_REG_LSR_OFFSET << dev->rshift)) & UART_LSR_THRE) == 0) {
	}

	*uart_dr = ch;
}

static uart_device_t uart_dev = { 0 };

void uart_init(uint32_t freq, uint32_t baud, uint32_t rshift, uint32_t rwidth, uint32_t roff, volatile void *base) {
	uint16_t bdiv = (freq + 8 * baud) / (16 * baud);
	
	set_uart_register(UART_REG_IER_OFFSET, rshift, roff, rwidth, base, 0x00);
	set_uart_register(UART_REG_LCR_OFFSET, rshift, roff, rwidth, base, UART_DIVSIOR_LATCH);

	if(bdiv) {
		set_uart_register(UART_REG_IER_OFFSET, rshift, roff, rwidth, base, bdiv & 0xff);
		set_uart_register(UART_REG_LCR_OFFSET, rshift, roff, rwidth, base, (bdiv >>  8) & 0xff);
	}
	
	set_uart_register(UART_REG_LCR_OFFSET, rshift, roff, rwidth, base, 0x3);

	set_uart_register(UART_REG_FCR_OFFSET, rshift, roff, rwidth, base, 0x1);

	set_uart_register(UART_REG_MCR_OFFSET, rshift, roff, rwidth, base, 0x1);
	
	get_uart_register(UART_REG_LSR_OFFSET, rshift, roff, rwidth, base);
	get_uart_register(UART_REG_RBR_OFFSET, rshift, roff, rwidth, base);
	
	uart_dev.get_ch = uart_getch;
	uart_dev.put_ch = uart_putch;
	uart_dev.base = base;
	uart_dev.roff = roff;
	uart_dev.rshift = rshift;
	uart_dev.rwidth = rwidth;
	debug_set_uart(&uart_dev);
}
