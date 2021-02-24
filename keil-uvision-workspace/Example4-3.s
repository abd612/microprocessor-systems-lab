	PRESERVE8
	THUMB

	AREA	|.text|, CODE, READONLY, ALIGN = 2
	ENTRY
	EXPORT	__main

__main

	MOV    R0, #0x07
	MOV    R3, #-0x669
	MOV	   R5, #0xD634
	MOVT   R5, #0xFFB1

STOP

	ASR	   R4, R3, #5
	ASR	   R2, R3, R0
	ASR	   R6, R5, #5
	ASRS   R7, R5, #5
	
	B	STOP
	END