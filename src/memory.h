#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stddef.h>
#include <stdint.h>

void mem_init();
void* mem_alloc(size_t size);
void* mem_realloc(void* addr, size_t size);
void mem_free(void* addr);

#endif // _MEMORY_H_
