.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	byteArray	db 1, 2, 3, 4, 5
	wordArray	dw 1, 2, 3, 4, 5, 6
	dwordArray	dd 1, 2, 3, 4, 5, 6, 7
	byteLength	db ?
	wordLength	db ?
	dwordLength	db ?

.CODE
main PROC
	MOV byteLength, Lengthof byteArray
	MOV wordLength, Lengthof wordArray
	MOV dwordLength, Lengthof dwordArray

INVOKE ExitProcess, 0

main ENDP
END main