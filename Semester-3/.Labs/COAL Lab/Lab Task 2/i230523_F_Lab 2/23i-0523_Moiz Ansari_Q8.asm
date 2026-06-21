.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC

	MOV ax, 38	; al = 38, ah = 0
	MOV bl, 51	; bl = 51

	ADD ax, bl		; The two registers will not add the values because ax is of 16 bits, 
					; while bl is of 8 bits. Since both registers should be of the same 
					; size to add so they won't add up.


INVOKE ExitProcess, 0

main ENDP
END main