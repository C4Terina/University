.data
i: .word 0
message: .asciiz "* \n"
.text
.globl main
main:

       li $v0, 5
       syscall
       move $s2, $v0
       li $v0, 5
       syscall
       move $s5,$v0
       
       subi $s5,$s5,1
       while:
         
           #{ 
           
           beq  $t0,$s2, exit
        #{
        while2:
        beq  $t1,$s5, next
        li $v0, 11
        la $a0, '*'
        syscall
        addi $t1, $t1, 1
        j while2
        #}
        next:
        li $v0, 4
        la $a0, message
        syscall
            addi $t0, $t0, 1  #  i++
            li $t1,0
            #}
            j while
            
       
       exit:
       
         li $v0, 10
          syscall
          