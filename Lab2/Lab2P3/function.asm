			.def _autocorr
			.text ;code section
_autocorr: 	; input are in A4, B4, A6 which are data array, autocorr array
			; and 512
			MV A4, A9  ; let A9 point to x[0]
			ZERO A7  ; set k for outer loop
outerloop
			mv B4, A5 ;ADD A7, B4, A5  ; get R[0] position
			ADDAH A9, A7, A3  ; get x[k] position (partial) UNDOCUMENTED note that the 1st term is the address, offset*2, dest.
			ZERO A8  ; set n for inner loop
innerloop
			LDH *+A9[A8], B5  ; load x[n]
			;NOP 5
			LDH *+A3[A8], B6  ; load x[n+k]
			NOP 5
			MPY B5, B6, B7  ; get x[n] * x[n+k]
			;NOP 5
			LDW *+A5[A7], B8  ; get R[0+k]
			NOP 5
			ADD B8, B7, B8  ; add to R[k]
			NOP 5
			STW B8, *+A5 [A7]  ; store R[k]
			ADD A8, 1, A8  ; increment n
			mv A6, B0  ; B0 = 512 ;ADD A6, 0, B0
			NOP 5
			SUB B0, A7, B0  ; B0 = 512 - k
			NOP 5
			SUB B0, A8, B0  ; B0 = 512 - k - n
			NOP 5
	[B0]	B innerloop
			NOP 5
			ADD A7, 1, A7  ; increment k (almost need 2 do by the # of bytes in a half word, which is confusing so how do we do 2 consecutive *+...'s?)
			ZERO B1
			ADD B1, 20, B1  ; B1 = 20
			SUB B1, A7, B1  ; B1 = 20 - k
	[B1]	B outerloop
			NOP 5

