#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* check if the compiler thinks if we are targeting the wrong operating system */
#if defined(__linux__)
#error "You are not using a cross-compiler. Please use i686-elf-gcc."
#endif

/* same, but make sure we're building for 32 bit for i686 */
#if defined(__linux__)
#error "You are not using a 32-bit i686 compiler. Please use i686-elf-gcc."
#endif

void core_main()
{
	/* put an A in the top-left corner to show we've booted */
	*((uint8_t*)0xb8000) = 'A'; 
	return;
}

