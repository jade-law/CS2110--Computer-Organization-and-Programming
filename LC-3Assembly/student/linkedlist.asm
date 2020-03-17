;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Make elements of a Linked List into a string
;;=============================================================
;;Name: Jade Law
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;length = LL.length;
;;curr = LL.head; //HINT: What can an LDI instruction be used for?
;;ANSWER = char[length]; //This character array will already be setup for you
;;i = 0;
;;while (curr != null) {
;;  ANSWER[i] = curr.value;
;;  curr = curr.next;
;;  i++;
;;}


.orig x3000

LD R0, ANSWER       	;R0 = start of string
LDI R1, LL 				;R1 = adress of head node
LD R2, LL
LDR R2, R2, 1


WHILE   BRZ END 		;if R2 == 0, end
		LDR R4, R1, 0
		LDR R3, R1, 1 	;R3 = value at node R1
		STR R3, R0, 0	;R0 = R3.value
		LDR R1, R1, 0
		ADD R0, R0, 1	;i++ (for string)
		ADD R2, R2, -1	;length--
		BRP WHILE


;; YOUR CODE GOES HERE

END     AND R4, R4, 0
		STR R4, R0, 0
		HALT

LL .fill x6000
ANSWER .fill x5000
.end

.orig x4000
.fill x4008
.fill 98
.fill x400A
.fill 73
.fill x4002
.fill 103
.fill x0000 
.fill 114
.fill x4004
.fill 97
.fill x4006
.fill 116
.end

.orig x5000
.blkw 7
.end

.orig x6000
.fill x4000
.fill 6
.end
