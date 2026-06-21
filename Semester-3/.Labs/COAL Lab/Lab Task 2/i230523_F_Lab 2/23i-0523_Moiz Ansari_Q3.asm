.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC
	
	;---------- Q-3 ----------;

	MOV ax, 1092	; al = 68, ah = 4
	MOV bx, 5		; bl = 5, bh = 0

	ADD ax, bx		; ax = 1092, bx = 5


INVOKE ExitProcess, 0

main ENDP
END main