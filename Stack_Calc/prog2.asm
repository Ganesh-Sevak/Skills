
;  In the MP we were tasked to make a calculator using SUBROUTINES
;My program gets input and echos via GETC and OUT. The we check what the actual input is. If 
;its a number then push the value of the number on the stack
; if its a operator pop, twice then evaluate the expression then push the result back on the stack.
;once an equal sign was inputted I checked if there was only 1 thing on the stack. If not
; then give an error. If there was 1 thing on the stack,  convert the hex numerical value into an
; ascii code which could be outputted via R0 and OUT. At any point during my program if there 
; was overflow or underflow on the stack, there would be an error called invalid expression. 





.ORIG x3000
	
;your code goes here
	
	AND R0, R0, #0
	AND R1, R1, #0
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0
	AND R5, R5, #0
	AND R6, R6, #0
	AND R7, R7, #0 ; All registers initialized
; The next part is just checking each input

NEXT_CHAR
	GETC ; ECHOs to screen and load ASCII into R0 
	OUT	
	LD R1, NEQUAL ; R1 has neg ASCII of = sign
	ADD R1, R1, R0 
	BRnp G_SPC ; go to checking for space if = not inputted
	JSR EQ_STACK_CHK ; this sr checks if there's only 1 result on stack
	
G_SPC
	LD R1, NSPC ; R1 has neg ASCII of  space	
	ADD R1, R1, R0 
	BRz NEXT_CHAR ; Ask for next input if space inputted
	; This is where the JSR command will go idk tbh

G_ZERO ; starting at the numbers we will have to convert ascii to real val
	LD R1, NZERO ; R1 has neg ASCII of 0
	ADD R1, R1, R0
	BRnp G_ONE ; check for 1 if 0 not inputted
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH ; puts real val into the stack
	BRnzp NEXT_CHAR ; get next input

G_ONE
	LD R1, NONE 
	ADD R1, R1, R0
	BRnp G_TWO
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_TWO
	LD R1, NTWO
	ADD R1, R1, R0
	BRnp G_THREE
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_THREE
	LD R1, NTHREE
	ADD R1, R1, R0
	BRnp G_FOUR
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_FOUR
	LD R1, NFOUR
	ADD R1, R1, R0
	BRnp G_FIVE
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_FIVE
	LD R1, NFIVE
	ADD R1, R1, R0
	BRnp G_SIX
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_SIX
	LD R1, NSIX
	ADD R1, R1, R0
	BRnp G_SEVEN
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_SEVEN
	LD R1, NSEVEN
	ADD R1, R1, R0
	BRnp G_EIGHT
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_EIGHT
	LD R1, NEIGHT
	ADD R1, R1, R0
	BRnp G_NINE
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_NINE
	LD R1, NNINE ; end of checking for numbers inputted 
	ADD R1, R1, R0 ; For all digits we check then convert
	BRnp G_CROSS ; to the real value then push
	LD R1, NZERO
	ADD R0, R0, R1 ; converts ascii to hex
	JSR PUSH
	BRnzp NEXT_CHAR ; get next input


G_CROSS
	LD R1, NCROSS
	ADD R1, R1, R0
	BRnp G_DASH
	JSR POP
	ADD R4, R0, #0 ; value of R0 into R4
	JSR POP
	ADD R3, R0, #0 ; value of R0 into R3
	ADD R5, R5, #0 ; sets the nzp of error code
	BRnp ERROR
	JSR PLUS ; this computes the subtraction with inputs being R4R and R3L
	JSR PUSH ; the result of the operation is in R0. Gets put back onto the stack
	BRnzp NEXT_CHAR ; after we push back to the stack get next input




G_DASH
	LD R1, NDASH
	ADD R1, R1, R0
	BRnp G_STAR
	JSR POP
	ADD R4, R0, #0 ; value of R0 into R4
	JSR POP
	ADD R3, R0, #0 ; value of R0 into R3
	ADD R5, R5, #0 ; sets the nzp of error code
	BRnp ERROR
	JSR MIN ; this computes the subtraction with inputs being R4R and R3L
	JSR PUSH ; the result of the operation is in R0. Gets put back onto the stack
	BRnzp NEXT_CHAR ; after we push back to the stack get next input


