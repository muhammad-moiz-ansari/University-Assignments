.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	dataArray dword 1, 2, 3, 4
	ptrToArray dword ?

.CODE
main proc
	mov ptrToArray, offset dataArray
	add ptrToArray, type ptrToArray
	mov esi, ptrToArray

Invoke ExitProcess, 0
main ENDP
End main