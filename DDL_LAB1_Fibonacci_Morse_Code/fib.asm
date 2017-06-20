 .global fib
fib:
	push {lr}
case_0:
	cmp r0, #0
	bgt case_1
	mov r0, #0
	pop {pc}
case_1:
	cmp r0, #1
	bgt recurse
	mov r0, #1
	pop {pc}
recurse:
	push {r0}
	sub r0, r0, #1
	bl fib
	mov r1, r0
	pop {r0}
	push {r1}
	sub r0, r0, #2
	bl fib
	pop {r1}
	add r0, r0, r1
	pop {pc}
