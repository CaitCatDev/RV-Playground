#pragma once

#include <types.h>

void __raw_write8(volatile void *address, uint8_t val);
void __raw_write16(volatile void *address, uint16_t val);
void __raw_write32(volatile void *address, uint32_t val);
void __raw_write64(volatile void *address, uint64_t val);

uint8_t __raw_read8(volatile void *address);
uint16_t __raw_read16(volatile void *address);
uint32_t __raw_read32(volatile void *address);
uint64_t __raw_read64(volatile void *address);

/*Memory barrier functions*/
void __io_mb();
void __io_mbr();
void __io_mbw();

static inline uint64_t read64(volatile void *address) {
	uint64_t val = __raw_read64(address);
	__io_mbr();
	return val;
}

static inline uint32_t read32(volatile void *address) {
	uint32_t val = __raw_read32(address);
	__io_mbr();
	return val;
}

static inline uint16_t read16(volatile void *address) {
	uint16_t val = __raw_read16(address);
	__io_mbr();
	return val;
}

static inline uint8_t read8(volatile void *address) {
	uint8_t val = __raw_read16(address);
	__io_mbr();
	return val;
}

static inline void write64(volatile void *address, uint64_t val) {
	__raw_write64(address, val);
	__io_mbw();
	return;
}

static inline void write32(volatile void *address, uint32_t val) {
	__raw_write32(address, val);
	__io_mbw();
	return;
}

static inline void write16(volatile void *address, uint16_t val) {
	__raw_write16(address, val);
	__io_mbw();
	return;
}

static inline void write8(volatile void *address, uint8_t val) {
	__raw_write8(address, val);
	__io_mbw();
	return;
}
