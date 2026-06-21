.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.DATA
	

.CODE
main PROC
	mov ax,1
	mov cx,2
	mov dx,3
	mov bx,4
	mov bp,5
	mov si,6
	mov di,7
	PUSHA
	mov ax,15
	mov cx,14
	mov dx,13
	mov bx,12
	mov bp,11
	mov si,10
	mov di,9
	POPA

Invoke ExitProcess, 0
main Endp
End main