G_STAR
	LD R1, NSTAR
	ADD R1, R1, R0
	BRnp G_SLASH
	JSR POP
	ADD R4, R0, #0 ; value of R0 into R4
	JSR POP
	ADD R3, R0, #0 ; value of R0 into R3
	ADD R5, R5, #0 ; sets the nzp of error code
	BRnp ERROR
	JSR MUL ; this will compute the multiplication
	JSR PUSH ; multiplication result goes back to stack
	BRnzp NEXT_CHAR



G_SLASH
	LD R1, NSLASH
	ADD R1, R1, R0
	BRnp G_CARROT
	JSR POP
	ADD R4, R0, #0 ; value of R0 into R4
	JSR POP
	ADD R3, R0, #0 ; value of R0 into R3
	ADD R5, R5, #0 ; sets the nzp of error code
	BRnp ERROR
	JSR DIV
	JSR PUSH ; multiplication result goes back to stack
	BRnzp NEXT_CHAR

	
G_CARROT
	LD R1, NCARROT
	ADD R1, R1, R0
	BRnp ERROR
	JSR POP
	ADD R4, R0, #0 ; value of R0 into R4
	JSR POP
	ADD R3, R0, #0 ; value of R0 into R3
	ADD R5, R5, #0 ; sets the nzp of error code
	BRnp ERROR
	JSR EXP ; go do the exponential computation
	JSR PUSH ; exponent result goes onto stack
	BRnzp NEXT_CHAR


ERROR
	LEA R0, INVALID ; no valid character inputted
	PUTS ; outputs the error message
	BRnzp TEST ; we want to end the program at this point





	

TEST	HALT ; program stops running here
INVALID		.STRINGZ "Invalid Expression"  ; message for bad input
NEQUAL		.FILL xFFC3 ; START of ASCII codes
NSPC		.FILL xFFE0
NZERO		.FILL xFFD0 ; you can use this one to convert ASCII to hex
NONE			.FILL xFFCF
NTWO			.FILL xFFCE
NTHREE		.FILL xFFCD
NFOUR		.FILL xFFCC
NFIVE			.FILL xFFCB
NSIX			.FILL xFFCA
NSEVEN		.FILL xFFC9
NEIGHT		.FILL xFFC8
NNINE			.FILL xFFC7
NCROSS		.FILL xFFD5 ; neg plus sign ASCII code
NDASH		.FILL xFFD3 ;  neg minus sign ASCII
NSTAR		.FILL xFFD6 ; neg ascii of times
NSLASH 		.FILL xFFD1 ; neg division sign ASCII
NCARROT		.FILL xFFA2 ;  neg power ASCII end of ASCII codes
N_ELM1		.FILL xC001 ; this is the neg value of x3FFF for 1 stack elm	



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

PRINT_HEX ;This SR prints what's in R5 to the screen 
	
	AND R1, R1, #0
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0
	AND R5, R5, #0
	AND R6, R6, #0
AND R7, R7, #0 ; All registers initialized

		
	LD R2, BITS
	LD R3, HEXA
	ADD R1, R0, #0
	ADD R5, R0, #0
	AND R0, R0, #0



BIT_SHIFT ; This section is the 4 bit shifts per hex charecter
	ADD R0, R0, R0 
	ADD R1, R1, #0
	BRzp SHIFT
	ADD R0, R0, #1

SHIFT
	ADD R1, R1, R1
	ADD R2, R2, #-1 
	BRnp BIT_SHIFT

	ADD R6, R0, #-10 ;checks if number
	BRzp FORWARD
	
	LD R6, DIGIT ; this gets the off set for a number
	ADD R0, R0, R6
	OUT
	AND R2, R2, #0 
	AND R0, R0, #0 ; reset R0
	ADD R2, R2, #4 ; resetting the 4 bit shift
	ADD R3, R3, #-1 ; decrement hex shift
	BRp BIT_SHIFT ; branches only taken if more hex shifts are needed
	BRnzp TEST ; kill program after printing

FORWARD	
	LD R6, LETTER ; this gets the off set for a letter
	ADD R0, R0, R6
	OUT
	AND R2, R2, #0 
	AND R0, R0, #0 ; reset R0 for next
	ADD R2, R2, #4 ; resetting the 4 bit shift
	ADD R3, R3, #-1 ; decrement hex shift
	BRp BIT_SHIFT ; branch is only taken if we have more hex shifts left
	BRnzp TEST ; kill program after printing

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here
	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ADD R0, R3, R4 ; this computes the addition
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	NOT R4, R4 ; first step in making second number R4 neg
	ADD R4, R4, #1 ; completed making the second num neg
	ADD R0, R3, R4 ; does the computation and goes into R0
	RET		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
