;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Iterative Multiplication
;;=============================================================
;;Name: Jade Law
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;a = (argument 1);
;;b = (argument 2);
;;ANSWER = 0;
;;while (b > 0) {
;;  ANSWER = ANSWER + a;
;;  b--;
;; }
;; note: when the while-loop ends, the value stored at ANSWER is a times b.

.orig x3000

    ;;YOUR CODE GOES HERE


LD R3, A 					;R3 = A
AND R2, R2, #0				;R2 = 0
LD R1, B 					;R1 = B

WHILE  	BRZ END 			;if (b == 0) stop
		ADD R2, R3, R2		;R2 = R3 + R2
		ADD R1, R1, #-1 	;R1--
       	BRP WHILE 			;Repeat while R1 > 0
ST R2, ANSWER
END 	HALT

A   .fill 5
B   .fill 15

ANSWER .blkw 1

.end