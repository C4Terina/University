 .data
    result: .asciiz "The sum is: "
    err: .asciiz "Error. Sum above 9"
.text
.globl main

main:
    # Read the first integer
    li $v0, 5
    syscall
    move $s0, $v0  # Store it in $s0

    # Read the second integer
    li $v0, 5
    syscall
    move $s1, $v0  # Store it in $s1

    # Compute the sum
    add $t0, $s0, $s1

    # Check if the sum is above 9
    li $t1, 9
    ble $t0, $t1, sum_below_9  # Branch if sum <= 9

    # Print out the error if sum is above 9
    li $v0, 4
    la $a0, err
    syscall
    li $v0, 10
    syscall

sum_below_9:
    # Print the result
    li $v0, 4
    la $a0, result
    syscall

    # Print the sum
    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 10
    syscall
