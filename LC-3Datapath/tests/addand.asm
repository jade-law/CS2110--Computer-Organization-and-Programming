.orig x0000

AND R1, R1, 0
AND R2, R2, 0

ADD R1, R1, 5
ADD R2, R2, -4

AND R3, R1, R2

ADD R4, R2, R1

HALT

.end

;; R1: x0005, R2: xfffc, R3: x0004, R4: x0001
