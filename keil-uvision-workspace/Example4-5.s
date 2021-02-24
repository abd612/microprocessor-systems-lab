	PRESERVE8
	THUMB

	AREA	|.text|, CODE, READONLY, ALIGN = 2
	ENTRY
	EXPORT	__main

__main

	MOV    R0, #0x9
	MOV	   R1, #0x25C3
	MOV    R3, #0x73A2
	MOVT   R3, #0x5D81

STOP

	ROR	   R2, R1, #24
	ROR	   R7, R3, R0
	ROR	   R4, R3, #10
	RORS   R5, R3, #10
	
	B	STOP
	END