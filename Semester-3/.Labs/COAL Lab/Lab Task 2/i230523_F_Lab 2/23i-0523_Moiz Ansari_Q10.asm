.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC

	MOV cx, 10111010b	; cl = 186, ch = 0
	MOV dx, 1152o		; dl = 106, dh = 2

	ADD cx, dx		; cx = 804, dx = 618

	; They would add together because their sizes are same, just their representation is different when inputting them.
	; Inside the registers they are stored in the same format


INVOKE ExitProcess, 0

main ENDP
END main