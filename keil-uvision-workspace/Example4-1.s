	PRESERVE8
	THUMB

	AREA	|.text|, CODE, READONLY, ALIGN = 2
	ENTRY
	EXPORT	__main

__main

	MOV    R0, #0xFF
	MOV    R1, #-0x281
	MOV	   R4, #0xD364
	MOVT   R4, #0xFFB1
	MOV    R5, R4

STOP
	B	STOP
	END