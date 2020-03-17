;;=======================================
;; CS 2110 - Spring 2019
;; HW6 - Recursive Multiplication
;;=======================================
;; Name: Jade Law
;;=======================================

;; In this file, you must implement the 'mult' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'mult' label.


.orig x3000
HALT

mult
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of mult: integer a, integer b
;;
;; Psuedocode:
;; mult(int a, int b) {
;;     if (a == 0 || b == 0) {
;;         return 0;
;;     }
;;	
;;     // Since one number might be negative, we will only decrement the larger number.
;;     // This ensures that one parameter will eventually become zero.
;;     if (a > b) {
;;         var result = b + mult(a - 1, b);
;;         return result;
;;     } else {
;;         var result = a + mult(a, b - 1);
;;         return result;
;;     }
;; }


;; IMPORTANT NOTE: we recommend following the pseudocode exactly. Part of the autograder checks that your implementation is recursive.
;; This means that your implementation might fail this test if, when calculating mult(6,4), you recursively calculated mult(6,3) instead of mult(5,4).
;; In particular, make sure that if a == b, you calculate mult(a,b-1) and not mult(a-1,b), as the psuedocode says.
;; If you fail a test that expects you to calculate mult(5,4) and you instead calculated mult(4,5), try switching the arguments around when recursively calling mult.


;; YOUR CODE HERE
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

;get a and b
LDR R1, R5, 5           ;Pop B off stack and into R1
LDR R0, R5, 4           ;Pop A off stack and into R0

BRz     IF1             ;if a == 0
ADD R1, R1, 0
BRz     IF1             ;if b == 0
BRnp    COMPARE         ;else move on
IF1     AND R3, R3, 0
        STR R3, R5, 3   ;0 stored on stack
        BR TEAR

COMPARE NOT R2, R1
        ADD R2, R2, 1   ;R2 = -b
        ADD R3, R0, R2  ;R3 = a - b
        BRp IF2         ;if (a > b)
        BR  IF3


IF2     ADD R0, R0, -1
        ADD R6, R6, -2
        STR R0, R6, 0
        STR R1, R6, 1
        JSR mult
        LDR R2, R6, 0   ;R2 = mult(a-1,b)
        ADD R2, R2, R1
        STR R2, R5, 3
        BR TEAR

IF3     ADD R1, R1, -1
        ADD R6, R6, -2
        STR R0, R6, 0
        STR R1, R6, 1
        JSR mult
        LDR R2, R6, 0   ;R2 = mult(a,b-1)
        ADD R2, R2, R0
        STR R2, R5, 3

;stack teardown and return
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

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
