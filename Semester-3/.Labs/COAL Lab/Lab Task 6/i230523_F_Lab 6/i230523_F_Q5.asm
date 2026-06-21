.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	A = 1011b
	B = 1101b

.CODE
main PROC
	;Addition
	mov al, A
	mov bl, B
	add al, bl	;al = 0001 1000

	;Subtraction
	mov al, A
	mov bl, B
	sub al, bl	;al = 1111 1110

	;Multiplication
	mov al, A
	mov bl, B
	mul bl		;al = 1000 1111

	;Division
	mov al, A
	mov bl, B
	div bl		;al = 0000 0000
				;ah = 0000 1011

Invoke ExitProcess, 0
Main Endp
End Main