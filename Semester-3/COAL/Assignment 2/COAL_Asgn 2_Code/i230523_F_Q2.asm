.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.DATA
	

.CODE
main PROC
	mov al, 0AEh
	and al, 246

Invoke ExitProcess, 0
main Endp
End main