.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC

	MOV cx, 804h	; cl = 4, ch = 8
	MOV dx, 0AAAh	; dl = 170, dh = 10

	ADD cx, dx		; cx = 4782, dx = 2730


INVOKE ExitProcess, 0

main ENDP
END main