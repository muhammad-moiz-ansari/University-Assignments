.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
VAR DB 46
rt DB "NAME"


.code
main PROC
	MOV eax, 46
	MOV ebx, 4
	mov al , rt
	MOV dh, VAR
	ADD eax, ebx
	ADD dh, 4


	INVOKE ExitProcess, 0

main ENDP
End main
