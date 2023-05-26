.data

msg: .asciiz "*"

.text
.globl main
   
   main:
      
       li $v0, 5
       syscall
       move $t0, $v0
       
       
      li $s3, 0
      again: 
      beq $s3, $t0, exit
      la $a0, msg
      addi $s3, $s3, 1
      j again
      
       
       exit:
         li $v0, 10
          syscall
         

