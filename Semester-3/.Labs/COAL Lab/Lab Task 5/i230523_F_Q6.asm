.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	complexArray word 1234h, 5678h, 9ABCh
	indexPtr dword offset complexArray

.CODE
main proc
	add indexPtr, type complexArray
	mov esi, indexPtr
	mov ax, [esi]

Invoke ExitProcess, 0
main ENDP
End main