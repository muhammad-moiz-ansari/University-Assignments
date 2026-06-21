.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	myword DB "Beware!"
	L DB ?
	S DB ?
	type_of_str DB ?

.CODE
main PROC

	MOV type_of_str, type myword
	MOV L, lengthof myword
	MOV S, sizeof myword

INVOKE ExitProcess, 0

main ENDP
END main