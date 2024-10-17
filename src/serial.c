#include <types.h>
#include <errors.h>
#include <serial.h>

static volatile uart_device_t *debug_uart;

void serial_debug(uint8_t ch) {
	if(debug_uart) {
		debug_uart->put_ch(debug_uart, ch);
	}
}

uint8_t getch_debug() {
	return debug_uart->get_ch(debug_uart);
}

void debug_set_uart(volatile uart_device_t *uart) {
	debug_uart = uart;
}
