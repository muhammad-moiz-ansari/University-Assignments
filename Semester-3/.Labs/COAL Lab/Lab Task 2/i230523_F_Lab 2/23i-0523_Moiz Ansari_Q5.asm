.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC
	
	;---------- Q-5 ----------;

	MOV cx, 2024	; cl = 232, ch = 7
	MOV dx, 2005	; dl = 213, dh = 7

	SUB cx, dx		; cx = 19, dx = 2005


INVOKE ExitProcess, 0

main ENDP
END main