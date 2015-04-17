#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* check if the compiler thinks if we are targeting the wrong operating system */
#if defined(__linux__)
#error "You are not using a cross-compiler. Please use i686-elf-gcc."
#endif

/* same, but make sure we're building for 32 bit for i386 */
#if defined(__linux__)
#error "You are not using a 32-bit x86 compiler. Please use i686-elf-gcc."
#endif

#include "terminal.h"
#include "lib/string.h"


void core_main()
{
	char* message1 = "Project";
	char* message2 = "\xb3 \xb3";
	term_init();
	term_setcolor(COLOR_LIGHT_GREY);
	term_setcur(term_getwidth() / 2 - strlen(message1) / 2, term_getheight() / 2 - 2);
	term_write(message1);
	term_setcolor(COLOR_BLUE);
	term_setcur(term_getwidth() / 2 - strlen(message2) / 2, term_getheight() / 2);
	term_write(message2);
	term_setcur(term_getwidth() / 2 - strlen(message2) / 2, term_getheight() / 2 + 1);
	term_write(message2);
	return;
}

