;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Selection Sort
;;=============================================================
;;Name: Jade Law
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;x = 0;                         // current swapping index in the array
;;len = length of array;
;;while(x < len - 1) {
;;  z = x;                     // index of minimum value in unsorted portion of array
;;  y = x + 1;                 // current index in array
;;  while (y < len) {
;;      if (arr[y] < arr[z]) {
;;          z = y;             // update the index of the minimum value
;;      }
;;      y++;
;;  }
;;  if (z != x) {
;;      temp = arr[x];         // perform a swap
;;      arr[x] = arr[z];
;;      arr[z] = temp;
;;  }
;;      x++;
;;}
.orig x3000

LD R1, LENGTH 			;R1 = length of array
AND R0, R0, 0 			;x = 0
LD R6, ARRAY 			;R6 = ARRAY
;Temporary Registers: R2, R5

OUTLOOP 		NOT R0, R0
				ADD R0, R0, 1
				ADD R2, R1, R0 	;
				NOT R0, R0
				ADD R0, R0, 1
				ADD R2, R2, -1 	;R2 = length - 1
				BRN END 		;if (length - x  < 0), END
				ADD R3, R0, 0  ;z = x
				ADD R4, R0, 1	;y = x + 1
				NOT R5, R4
				ADD R5, R5, 1
				ADD R5, R5, R1
				BRP WHILE 		;go to WHILE if (length - y > 0)
				NOT R5, R3
				ADD R5, R5, 1
				ADD R5, R5, R3
				BRNP  SWAP
				BRZ OUTCONT


WHILE  			;BRZ END 		;if R5 == 0, end 			while (y < len)
				ADD R2, R6, R3
 				LDR R2, R2, 0	;R2 = array[z]
 				ADD R5, R6, R4
 				LDR R5, R5, 0	;R5 = array[y]
 				NOT R2, R2
 				ADD R2, R2, 1
 				ADD R2, R2, R5
 				BRN IF
 				BR WHILECONT
 		

IF 				AND R3, R3, 0
				ADD R3, R3, R4


WHILECONT 		ADD R4, R4, 1
				NOT R5, R4
				ADD R5, R5, 1
				ADD R5, R5, R1
 				BRP WHILE


SWAP 			NOT R3, R3
				ADD R3, R3, 1
				AND R2, R2, 0
				ADD R2, R3, R0
				BRZ OUTCONT
				NOT R3, R3
				ADD R3, R3, 1
				ADD R4, R6, R0	;R4 = x
				LDR R2, R4, 0 	;R2 = array[x]
				ADD R3, R6, R3	;R3 = z
				LDR R5, R3, 0 	;R5 = array[z]
				STR R2, R3, 0
				STR R5, R4, 0
				BR OUTCONT


OUTCONT 		ADD R0, R0, 1
				BR OUTLOOP


;;PUT YOUR CODE HERE

END 	HALT

ARRAY .fill x4000
LENGTH .fill 7
.end

.orig x4000
.fill 4
.fill 9
.fill 0
.fill 2
.fill 9
.fill 3
.fill 10
.end
