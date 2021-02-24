	PRESERVE8
	THUMB

	AREA	|.text|, CODE, READONLY, ALIGN = 2
	ENTRY
	EXPORT	__main

__main

	MOV    R0, #0x06
	MOV    R3, #0x200
	MOV	   R5, #0x9B1D

STOP

	LSR	   R4, R3, #6
	LSR	   R2, R3, R0
	LSR	   R6, R5, #5
	LSRS   R7, R5, #5
	
	B	STOP
	END