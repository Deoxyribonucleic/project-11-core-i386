#include "string.h"


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

