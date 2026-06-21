.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	numArray db 10

.CODE
main proc
	mov esi, offset numArray
	mov ecx, 10
	mov al, 10h

	L1:
		mov [esi], al
		add al, 10h
		inc esi

	Loop L1

	mov esi, offset numArray
	mov bl, [esi + 5]

Invoke ExitProcess, 0
main ENDP
End main