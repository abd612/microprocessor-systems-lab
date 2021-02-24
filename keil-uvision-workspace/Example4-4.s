	PRESERVE8
	THUMB

	AREA	|.text|, CODE, READONLY, ALIGN = 2
	ENTRY
	EXPORT	__main

__main

	MOV    R7, #0xC
	MOV    R0, #-0x281
	MOV	   R2, #0x25C3
	MOV    R4, #0x593C
	MOVT   R4, #0xA377

STOP

	LSL	   R1, R0, #3
	LSL	   R3, R2, R7
	LSL	   R5, R4, #10
	LSLS   R6, R4, #10
	
	B	STOP
	END