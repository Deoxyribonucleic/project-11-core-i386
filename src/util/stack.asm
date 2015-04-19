.intel_syntax noprefix

.global stack_dump
.type stack_dump, @function
stack_dump:
	# stack frame
	push ebp
	mov ebp, esp
	add ebp, 8 # for pushed ebp and return address

	push ebx

	# eax: length
	mov ebx, [ebp]
	mov eax, esp

	.loop:
		add eax
		dec ebx
		test ebx, ebx
		jnz .loop

	# restore stack frame and return
	pop ebx
	pop ebp
	ret

