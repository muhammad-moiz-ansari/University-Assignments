.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	arr word 1234h, 5678h, 90ABh, 0CDEFh, 9876h, 5432h

.CODE
main proc
	mov edi, offset arr
	add edi, 3 * (type arr)
	mov esi, edi

Invoke ExitProcess, 0
main ENDP
End main