#pragma once
#include <types.h>
#include <stdarg.h>


void stdio_init(void (*PRINTCH)(uint8_t ch));
void puts(const char *str);	
void puth(uint64_t value, uint16_t nibbles);
void putd(uint64_t value);
void vkprintf(const char *fmt, va_list args);
void kprintf(const char *fmt, ...);
