.data
arr: .word 1, 15, 0, -3, 99, 48, -17, -9, 20, 15

.text
.globl main
main:

add $t0, $zero, $zero   #counter i
add $t1, $zero, $zero   #sum

la  $t2, arr

loop:
slti    $t3, $t0, 10        #i<10
beq $t3, $zero, EXIT

lw  $t4, ($t2)  #$t4 = arr[i]
addi    $t2, $t2, 4

add $t1, $t1, $t4   #sum = sum + arr[i]

addi    $t0, $t0, 1 #i++
j loop
EXIT:

add $a0, $zero, $t1     #moving the sum to $a0 register for printing

li  $v0, 1
syscall

li  $v0, 10
syscall