#pragma once

#include <types.h>

typedef struct _uart_device_s uart_device_t;

struct _uart_device_s {
	volatile void *base;
	void (*put_ch)(volatile uart_device_t *dev, uint8_t ch); 
	int8_t (*get_ch)(volatile uart_device_t *dev);
	uint32_t rshift, roff, rwidth;
};


uint8_t getch_debug();
void serial_debug(uint8_t ch);
void debug_set_uart(volatile uart_device_t *uart);

void uart_init(uint32_t freq, uint32_t baud, uint32_t rshift, uint32_t rwidth, uint32_t roff, volatile void *base);	
