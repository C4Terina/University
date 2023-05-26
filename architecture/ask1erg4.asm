.data 
.data
msg: .asciiz "ZERO"
msg2: .asciiz "NON ZERO"
n: .word 0
.text
.globl main
main: 

la $t0, n
li $v0, 5 #????? ??? ?????? 
syscall
move $t0, $v0
beq $t0, $zero, L1

li $v0, 4
la $a0, msg2
syscall

j L2

L1:
li $v0, 4
la $a0, msg
syscall

L2:
li $v0, 10
syscall 