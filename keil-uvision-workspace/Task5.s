	PRESERVE8
	THUMB
	
	AREA	myDATA, DATA, READWRITE
	
Result	DCD	0

	AREA	|.text|, CODE, READONLY, ALIGN=2
	
	ENTRY
	
	EXPORT	__main
	
__main

	LDR R0, =Value
	
	BL	ISPRIME
	
	B	STOP
	
ISPRIME	PROC
	
	LDR R7, [R0]
	LSR R1, R7, #1
	
	MOV	R2, #2
	
lbegin
	SUB	R3, R1, R2
	CBZ	R3, lend
	
	SDIV R4, R7, R2
	MLS	R5, R4, R2, R7
	
	CBZ R5, mbegin

	ADD	R2, #1
	B	lbegin
	
lend
	MOV R6, #1

mend

	BX	LR
	ENDP

mbegin
	MOV	R6, #0
	B	mend
	
STOP

Value DCD 13

	END