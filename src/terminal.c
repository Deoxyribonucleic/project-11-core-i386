#include "terminal.h"

#include <stddef.h>
#include <stdint.h>

#include <string.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_START (uint16_t*)0xB8000

static uint16_t* vga_start;
static size_t cursor;
static uint8_t color;


void term_init()
{
	vga_start = VGA_START;

	size_t offset;
	for(offset = 0; offset < VGA_WIDTH * VGA_HEIGHT + VGA_WIDTH; ++offset)
	{
		vga_start[offset] = 0x0700;
	}

	cursor = 0;
	color = COLOR_LIGHT_GREY;
}

void term_putch(char c)
{
	if (c == '\n')
	{
		// if we're on last row, scroll text
		// and only reset X
		if(term_getcury() == VGA_HEIGHT - 1)
		{
			term_setcur(0, term_getcury());
			memmove(vga_start, (void*)vga_start + VGA_WIDTH * 2, VGA_HEIGHT * VGA_WIDTH * 2);
		}
		else
		{
			term_setcur(0, term_getcury() + 1);
		}
	}
	else
	{
		vga_start[cursor++] = (color << 8) | c;
	}
}

void term_write(char const* str)
{
	size_t i, len = strlen(str);
	for(i=0; i<len; ++i)
	{
		term_putch(str[i]);
	}
}

void term_setcur(size_t x, size_t y)
{
	cursor = y * VGA_WIDTH + x;
}

size_t term_getcurx()
{
	return cursor % VGA_WIDTH;
}

size_t term_getcury()
{
	return cursor / VGA_WIDTH;
}

size_t term_getwidth()
{
	return VGA_WIDTH;
}

size_t term_getheight()
{
	return VGA_HEIGHT;
}

void term_setcolor(uint8_t clr)
{
	color = clr;
}

