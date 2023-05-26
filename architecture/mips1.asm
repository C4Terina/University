.data 
	str: .byte '*'
.text
.globl main

main: 


li $v0, 5
syscall
move $t0, $v0

li $v0, 5
syscall
move $t1, $v0

addi $s2, $zero, 0 # i = 0
addi $s3, $zero, 0 # j = 0 

jump2: bne $s2, $t0, jump

      j exit
  
   jump:
    li $v0, 4
    la $a0, str
    syscall
    addi $s2, $s2, 1
    bne $s3, $t1 , jump3
    
    jump3: 
    li $v0, 4
    la $a0, str
    syscall
    addi $s3, $s3, 1
    
    j jump2 
   
   
   exit:
   li $v0, 10
   syscall 
