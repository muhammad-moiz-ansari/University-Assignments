.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	R = 1001b
	S = 0010b

.CODE
main PROC
	;Decrement
	mov al, R
	mov bl, S
	dec al		;al = 0000 1101
	dec bl		;bl = 0000 0100

	;Increment
	mov al, R
	mov bl, S
	inc al		;al = 0000 1111
	inc bl		;bl = 0000 0110

	;Division
	mov dx, 0
	mov ax, R
	mov bx, S
	div bx		;ax = 0100 (Q)
				;dx = 0001 (R)

Invoke ExitProcess, 0
Main Endp
End Main