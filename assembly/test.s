.data
.balign 4
message1 : .asciz "type a number : "
.balign 4
message2 : .asciz "%d + %d = %d\n"
.balign 4
message3 : .asciz "%d * %d = %d\n"

.balign 4
scan_pattern : .asciz "%d"

.balign 4
number_read1 : .word 0

.balign 4
number_read2 : .word 0

.balign 4
return : .word 0
.balign 4
return2 : .word 0
.balign 4
return3 : .word 0

.text
add_u:
	ldr r2, addr_of_return2
	str lr, [r2]

	add r0, r0, r1
	
	ldr lr, addr_of_return2
	ldr lr, [lr]
	bx lr
addr_of_return2 : .word return2

mul_u:
	ldr r2, addr_of_return3
	str lr, [r2]
	mul r2, r0, r1
	mov r0, r2
	ldr lr, addr_of_return3
	ldr lr, [lr]
	bx lr
addr_of_return3 : .word return3

.global main
main:
	ldr r1, addr_of_return
	str lr, [r1]
	
	ldr r0, addr_of_msg1
	bl printf
	
	ldr r0, addr_of_scan_pattern
	ldr r1, addr_of_number_read1
	bl scanf
	
	ldr r1, addr_of_number_read1
	ldr r1, [r1]
	mov r5, r1

	ldr r0, addr_of_msg1
	bl printf
	
	ldr r0, addr_of_scan_pattern
	ldr r1, addr_of_number_read2
	bl scanf
	
	ldr r1, addr_of_number_read2
	ldr r1, [r1]
	mov r6, r1

	mov r0, r5
	mov r1, r6

	bl add_u
	mov r7, r0
	ldr r0, addr_of_msg2
	mov r1, r5
	mov r2, r6
	mov r3, r7

	bl printf

	mov r0, r5
	mov r1, r6

	bl mul_u

	mov r7, r0
	ldr r0, addr_of_msg3
	mov r1, r5
	mov r2, r6
	mov r3, r7

	bl printf

	ldr lr, addr_of_return
	ldr lr, [lr]
	bx lr

addr_of_msg1 : .word message1
addr_of_msg2 : .word message2
addr_of_msg3 : .word message3
addr_of_scan_pattern : .word scan_pattern
addr_of_number_read1 : .word number_read1
addr_of_number_read2 : .word number_read2
addr_of_return : .word return

.global printf
.global scanf
	
