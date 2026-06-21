.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	X = 1110b
	Y = 0101b

.CODE
main PROC
	;Multiplication
	mov al, X
	mov bl, Y
	mul bl		;al = 0100 0110

	;Decrement
	mov al, X
	mov bl, Y
	dec al		;al = 0000 1101
	dec bl		;bl = 0000 0100

	;Addition
	mov al, X
	mov bl, Y
	add al, bl	;al = 0001 0011

	;Subtraction
	mov al, X
	mov bl, Y
	sub al, bl	;al = 0000 1001

	;Increment
	mov al, X
	mov bl, Y
	inc al		;al = 0000 1111
	inc bl		;bl = 0000 0110

Invoke ExitProcess, 0
Main Endp
End Main