.data 0x10000480
Array_A: .word 1,1,1,1,2,2,2,2
.data 0x10000CC0
Array_B: .word 3,3,3,3,4,4,4,4
.text
li $8, 5
ext_loop: la $2, Array_A
la $3, Array_B
li $6, 0
li $4, 8
loop: lw $5, 0($2)
lw $7, 0($3)
add $6, $6,$5
add $6, $6,$7
addi $2,$2,4
addi $3, $3,4
addi $4,$4,-1
bgt $4,$0,loop
addi $8, $8, -1
bgt $8, $0, ext_loop
.end
