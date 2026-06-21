.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC

	MOV cx, 101101100b	; cl = 108, ch = 1
	MOV dx, 110110100b	; dl = 180, dh = 1

	ADD cx, dx		; cx = 800, dx = 436


INVOKE ExitProcess, 0

main ENDP
END main