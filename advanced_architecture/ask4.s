.data 0x10000480
Array_A: .word 1, 1, 1, 1, 2, 2, 2, 2
.data 0x10000CC2
Array_B: .word 3, 3, 3, 3, 4, 4, 4, 4
.text
la $2, Array_A
li $6,0
li $4,8
loop:
lw $5,0($2)
add $6,$6,$5
addi $2,$2,4
addi $4,$4,-1
bgt $4,$0,loop
