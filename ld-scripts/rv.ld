ENTRY(_start)

SECTIONS {
	. = CATBOOT_TEXT_BASE;
  .text ALIGN(4K) : {
    *(.text)
  }
	.rodata ALIGN(4K) : {
		*(.rodata .rodata.*)
	}
	.data ALIGN(4K) : {
		*(.data)
	}
	.bss ALIGN(4K) : {
		*(.bss)
	}
}
