.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	largeValue dword 0ABCDEF12h

.CODE
main proc
	mov al, byte ptr largeValue
	mov cx, word ptr [largeValue + 1]
	mov edx, dword ptr largeValue

Invoke ExitProcess, 0
main ENDP
End main