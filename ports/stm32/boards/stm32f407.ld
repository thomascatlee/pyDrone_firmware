/*
    GNU linker script for STM32F407
*/

/* Specify the memory areas */
MEMORY
{
		FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 1024K /* entire flash */
		FLASH_ISR (rx)  : ORIGIN = 0x08000000, LENGTH = 16K /* sector 0 */
		FLASH_FS (rx)   : ORIGIN = 0x08004000, LENGTH = 112K /* sectors 1,2,3,4 are for filesystem */
		FLASH_TEXT (rx) : ORIGIN = 0x08020000, LENGTH = 896K /* sectors 5,6,7,8,9,10,11 */
		CCMRAM (xrw)    : ORIGIN = 0x10000000, LENGTH = 64K
		RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K /*128*/
		SRAM (xrw)      : ORIGIN = 0x68000000, LENGTH = 1024K /*128*/
}

/* produce a link error if there is not this amount of RAM for these sections */
_minimum_stack_size = 2K;
_minimum_heap_size = 16K;

/* Define the stack.  The stack is full descending so begins just above last byte
   of RAM.  Note that EABI requires the stack to be 8-byte aligned for a call. */
_estack = ORIGIN(RAM) + LENGTH(RAM) - _estack_reserve;
_sstack = _estack - 16K; /* tunable */

/* RAM extents for the garbage collector */
_ram_start = ORIGIN(RAM);
_ram_end = ORIGIN(RAM) + LENGTH(RAM);
_heap_start = _ebss; /* heap starts just after statically allocated memory */
_heap_end = _sstack;

/* add  */
/*
_flash_fs_start = ORIGIN(FLASH_FS);
_flash_fs_end   = ORIGIN(FLASH_FS) + LENGTH(FLASH_FS);
*/