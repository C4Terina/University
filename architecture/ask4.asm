.data 

msg: .asciiz "Enter a string: "
str: .space 17


.text

main:


   li $v0,4
   la $a0,msg
   syscall
   la $a0, msg 
   li $v0, 8
   la $a0,str
   li $a1, 17
   syscall

    la    $s0, str    # $s0 contains base address of str
    add    $s2, $zero, $zero   # $s2 = 0
    addi    $s3, $0, '\n'    # $s2 = '\n'
loop:
    lb    $s1, 0($s0)    # load character into $s0
    beq    $s1, $s3, end    # Break if byte is newline
    addi    $s2, $s2, 1    # i = i+1
    addi    $s0, $s0, 1    # increase str address
    j    loop
end:
    sb    $zero, 0($s0)    #replace newline with 0

    li    $v0, 1        # Load 1=print_int into $v0
    add    $a0, $s2, $zero    # Load first number into $a0
    syscall        



li $v0, 10
syscall