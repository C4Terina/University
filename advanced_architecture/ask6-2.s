.data
    err: .asciiz "Error. Sum above 9"
.text
.globl main

main:
    # Read first integer
    lui $t0, 0xffff # ffff0000
    Wait: lw $t1, 0($t0) # Θύρα Κατάστασης
    andi $t1,$t1,0x1
    beq $t1,$zero, Wait
    lw $s0, 4($t0) # Θύρα Δεδομένων
    sub $s0, $s0,  0x30

    # Read second  integer
    lui $t0, 0xffff # ffff0000
    Wait2: lw $t1, 0($t0) # Θύρα Κατάστασης
    andi $t1,$t1,0x1
    beq $t1,$zero, Wait2
    lw $s1, 4($t0) # Θύρα Δεδομένων
    sub $s1, $s1,  0x30

    add $s3, $s0, $s1
    #sub $s3, $s3,  0x30

    li $s4, 9
    ble $s3, $s4, sum_below_9  # Branch if sum <= 9

    # Print out the error if sum is above 9
    li $v0, 4
    la $a0, err
    syscall
    li $v0, 10
    syscall


sum_below_9:
    lui $t0, 0xffff # ffff0000
    Wait3:
        lw $t1, 8($t0) # Θύρα Κατάστασης
        andi $t1,$t1,0x1
        beq $t1,$zero, Wait3
        sw $s3,12($t0)
        nop
        nop
        nop
        nop
