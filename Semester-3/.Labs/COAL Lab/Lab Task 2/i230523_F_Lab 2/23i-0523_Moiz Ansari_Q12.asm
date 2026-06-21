.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	var1 DB 9
	var2 DB 6
	Result DB ?

.CODE
main PROC

	; To prevent changing var1 value
	MOV al, var1
	MOV Result, al	
	MOV ah, var2

	; Addition
	ADD Result, ah

INVOKE ExitProcess, 0

main ENDP
END main