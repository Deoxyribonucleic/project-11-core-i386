#include "stack.h"

#include <stdint.h>

int stack_dump(size_t length, ...)
{
	uint32_t stack[0];
	printf("dumping %d dwords of stack at %08x", length, stack);
	
	int offset = 0;
	for(;offset < length; ++offset)
	{
		if(offset % 4 == 0)
			printf("\n%08x:", stack + offset);
		printf(" %08x", stack[offset]);
	}
	printf("\n");

	return length;
}

