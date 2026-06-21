.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	byteArray db 1, 2, 3, 4, 5
	wordArray dw 10, 20, 30, 40
	dwordArray dd 100, 200, 300

.CODE
main PROC
	

INVOKE ExitProcess, 0

main ENDP
END main