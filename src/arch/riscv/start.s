.text

.type start,@function
.global _start
.global DATA

_start:
	csrr a0,mhartid

	/*Setup trap handlers*/
	la t0, _trap_entry
	csrw mtvec, t0
	/*Each Thread Gets A Stack*/
	/*TODO: we only support upto 5 cores atm cause the stack is only 0x5000*/
	la sp,_stack_top
	sll t1, a0,12
	sub sp, sp,t1


	/*Pick a CPU to continue booting with in multicore environments*/
	la t0,DATA
	addi t1,x0,1
	amoswap.w s2,t1,(t0)
	bnez s2,_loop

	call cmain

_loop:
	wfi
	j _loop

.global _dump_registers

_dump_registers:
	addi sp, sp, -31 * 8
	sd x1, 0 * 8(sp)
	sd x2, 1 * 8(sp)
	sd x3, 2 * 8(sp)
	sd x4, 3 * 8(sp)
	sd x5, 4 * 8(sp)
	sd x6, 5 * 8(sp)
	sd x7, 6 * 8(sp)
	sd x8, 7 * 8(sp)
	sd x9, 8 * 8(sp)
	sd x10, 9 * 8(sp)
	sd x11, 10 * 8(sp)
	sd x12, 11 * 8(sp)
	sd x13, 12 * 8(sp)
	sd x14, 13 * 8(sp)
	sd x15, 14 * 8(sp)
	sd x16, 15 * 8(sp)
	sd x17, 16 * 8(sp)
	sd x18, 17 * 8(sp)
	sd x19, 18 * 8(sp)
	sd x20, 19 * 8(sp)
	sd x21, 20 * 8(sp)
	sd x22, 21 * 8(sp)
	sd x23, 22 * 8(sp)
	sd x24, 23 * 8(sp)
	sd x25, 24 * 8(sp)
	sd x26, 25 * 8(sp)
	sd x27, 26 * 8(sp)
	sd x28, 27 * 8(sp)
	sd x29, 28 * 8(sp)
	sd x30, 29 * 8(sp)
	sd x31, 30 * 8(sp)

	addi a0, sp, 0
	call print_regs
	
	ld x1, 0 * 8(sp)
	ld x2, 1 * 8(sp)
	ld x3, 2 * 8(sp)
	ld x4, 3 * 8(sp)
	ld x5, 4 * 8(sp)
	ld x6, 5 * 8(sp)
	ld x7, 6 * 8(sp)
	ld x8, 7 * 8(sp)
	ld x9, 8 * 8(sp)
	ld x10, 9 * 8(sp)
	ld x11, 10 * 8(sp)
	ld x12, 11 * 8(sp)
	ld x13, 12 * 8(sp)
	ld x14, 13 * 8(sp)
	ld x15, 14 * 8(sp)
	ld x16, 15 * 8(sp)
	ld x17, 16 * 8(sp)
	ld x18, 17 * 8(sp)
	ld x19, 18 * 8(sp)
	ld x20, 19 * 8(sp)
	ld x21, 20 * 8(sp)
	ld x22, 21 * 8(sp)
	ld x23, 22 * 8(sp)
	ld x24, 23 * 8(sp)
	ld x25, 24 * 8(sp)
	ld x26, 25 * 8(sp)
	ld x27, 26 * 8(sp)
	ld x28, 27 * 8(sp)
	ld x29, 28 * 8(sp)
	ld x30, 29 * 8(sp)
	ld x31, 30 * 8(sp)
	addi sp, sp, 31 * 8

	ret

.align 6
_trap_entry:
	addi sp, sp, -31 * 8
	sd x1, 0 * 8(sp)
	sd x2, 1 * 8(sp)
	sd x3, 2 * 8(sp)
	sd x4, 3 * 8(sp)
	sd x5, 4 * 8(sp)
	sd x6, 5 * 8(sp)
	sd x7, 6 * 8(sp)
	sd x8, 7 * 8(sp)
	sd x9, 8 * 8(sp)
	sd x10, 9 * 8(sp)
	sd x11, 10 * 8(sp)
	sd x12, 11 * 8(sp)
	sd x13, 12 * 8(sp)
	sd x14, 13 * 8(sp)
	sd x15, 14 * 8(sp)
	sd x16, 15 * 8(sp)
	sd x17, 16 * 8(sp)
	sd x18, 17 * 8(sp)
	sd x19, 18 * 8(sp)
	sd x20, 19 * 8(sp)
	sd x21, 20 * 8(sp)
	sd x22, 21 * 8(sp)
	sd x23, 22 * 8(sp)
	sd x24, 23 * 8(sp)
	sd x25, 24 * 8(sp)
	sd x26, 25 * 8(sp)
	sd x27, 26 * 8(sp)
	sd x28, 27 * 8(sp)
	sd x29, 28 * 8(sp)
	sd x30, 29 * 8(sp)
	sd x31, 30 * 8(sp)

	addi a0, sp, 0
	csrr a1,mcause
	csrr a2,mepc
	csrr a3,mtval
	
	call trap_handler
	
	ld x1, 0 * 8(sp)
	ld x2, 1 * 8(sp)
	ld x3, 2 * 8(sp)
	ld x4, 3 * 8(sp)
	ld x5, 4 * 8(sp)
	ld x6, 5 * 8(sp)
	ld x7, 6 * 8(sp)
	ld x8, 7 * 8(sp)
	ld x9, 8 * 8(sp)
	ld x10, 9 * 8(sp)
	ld x11, 10 * 8(sp)
	ld x12, 11 * 8(sp)
	ld x13, 12 * 8(sp)
	ld x14, 13 * 8(sp)
	ld x15, 14 * 8(sp)
	ld x16, 15 * 8(sp)
	ld x17, 16 * 8(sp)
	ld x18, 17 * 8(sp)
	ld x19, 18 * 8(sp)
	ld x20, 19 * 8(sp)
	ld x21, 20 * 8(sp)
	ld x22, 21 * 8(sp)
	ld x23, 22 * 8(sp)
	ld x24, 23 * 8(sp)
	ld x25, 24 * 8(sp)
	ld x26, 25 * 8(sp)
	ld x27, 26 * 8(sp)
	ld x28, 27 * 8(sp)
	ld x29, 28 * 8(sp)
	ld x30, 29 * 8(sp)
	ld x31, 30 * 8(sp)
	addi sp, sp, 31 * 8

	mret

.data
DATA: .long 0

.bss

.lcomm _stack_bottom, 0x5000
_stack_top:
