.data
.balign 4
message1 : .asciz "Hello world"

.balign 4
message2 : .asciz "Type a number: "

.balign 4
scan_pattern : .asciz "%d"

.balign 4
number_read : .word 0

.balign 4
return : .word 0

.text
.global main
main:
	ldr r1, addr_of_return
	str lr, [r1]

	ldr r0, addr_of_msg2
	bl puts

	ldr r0, addr_of_scan_pattern
	ldr r1, addr_of_number_read
	bl scanf

	ldr r1, addr_of_number_read
	ldr r1, [r1]
	mov r5, r1
	mov r6, #0
loop:
	cmp r6, r5 
	bge end
	add r6, r6, #1 
	ldr r0, addr_of_msg1
	bl printf
	b loop
end:
	ldr r1, addr_of_return
	ldr lr, [r1]
	bx lr 

addr_of_return : .word return
addr_of_msg1 : .word message1
addr_of_msg2 : .word message2
addr_of_scan_pattern : .word scan_pattern
addr_of_number_read : .word number_read

.global printf
.global scanf
.global puts
