.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	byteArray	db 1, 2, 3, 4, 5
	wordArray	dw 1, 2, 3, 4, 5
	dwordArray	dd 1, 2, 3, 4, 5
	byteSize	db ?
	wordSize	db ?
	dwordSize	db ?

.CODE
main PROC
	MOV byteSize, Sizeof byteArray
	MOV wordSize, Sizeof wordArray
	MOV dwordSize, Sizeof dwordArray

INVOKE ExitProcess, 0

main ENDP
END main