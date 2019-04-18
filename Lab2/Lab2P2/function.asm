		.def _reversefunc
		.text ;code section
_reversefunc: ;reverse the order in the stored address
		; the parameter passed in will be stored in A4,
		; which is the reference pointer for the array
		MV A6, B0
		MPY A6, 2, A6
		NOP 5
		ADD A6, B4, B4  ; advancing dest array to the last addr
		NOP 5
		SUB B4, 1, B4
loop	LDH *A4++[1], A7  ; load data into A7
		NOP 5
		STH A7, *B4--[1]  ; store data into memory location
		SUB B0, 1, B0
	[B0] B loop
		NOP 5
		ADD B4, 2, A4
		NOP 5

