;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here
; The Code above already had placed the frequency of each charecter into respective memory
;location. Now we must take those frequencies and print them to the console
; To do this for each charecter we must take the data from each memory location
; put it into R0 then extract 4 bits at a time. Then check if value is a number
;or a charecter, convert to its respective ascii then print. 
;Do this for all 27 categories of the histogram
		AND R0, R0,  #0
		AND R1, R1,  #0
		AND R2, R2,  #0
		AND R3, R3,  #0
		AND R4, R4,  #0
		AND R5, R5,  #0
		AND R6, R6,  #0
		AND R7, R7,  #0 ; All registers initialized

		LD R4, HIST_ADDR ; R4 is now has the location of the histogram
		ADD R2, R2, #4;bitshifts
		ADD R3, R3, #4;hexshifts
		

		LD R0, ROWS ;
		STI R0, ROW_LOC ; number of rows to memory

		LD R0, R_LET 
		STI R0, R_LOC
NEXT_ROW	LDI R0, R_LOC ; brings the AXIS ASCII into R0
		OUT
		ADD R0, R0, #1 ; increments the axis
		STI R0, R_LOC ; Incremented axis gets stored back at x3500

		LD R0, TAB
		OUT ; Prints a space before the numerical value gets printed

		

		AND R0, R0, #0 ; Set R0 to 0 so you can do the left shifting		

		LDR R1, R4, #0 ; R1 now has the numerical values of the frequencies


BIT_SHIFT 	ADD R0, R0, R0
		ADD R1, R1, #0
		BRzp SHIFT
		ADD R0, R0, #1
		SHIFT ADD R1, R1, R1
		ADD R2, R2, #-1
		BRnp BIT_SHIFT


		ADD R6, R0, #-10 ;checks if num or letter 

		BRzp FORWARD

		LD R5, DIGIT
		ADD R0, R0, R5
		OUT
		AND R2, R2, #0 
		AND R0, R0, #0 ; reset R0
		ADD R2, R2, #4 ; resetting the 4 bit shift
		ADD R3, R3, #-1 ; decrement hex shift
		BRp BIT_SHIFT ; branches only taken if more hex shifts are needed
		AND R3, R3, #0
		ADD R3, R3, #4; resets hex shift
		LD R0, NEW_LINE ; after 4 hex shifts go new line for next char
		OUT
		ADD R4, R4, #1 ;columb pts to next
		LDI R0, ROW_LOC ;row num into r0
		ADD R0, R0, #-1
		STI R0, ROW_LOC ;row num back to memory
		ADD R0, R0, #0
		BRp NEXT_ROW
		BRnzp DONE




FORWARD		LD R5, LETTER
		ADD R0, R0, R5
		OUT
		AND R2, R2, #0 
		AND R0, R0, #0 ; reset R0 for next
		ADD R2, R2, #4 ; resetting the 4 bit shift
		ADD R3, R3, #-1 ; decrement hex shift
		BRp BIT_SHIFT ; branch is only taken if we have more hex shifts left
		AND R3, R3, #0
		ADD R3, R3, #4 ; resets hex shift
		LD R0, NEW_LINE ;after 4 hex shifts go new line for next char
		OUT
		ADD R4, R4, #1 ;coulmn points to next
		LDI R0, ROW_LOC
		ADD R0, R0, #-1
		STI R0, ROW_LOC ;row num back to mem
ADD R0, R0, #0
BRp NEXT_ROW


; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program
	NUM_BINS	.FILL #27	; 27 loop iterations
	NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
	AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
	AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
	HIST_ADDR	.FILL x3F00     ; histogram starting address
	STR_START	.FILL x4000	; string starting address
	NEW_LINE 	.FILL xA ; ASCII for  next line
	R_LET 		.FILL x40 ;ascii of at
	R_LOC 		.FILL x3500 ; where the ascii of the label of histogram is stored
	TAB		.FILL x20 ;ascii of a space
	ROWS 		.FILL x1B ; #27 rows
	DIGIT 		.FILL x30 ;#48 add to a number ascii
	LETTER		.FILL x37 ; #55 add to a letter ascii
	ROW_LOC 	.FILL x3501 ; where the row count is stored



; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END