#include "memory.h"

#include "terminal.h"
#include "util/mini-printf.h"

#include <stdbool.h>
#include <string.h>

#define NEW_BLOCK_THRESHOLD 4



struct mem_block
{
	struct mem_block* next;
	struct mem_block* prev;
	bool free;
};


/* completely arbitrary and probably crash-prone; see
 * boot.asm for more details */
static void* heap_start = (void*)0x04000000;
static void* heap_end   = (void*)0x06000000;
static struct mem_block* first_block;
static struct mem_block* last_block;


void mem_init()
{
	// initialize block pointers
	first_block = (struct mem_block*)heap_start;
	last_block = (struct mem_block*)(heap_end - sizeof(struct mem_block));

	// initialize block meta data
	first_block->next = last_block;
	first_block->prev = NULL;
	first_block->free = true;
	last_block->prev = first_block;
	last_block->next = NULL;
	last_block->free = false;

	// print fancy message
	//term_write("[mem] heap initialized at: 0x");
	printf("[mem] heap initialized at %08x, block control size %d\n", heap_start, sizeof(struct mem_block));
}

size_t get_block_size(struct mem_block const* block)
{
	return (void*)block->next - (void*)block - sizeof(struct mem_block);
}

void try_insert_block(struct mem_block* block, size_t size)
{
	// if there's a reasonable amount of space left between the end
	// of our newly allocated memory and the next block,
	// then create a new end block and put it into the linked list
	if(get_block_size(block) - sizeof(struct mem_block) - NEW_BLOCK_THRESHOLD > size)
	{
		struct mem_block* new_end = (void*)block + sizeof(struct mem_block) + size;
		new_end->next = block->next;
		block->next->prev = new_end;
		block->next = new_end;
		new_end->prev = block;
		new_end->free = true;
		printf("[mem] new end block %08x\n", new_end);
	}
}

void* mem_alloc(size_t size)
{
	printf("[mem] allocating %x bytes\n", size);
	struct mem_block* block = first_block;

	// walk through the linked list until we find
	// a block that is (a) free and (b) large enough,
	// or until we get next == NULL
	while(true)
	{
		// if we're at the end of the heap
		// we couldn't find an appropriate block
		// and we are out of memory
		if(block->next == NULL)
		{
			printf("[mem] out of memory: couldn't allocate %x bytes\n", size);
			return NULL;
		}

		printf("[mem] block size (%08x): %x bytes\n", block, get_block_size(block));

		// if the block is free and is large enough, break
		// and allocate it
		if(block->free && get_block_size(block) >= size)
			break;

		block = block->next;
	}

	//printf("[mem] block of size %x bytes found at %08x\n", get_block_size(block), block);

	// we found a block! let's allocate it.
	block->free = false;
	try_insert_block(block, size);
	
	
	printf("[mem] returning start of allocated memory %08x\n", (void*)block + sizeof(struct mem_block));
	return (void*)block + sizeof(struct mem_block);
}

// returns the previous block if merged backwards,
// otherwise returns block in arguments
struct mem_block* try_merge(struct mem_block* block)
{
	// if the next block is also free, merge them
	if(block->next->free)
	{
		printf("[mem] merging blocks %08x (%x bytes) with next %08x (%x bytes)\n", block, get_block_size(block), block->next, get_block_size(block->next));
		// next->next is safe because addr should never point to the last
		// block and the last block is never free
		block->next->next->prev = block;
		block->next = block->next->next;
		printf("[mem] new block size for %08x: %x bytes\n", block, get_block_size(block));
	}
	
	// if we're not in the first block, and the previous block is free,
	// merge them
	if(block->prev != NULL && block->prev->free)
	{
		printf("[mem] merging blocks %08x (%x bytes) with prev %08x (%x bytes)\n", block, get_block_size(block), block->prev, get_block_size(block->prev));
		block->prev->next = block->next;
		block->next->prev = block->prev;
		printf("[mem] new block size for %08x: %x bytes\n", block->prev, get_block_size(block->prev));
		return block->prev;
	}

	return block;
}

void* mem_realloc(void* addr, size_t size)
{
	/* We completely trust the caller about this one, but oh well... */

	// the address the allocator retuns lies immediately after the control
	// information, so subtract the size of it to arrive at the start
	struct mem_block* block = addr - sizeof(struct mem_block);
	printf("[mem] reallocating %08x (%x bytes) to %x bytes\n", block, get_block_size(block), size);
	
	// if the requested size is greater than the currently allocated one
	if(size > get_block_size(block))
	{
		size_t oldsize = get_block_size(block);
		
		// attempt merging with adjacent empty blocks and see if result is
		// of sufficient size
		block = try_merge(block);
		block->free = false;
		if(get_block_size(block) >= size)
		{
			// if it is, move content to start of new block
			memmove((void*)block + sizeof(struct mem_block), addr, oldsize);
			printf("[mem] returning start of merged reallocated memory %08x\n", (void*)block + sizeof(struct mem_block));
			return (void*)block + sizeof(struct mem_block);
		}
		else
		{
			void* oldaddr = addr;
			// otherwise we have to allocate an entirely new block
			addr = mem_alloc(size);
			if(addr == NULL)
				return NULL;

			// if we got a new block, copy data over and free this one
			printf("[mem] moving realloced memory %08x --> %08x (%x bytes)\n", oldaddr, addr, oldsize);
			memmove(addr, oldaddr, oldsize);
			mem_free(oldaddr);

			return addr;
		}
	}
	else
	{
		// if the requested size is smaller,
		// simply attempt inserting a free block in the free part of this
		// block
		try_insert_block(block, size);
		printf("[mem] returning start of shrunken reallocated memory %08x\n", (void*)block + sizeof(struct mem_block));
		return (void*)block + sizeof(struct mem_block);
	}
	return NULL;
}

void mem_free(void* addr)
{
	/* We completely trust the caller about this one, but oh well... */

	// the address the allocator retuns lies immediately after the control
	// information, so subtract the size of it to arrive at the start
	struct mem_block* block = addr - sizeof(struct mem_block);
	printf("[mem] freeing %08x (%x bytes)\n", block, get_block_size(block));
	
	// mark our block as free
	block->free = true;

	try_merge(block);
}

