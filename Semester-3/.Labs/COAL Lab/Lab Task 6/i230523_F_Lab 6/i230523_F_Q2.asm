.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main Proc
	;(i)
	mov ax, 9999
	mov bx, 9999

	mul bx

	;(ii)
	mov ax, -2
	mov bx, -6

	imul bx

	;(iii)
	mov al, 9
	mov bl, 5

	div bl

	;(iv)
	mov dx, 0
	mov ax, -6
	mov bx, -2

	idiv bx

Invoke ExitProcess, 0
main ENDP
END main