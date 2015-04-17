#include "string.h"

#include "../terminal.h"


size_t strlen(const char* str)
{
	size_t len;
	for(len = 0; str[len] != 0; ++len);
	return len;
}

char* strcpy(char* dest, char const* src)
{
	size_t len = strlen(src);
	size_t i;
	for(i=0; i<=len; ++i)
		dest[i] = src[i];
	return dest;
}

char* itoa(int value, char* str, int base)
{
	if(base == 16)
	{
		int mask = 0xf << 28;
		size_t i;
		for(i=0; i<8; ++i)
		{ 
			str[i] = "0123456789abcdef"[((value & mask) >> 4 * (7 - i)) & 0xf];
			mask >>= 4;
		}
		str[i] = 0;
	}
	else
	{
		strcpy(str, "NOIMPL");
	}
	return str;
}

