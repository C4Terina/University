.data
msg: .asciiz "Positive"
msg2: .asciiz "Non Positive"
n: .word 0
.text
.globl main
main: 

la $t0, n
li $v0, 5 #????? ??? ?????? 
syscall
move $t0, $v0
bgez $t0, L1

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