.text

.global __raw_read8
.global __raw_read16
.global __raw_read32
.global __raw_read64

.global __raw_write8
.global __raw_write16
.global __raw_write32
.global __raw_write64

.global __io_mb
.global __io_mbw
.global __io_mbr

.global _enable_ints

__raw_write8:
	sb a1,(a0)
	ret

__raw_write16:
	sh a1,(a0)
	ret

__raw_write32:
	sw a1,(a0)
	ret

__raw_write64:
	sd a1,(a0)
	ret

__raw_read8:
	lbu a1,(a0)
	add a0, x0, a1
	ret

__raw_read16:
	lhu a1,(a0)
	add a0, x0, a1
	ret

/* TODO: We assume RV64 and this opcode may not exist in 
 * RV32 or other specs
 */
__raw_read32:
	lwu a1,(a0)
	add a0, x0, a1
	ret

__raw_read64:
	ld a1,(a0)
	add a0, x0, a1
	ret

__io_mb:
	fence iorw,iorw
	ret

__io_mbr:
	fence ir,ir
	ret

__io_mbw:
	fence ow,ow
	ret
