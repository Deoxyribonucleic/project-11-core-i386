#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>
#include <math.h>

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

#endif
