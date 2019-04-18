			.def _autocorr
			.text ;code section
_autocorr: 	; input are in A4, B4, A6 which are data array, autocorr array
			; and 512
			MV A4, A9  ; let A9 point to x[0]
			ZERO A7  ; set k for outer loop
outerloop
			ADD A7, B4, A5  ; get R[k] position
			ADD A7, A9, A3  ; get x[k] position
			ZERO A8  ; set n for inner loop
innerloop
			LDH *+A9[A8], B5  ; load x[n]
			NOP 5
			LDH *+A3[A8], B6  ; load x[n+k]
			NOP 5
			MPY B5, B6, B7  ; get x[n] * x[n+k]
			NOP 5
			LDH *A5, B8  ; get R[k]
			NOP 5
			ADD B8, B7, B8  ; add to R[k]
			NOP 5
			STH B8, *A5  ; store R[k]
			ADD A8, 1, A8  ; increment n
			ADD A6, 0, B0  ; B0 = 512
			SUB B0, A7, B0  ; B0 = 512 - k
			SUB B0, A8, B0  ; B0 = 512 - k - n
	[B0]	B innerloop
			NOP 5
			ADD A7, 1, A7  ; increment k
			ZERO B1
			ADD B1, 20, B1  ; B1 = 20
			SUB B1, A7, B1  ; B1 = 20 - k
	[B1]	B outerloop
			NOP 5

