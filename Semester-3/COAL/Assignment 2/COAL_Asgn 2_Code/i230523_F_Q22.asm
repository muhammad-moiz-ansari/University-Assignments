.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.data
	val1 DW 5
	val2 DW 6

.code
Sum PROC
	PUSH ebp
	mov ebp,esp
	mov ax,0
	add ax,[ebp+4]
	add ax,[ebp+6]
	POP ebp
	RET 4
Sum ENDP

Main PROC
	Push val1
	Push val2
	call sum

Invoke ExitProcess, 0
main Endp
End main