#include <exceptions.h>
#include <types.h>
#include <serial.h>
#include <stdio.h>
#include <io.h>

typedef struct cpu_state {
	reg_t ra;
	reg_t sp;
	reg_t gp;
	reg_t tp;
	reg_t t0;
	reg_t t1;
	reg_t t2;
	reg_t fp;
	reg_t s1;
	reg_t a0;
	reg_t a1;
	reg_t a2;
	reg_t a3;
	reg_t a4;
	reg_t a5;
	reg_t a6;
	reg_t a7;
	reg_t s2;
	reg_t s3;
	reg_t s4;
	reg_t s5;
	reg_t s6;
	reg_t s7;
	reg_t s8;
	reg_t s9;
	reg_t s10;
	reg_t s11;
	reg_t t3;
	reg_t t4;
	reg_t t5;
	reg_t t6;
} cpu_state_t;

void *memset(void *dst, int val, uint64_t n) {
	uint8_t *dstu8 = dst;

	for(uint64_t i = 0; i < n; i++) {
		dstu8[i] = val;
	}

	return dst;
}

const char *trap_name(reg_t cause) {
	if(cause & RV_INTERRUPT_BIT) {
		return "Int";
	}
	switch(cause) {
		case RV_TRAP_INSTR_ADDR_MISALIGNED:
			return "Instruction Address Misaligned";
		case RV_TRAP_INSTR_ACCESS_FAULT:
			return "Instruction Access Fault";
		case RV_TRAP_ILLEGAL_INSTR:
			return "Illegal Instruction";
		case RV_TRAP_LO_ADDRESS_MISALIGNED:
			return "Load Address Misaligned";
		case RV_TRAP_LO_ACCESS_FAULT:
			return "Load Access Fault";
		case RV_TRAP_ST_ADDRESS_MISALIGNED:
			return "Store Address Misaligned";
		case RV_TRAP_ST_ACCESS_FAULT:
			return "Store Access Fault";
		case RV_TRAP_ECALL_FROM_UMODE:
		case RV_TRAP_ECALL_FROM_SMODE:
		case RV_TRAP_ECALL_FROM_MMODE:
			return "ecall";
		case RV_TRAP_INSTR_PAGE_FAULT:
			return "Instruction Page Fault";
		case RV_TRAP_LO_PAGE_FAULT:
			return "Load Page Fault";
		case RV_TRAP_ST_PAGE_FAULT:
			return "Store Page Fault";
		case RV_TRAP_SOFTWARE_CHECK:
			return "Software Check";
		case RV_TRAP_HARDWARE_ERROR:
			return "Hardware Error";
		default:
			return "Unknown";
	}

	return "Unknown";
}

const char *int_name(reg_t cause) {
	return "Int";
}

void print_regs(cpu_state_t *regs) {
	kprintf("RA: %r, SP: %r, GP: %r\r\n", regs->ra, regs->sp, regs->gp);
	kprintf("FP: %r, TP: %r\r\n", regs->fp, regs->tp);

	kprintf("A Regs:\r\n");
	/*Args*/
	kprintf("A0: %r, A1: %r, A2: %r\r\n", regs->a0, regs->a1, regs->a2);
	kprintf("A3: %r, A4: %r, A5: %r\r\n", regs->a3, regs->a4, regs->a5);
	kprintf("A6: %r, A7: %r\r\n", regs->a6, regs->a7);
	

	kprintf("T Regs:\r\n");
	/*Temp Regs*/
	kprintf("T0: %r, T1: %r, T2: %r\r\n", regs->t0, regs->t1, regs->t2);
	kprintf("T3: %r, T4: %r, T5: %r\r\n", regs->t3, regs->t4, regs->t5);
	kprintf("T6: %r\r\n", regs->t6);
	
	kprintf("S Regs:\r\n");
	/*Save Regs*/
	kprintf("S1: %r, S2: %r, S3: %r\r\n", regs->s1, regs->s2, regs->s3);
	kprintf("S4: %r, S5: %r, S6: %r\r\n", regs->s4, regs->s5, regs->s6);
	kprintf("S7: %r, S8: %r, S9: %r\r\n", regs->s7, regs->s8, regs->s9);
	kprintf("S10: %r, S11: %r\r\n", regs->s10, regs->s11);

	kprintf("\r\n");
}

void _dump_registers();

void trap_handler(cpu_state_t *regs, reg_t cause, reg_t epc, reg_t val) {
	if(cause & RV_INTERRUPT_BIT) {
		volatile uint32_t *baggage = (void*)0xc000000 + 0x202004;
		uint32_t num = *baggage;
		kprintf("baggage: %x\r\n", num);
		return;
	}

	kprintf("Trap: %s\r\n", trap_name(cause));
	kprintf("Cause: %r,  epc: %r, val: %r\r\n", cause, epc, val);

	print_regs(regs);

	while(1) {
	
	}
} 

void cmain(int hart_id) {
	volatile uint8_t *serial = (void*)0x10000000;
	int8_t ch = 0;

#if defined (VIRTUAL_RISCV) && defined (VF2_RISCV)
	#error "Both platforms can't be defined at once"
#endif

#if defined(VIRTUAL_RISCV)
	uart_init(0, 115200, 0, 1, 0, serial);
#elif defined(VF2_RISCV)
	uart_init(0, 115200, 2, 4, 0, serial);
#else 
	#error "We need a platform to compile for -DVF2_RISCV or -DVIRTUAL_RISCV"
#endif
	stdio_init(serial_debug);
	
	while(1) {
		ch = getch_debug();
		if(ch > 0) {
			serial_debug(ch);
		}
	}

	return;
}
