.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.DATA
	

.CODE
Sum PROC
	add ax,bx
	add ax,cx
	RET
Sum ENDP
Main PROC
	mov ax,1
	mov bx,2
	mov cx,3
	call sum

Invoke ExitProcess, 0
main Endp
End main