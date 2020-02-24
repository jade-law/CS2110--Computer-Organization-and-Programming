.orig x0000

LD R1, MYLABEL
LDR R2, R1, 0
STR R2, R1, 1

LDR R3, R1, 1

HALT

MYLABEL .fill x3006

.fill x0005
.fill x0000

.end

;; R1: x0006, R2: x0005, R3: x0005
