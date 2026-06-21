.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	byteArray	db 'byte$'
	wordArray	db 'word$'
	dwordArray	db 'dword$'

.CODE
main PROC
	

INVOKE ExitProcess, 0

main ENDP
END main