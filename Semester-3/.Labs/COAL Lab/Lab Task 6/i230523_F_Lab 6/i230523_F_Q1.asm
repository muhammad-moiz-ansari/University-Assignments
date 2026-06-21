.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main Proc
	;(i)
	mov ax, 9
	mov bx, 5

	add ax, bx

	;(ii)
	mov cx, -2
	mov dx, -6

	add cx, dx

	;(iii)
	mov ax, 9
	mov bx, 5

	sub ax, bx

	;(iv)
	mov cx, -2
	mov dx, -6

	sub cx, dx

Invoke ExitProcess, 0
main ENDP
END main