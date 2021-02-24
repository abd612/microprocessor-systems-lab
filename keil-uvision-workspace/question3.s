	PRESERVE8
	THUMB
	
Stack	EQU		0x00000100

	AREA	STACK, NOINIT, READWRITE, ALIGN=3
StackMem	SPACE	Stack

	AREA	RESET, DATA, READONLY
	EXPORT	__Vectors
	
__Vectors
	DCD		StackMem + Stack
	DCD		Reset_Handler
	

	AREA	RawData, DATA, READONLY
X	DCD		10, 20, 30, 40

	AREA	ProcessedData, DATA, READWRITE
Y	DCD		0, 0, 0, 0

	AREA	|.text|, CODE, READONLY, ALIGN=2
	ENTRY
	EXPORT	Reset_Handler
	
Reset_Handler

	LDR		R1, =X
	LDR		R2, =Y
	MOV		R3, #4
	
lbegin
	CBZ		R3, lend
	
	LDR		R4, [R1]
	LDR		R5, [R2]
	ADD		R4, R4
	ADD		R5, R4, #15
	
	STR		R5, [R2]
	
	ADD		R1, #4
	ADD		R2, #4
	SUB		R3, #1
	
	B		lbegin
lend
	
STOP
	B	STOP
	END