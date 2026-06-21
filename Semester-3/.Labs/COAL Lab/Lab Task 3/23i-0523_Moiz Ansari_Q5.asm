.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	Var1 dd 12345678h

.CODE
main PROC
	

INVOKE ExitProcess, 0

main ENDP
END main