;; DO NOT WORRY ABOUT THE CODE BELOW (except for the checkpoint labels)
.orig x3000

HALT ; DO NOT REMOVE

STACK .fill xF000 ; NEEDED BY COMPLx, DO NOT REMOVE

HEAD  .fill x4000
EXP   .fill 2    ;exp

; Labels for checkpoints
; DO NOT MODIFY
FIRSTNODE .blkw 1 ; Checkpoint 1
FINISHEDSUM .blkw 1 ; Checkpoint 3

;; DO NOT WORRY ABOUT THE CODE ABOVE (except for the checkpoint labels)



; START OF SUM POWERS
sumPowers
; !!!!! WRITE YOUR CODE FOR THE TIMED LAB HERE !!!!!
ADD R6, R6, -4          ;make room for return value, return address, old frame pointer, and 1 local
STR R7, R6, 2           ;save return address in the space we made it
STR R5, R6, 1           ;save R5 in space for the old frame pointer
ADD R5, R6, 0           ;save R5 to the frame pointer of the activation record
ADD R6, R6, -5          ;make room for saving registers
STR R0, R5, -1          ;save R0
STR R1, R5, -2          ;save R1
STR R2, R5, -3          ;save R2
STR R3, R5, -4          ;save R3
STR R4, R5, -5          ;save R0

LDR R0, R5, 4           ;R0 = address for head
ST R0, FIRSTNODE
LDR R1, R5, 5           ;R1 = int exp
LDR R2, R5, 6           ;R2 = func

WHILE   ADD R0, R0, 0
        BRz ENDWHILE
        LDR R4, R0, 1
        ADD R6, R6, -2
        STR R4, R6, 0
        STR R1, R6, 1
        JSR pow
        LDR R4, R6, 0
        LD R3, FINISHEDSUM
        ADD R4, R3, R4
        ST R4, FINISHEDSUM
        LDR R0, R0, 0
        BRz ENDWHILE
        BR WHILE


ENDWHILE    ADD R6, R6, -1
            STR R4, R6, 0
            JSRR R2
            LDR R4, R6, 0
            STR R4, R5, 3

TEAR    LDR R4, R5, -5      ;Restore R0
        LDR R3, R5, -4      ;Restore R1
        LDR R2, R5, -3      ;Restore R2
        LDR R1, R5, -2      ;Restore R3
        LDR R0, R5, -1      ;Restore R4
        ADD R6, R5, 0       ;Reset stack pointer to frame pointer (R6 = R5)
        LDR R5, R6, 1       ;Restore old frame pointer to R5
        LDR R7, R6, 2       ;Restore return address to R7
        ADD R6, R6, 3       ;Reallocate space for local, old frame pointer and return address
        RET
; END SUM POWERS




; ====== HELPER SUBROUTINES ======
; pow
; multBy10
; isEven
; DO NOT MODIFY

; START POW SUBROUTINE
pow
.fill x1DBC
.fill x7F82
.fill x7B81
.fill x1BA0
.fill x1DBB
.fill x7980
.fill x7781
.fill x7582
.fill x7383
.fill x7184
.fill x6144
.fill x6345
.fill x1420

POWLOOP
.fill x18A0
.fill x127F
.fill x0406
.fill x1620

MULTLOOP
.fill x16FF
.fill x0402
.fill x1484
.fill x0FFC

DONEMULT
.fill x0FF7

DONEPOW
.fill x7543
.fill x6184
.fill x6383
.fill x6582
.fill x6781
.fill x6980
.fill x1D60
.fill x6B81
.fill x6F82
.fill x1DA3
.fill xC1C0
; END POW SUBROUTINE

; START MULT BY 10
multBy10
.fill x1DBC
.fill x7F82
.fill x7B81
.fill x1BA0
.fill x1DBB
.fill x7980
.fill x7781
.fill x7582
.fill x7383
.fill x7184
.fill x6144
.fill x1220
.fill x1000
.fill x1000
.fill x1000
.fill x1001
.fill x1001
.fill x7143
.fill x6184
.fill x6383
.fill x6582
.fill x6781
.fill x6980
.fill x1D60
.fill x6B81
.fill x6F82
.fill x1DA3
.fill xC1C0

isEven
.fill x1DBC
.fill x7F82
.fill x7B81
.fill x1BA0
.fill x1DBB
.fill x7980
.fill x7781
.fill x7582
.fill x7383
.fill x7184
.fill x6144
.fill x5021
.fill x0402
.fill x103F
.fill x0E01

EVEN
.fill x1021

END
.fill x7143
.fill x6184
.fill x6383
.fill x6582
.fill x6781
.fill x6980
.fill x1D60
.fill x6B81
.fill x6F82
.fill x1DA3
.fill xC1C0
.end

; NODES FOR TESTING
.orig x4000
.fill x4008
.fill 5
.end

.orig x4008
.fill x0
.fill 12
.end
