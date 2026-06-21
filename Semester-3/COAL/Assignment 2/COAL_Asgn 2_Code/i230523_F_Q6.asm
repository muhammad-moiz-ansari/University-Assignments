.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.DATA
	

.CODE
main PROC
	mov ax, 0A593H
	XOR ax,-1
	XOR ax, 0
	XOR ax, -1
	XOR ax, ax


	mov ax, 05A37H
	XOR al, 0

	XOR ah, 1
	XOR al, ah

Invoke ExitProcess, 0
main Endp
End main