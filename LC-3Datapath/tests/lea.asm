.orig x0000

AND R1, R1, 0
ADD R1, R1, -1 ; CC = n
LEA R2, MYLABEL ; CC = p
BRp SKIP
AND R1, R1, 0
SKIP
HALT

MYLABEL .fill 0

.end

;; R1 = -1, R2 = 6, CC = p
