# Declare constants used for creating a multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


# Set up stack
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KB
stack_top:


# Time to start the kernel!
.section .text
.global _start
.type _start, @function
_start:
	# Use our temporary stack
	# movl $stack_top, %esp
	
	# Try using arbitrary stack at 0x07ffffff.
	# This is (obviously) not optimal, but as the noob I am
	# I don't completely understand the memory stuff yet.
	# For now I'm just going to assume that the machine
	# has at least 128 MB of memory, putting the heap at
	# 64MB (growing upwards) and the stack at 128MB (downwards).
	# This area of memory should at least be free, provided it exists.
	movl $0x07ffffff, %esp
	
	# Let's go!
	call core_main

	# Infinite loop upon return.
	# We disable interrupts and then halt the CPU,
	# stopping it until it receives an interrupt (i.e., never).
	cli
	hlt

	# Just to be safe we enter an infinite loop, should
	# we continue anyway.
.Lhang:
	jmp .Lhang

# Set size of start (_start to here)
.size _start, . - _start

