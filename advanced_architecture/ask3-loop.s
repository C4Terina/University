.data
array: .word 1, 2, 3, 4, 5, 6, 7,8
result: .word 0
.code
daddi r1, r0, array
daddi r2, r0,8
daddi r3, r0,0
loop: lw r4, 0(r1)
lw r6, 8(r1)
dmul r5, r4, r4
dmul r7, r6, r6
dadd r3, r3, r5
dadd r8, r8, r7
daddi r1, r1, 8
daddi r2, r2, -2
bnez r2, loop
sw r3, result(r0)
halt

