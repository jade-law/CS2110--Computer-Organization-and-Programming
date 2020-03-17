;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Print the Vowels in a String
;;=============================================================
;;Name: Jade Law
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;string = "TWENTY ONE TEN";
;;i = 0;
;;while(string[i] != ’\0’){
;;  if(string[i] == ’A’ || string[i] == ’E’ ||
;;  string[i] == ’I’ || string[i] == ’O’ ||
;;  string[i] == ’U’){
;;      print(string[i]);
;;  }
;;i++;
;;}
.orig x3000

	;;INSERT CODE AT THIS LOCATION

LD R2, A 				;R2 = A in ASCII
NOT R2, R2
ADD R2, R2, 1
AND R3, R3, 0
LD R1, STRING       	;R1 = Address for index 0 of string
LDR R0, R1, 0			;R0 = character at index R1 of string
WHILE   BRZ END 		;End if R0 is null (0)
		AND R3, R3, 0
		ADD R3, R0, R2  ;if R0 == 'A'
		BRZ PRINT 		;print R0
		ADD R2, R2, -4
		AND R3, R3, 0
		ADD R3, R0, R2	;if R0 == 'E'
		BRZ PRINT 		;print R0
		ADD R2, R2, -4
		AND R3, R3, 0
		ADD R3, R0, R2	;if R0 == 'I'
		BRZ PRINT 		;print R0
		ADD R2, R2, -6
		AND R3, R3, 0
		ADD R3, R0, R2	;if R0 == 'O'
		BRZ PRINT 		;print R0
		ADD R2, R2, -6
		AND R3, R3, 0
		ADD R3, R0, R2	;if R0 == 'U'
		BRZ PRINT 		;print R0
		BR CONT		;else continue


CONT	ADD R1, R1, 1
		AND R3, R3, 0
		LD R2, A
		NOT R2, R2
		ADD R2, R2, 1
		LDR R0, R1, 0
		BR WHILE

PRINT 	OUT
		BR CONT







END     HALT

A .fill x41    ;; A in ASII
STRING .fill x4000
.end

.orig x4000
.stringz "TWENTY ONE TEN"
.end
