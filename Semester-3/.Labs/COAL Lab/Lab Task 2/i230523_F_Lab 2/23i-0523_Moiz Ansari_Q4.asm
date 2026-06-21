.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC
	
	;---------- Q-4 ----------;

	MOV cx, 0523	; cl = 11, ch = 2
	MOV dx, 0617	; dl = 105, dh = 2

	ADD cx, dx		; cx = 1140, dx = 617


INVOKE ExitProcess, 0

main ENDP
END main