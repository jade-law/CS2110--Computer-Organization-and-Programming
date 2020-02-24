.orig x0000
;; immediate and
AND R0, R0, 0
AND R1, R1, 0
AND R2, R2, 0
AND R3, R3, 0
AND R4, R4, 0
AND R5, R5, 0
AND R6, R6, 0
AND R7, R7, 0

;; immediate add
ADD R1, R1, 7 ;;R1 = 7
ADD R2, R1, -2 ;;R2 = 5

;; register add
ADD R3, R2, R1 ;;R3 = 12

;; register and
AND R4, R2, R1 ;;R4 = 5

;;not
NOT R4, R4

;;random address calculation
ADD R6, R6, 15
ADD R6, R6, R6 ;; 30
ADD R6, R6, R6 ;; 60
ADD R6, R6, R6 ;; 120
ADD R6, R6, R6 ;; 240
ADD R6, R6, R6 ;; R6 = 480

;; str
STR R4, R6, 3 ;; mem[r6 + 3] <= R4
STR R3, R6, 2 ;; mem[r6 + 2] <= R3
STR R2, R6, 1 ;; mem[r6 + 1] <= R2
STR R1, R6, 0 ;; mem[r6 + 0] <= R1

BRnzp Continue

PTR
.FILL x0000
.FILL x0000

Continue
LEA R5, PTR ;; R5 = ADDR(PTR)
ADD R5, R5, 1 ;; R5 = ADDR(PTR) + 1
ST R5, PTR ;; MEM[ADDR(PTR)] <= ADDR(PTR) + 1
STI R6, PTR ;; MEM[MEM[ADDR(PTR)]] <= R6

;;CLEAR EVERYTHING EXCEPT R5
AND R0, R0, 0
AND R1, R1, 0
AND R2, R2, 0
AND R3, R3, 0
AND R4, R4, 0
AND R6, R6, 0
AND R7, R7, 0

LEA R5, SKIP

JMP R5

HALT
HALT
HALT

;;LD TESTS
SKIP
LDI R6, PTR
LDR R4, R6, 3 ;; mem[r6 + 3] => R4
LDR R3, R6, 2 ;; mem[r6 + 2] => R3
LDR R2, R6, 1 ;; mem[r6 + 1] => R2
LDR R1, R6, 0 ;; mem[r6 + 0] => R1

LD R0, SKIP ;; R0 <= VALUE FOR: LDI R6, PTR

;;HALT
HALT

;;END STATE
;;r0 = xADED
;;r1 = x0007
;;r2 = x0005
;;r3 = x000C
;;r4 = xFFFA
;;r5 = x002A
;;r6 = x01E0
;;r7 = x0000
.end