; we will call R3 A R4 B
	AND R6, R6, #0 ; sets the sign flag
	ADD R3, R3, #0 ; R3 sets the ZNP
	BRn A_NEG
	BRz DEF_ZERO ; if you times  a zero just go right to zero
	BRp A_POS


A_NEG
	NOT R6, R6 ;makes our flag neg because 1 neg encountered
	NOT R3, R3
	ADD R3, R3, #1 ; this made A pos
	ADD R4, R4, #0 ; R4 sets the NZP
	BRn B_NEG
	BRz DEF_ZERO
	BRp B_POS



A_POS
	ADD R4, R4, #0 ; R4 sets the NZP
	BRn B_NEG
	BRz DEF_ZERO
	BRp B_POS

B_NEG
	NOT R6, R6 ; Flip the neg flag
	NOT R4, R4 
	ADD R4, R4, #1 ; this made the R4 positive
	BRnzp DO_TIMES ; no matter what do computation
	

B_POS
	BRnzp DO_TIMES ; no matter what do the computation


DEF_ZERO
	AND R0, R0, #0 ; R0 is now 0
	RET

DO_TIMES
	AND R0, R0, #0 ; SETS R0 for mult

TIMES_LOOP
	ADD R0, R0, R3
	ADD R4, R4, #-1
	BRp TIMES_LOOP
	ADD R6, R6, #0 ; R6 sets nzp so we se if mult should be neg
	BRzp CLEAR
	NOT R0, R0
	ADD R0, R0, #1 ; R0 is now neg



	CLEAR RET
			
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	AND R0,R0, #0 ; resets R0
	NOT R4, R4
	ADD R4, R4, #1 ; R4 is now neg
	DIV_LOOP
	ADD R3, R4, R3 ; one iteration of division
	BRn DIV_DONE



	ADD R0, R0,#1 ; quotient divide fix div
	ADD R3, R3, #0 ; R3 sets nzp
	BRp DIV_LOOP
	DIV_DONE
	RET	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	STI R3, GOOF ; original value of base in mem
	AND R1, R1, #0
	AND R0, R0, #0 ; intializing
	ADD R1, R4, #0 ; R1 has the power
	ADD R1, R1, #0 ; Checks value of power
	BRz POWER_ZERO ; take this if the power is zero
	ADD R1, R1, #-1 ; checks for power of 1
	BRz POWER_ONE
	LDI R4, GOOF
	;ADD R0, R3, #0 ; push value of R3 into R0
EXP_MULT
	ADD R0, R0, R3
	ADD R4, R4, #-1
	BRp EXP_MULT
	LDI R4, GOOF
	ADD R4, R4, #-1 ; DEC by 1
	STI R4, GOOF
	ADD R3, R0, #0 ; gives r3 new value
	ADD R1, R1, #-1 ; decrement the power
	BRp EXP_MULT
	BRnz EXPONENT_DONE



	


POWER_ZERO
	AND R0, R0, #0
	ADD R0, R0, #1
BRnzp EXPONENT_DONE


POWER_ONE
	
	ADD R0, R3, #0
	BRnzp EXPONENT_DONE

EXPONENT_DONE
	RET


	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

	;MYSUBROUTINES

EQ_STACK_CHK
	LD R1, STACK_TOP
	LD R0, N_ELM1
	ADD R0, R0, R1
	BRnp ERROR ; this will end the program with error
	JSR POP ; only happens if stack has 1 item, item is returned in R0
	JSR PRINT_HEX ; this will take the value in R0 and print it to the screen
	
BRnzp TEST ; Just in case we get here kill the program

	




POP_SaveR3		.BLKW #1	;
POP_SaveR4		.BLKW #1	;
STACK_END		.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP		.FILL x4000	;

BITS			.FILL x4 ; this represents the 4 bits in a hex number
HEXA			.FILL x4 ; represents the 4 hex numbers in a instruction
DIGIT			.FILL x30 ; offset needed print number
LETTER		.FILL x37 ; offset needed to print letter
GOOF			.FILL x4500 ;remove



.END