.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.DATA
	i db 0

.CODE
main PROC
	MOV al,+127
	CMP al,-128
	JA IsAbove
		inc i
	IsAbove:
	JG IsGreater
		inc i
	IsGreater:

Invoke ExitProcess, 0
main Endp
End main