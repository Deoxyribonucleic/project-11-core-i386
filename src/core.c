#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* check if the compiler thinks if we are targeting the wrong operating system */
#if defined(__linux__)
#error "You are not using a cross-compiler. Please use i686-elf-gcc."
#endif

/* same, but make sure we're building for 32 bit for i386 */
// #if defined(__i386__)
// #error "You are not using a 32-bit x86 compiler. Please use i686-elf-gcc."
// #endif

#include "terminal.h"
#include "memory.h"
#include <string.h>
#include <stdio.h>


void core_main()
{
	char* message1 = "Project";
	char* message2 = "\xb3 \xb3";
	term_init();
	term_setcolor(COLOR_DARK_GREY);
	term_setcur(term_getwidth() - strlen(message1) - 2, 1);
	term_write(message1);
	term_setcolor(COLOR_BLUE);
	term_setcur(term_getwidth() - strlen(message1) / 2 - strlen(message2) / 2 - 3, 2);
	term_write(message2);
	term_setcur(term_getwidth() - strlen(message1) / 2 - strlen(message2) / 2 - 3, 3);
	term_write(message2);
	term_setcur(0, 0);
	term_setcolor(COLOR_LIGHT_GREY);

	mem_init();
	
	void* block1 = mem_alloc(0x10000);
	void* block2 = mem_alloc(0x10000);
	mem_free(block1);
	void* block3 = mem_alloc(0x10000);
	block3 = mem_realloc(block3, 0x5000);
	block3 = mem_realloc(block3, 0x15000);
	void* block4 = mem_alloc(0x10000);
	mem_free(block2);
	mem_free(block4);
	
	return;
}

