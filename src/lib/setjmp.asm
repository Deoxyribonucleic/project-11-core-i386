.intel_syntax noprefix

.global setjmp
.type setjmp, @function
setjmp:
	# jmp setjmp
	# movl 4(%esp), %eax
	mov eax, [esp + 4]
	mov byte ptr [eax], 2 
	mov eax, [eax]
	# mov dword ptr [eax], 0xabcdef00
	# movl %esp, (%eax)
	# movl $0, %eax
	#mov eax, 0
	# leave
	ret

.size setjmp, .-setjmp

