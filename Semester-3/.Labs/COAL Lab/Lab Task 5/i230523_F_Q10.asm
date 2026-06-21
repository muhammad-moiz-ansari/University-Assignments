.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main proc
	

Invoke ExitProcess, 0
main ENDP
End main