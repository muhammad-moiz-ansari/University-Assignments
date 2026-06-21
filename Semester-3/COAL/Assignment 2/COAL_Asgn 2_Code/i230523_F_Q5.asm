.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.DATA
	

.CODE
main PROC
	mov al, 11100011b
	or al, 00000100

Invoke ExitProcess, 0
main Endp
End main