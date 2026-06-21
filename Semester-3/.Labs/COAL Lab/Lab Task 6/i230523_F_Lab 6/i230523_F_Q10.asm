.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	asize = 26
	arr db asize dup(?)

.CODE
main PROC
	mov ecx, asize
	mov esi, offset arr
	mov al, 61h

	L1:
		mov [esi], al
		inc esi
		inc al
	Loop L1

Invoke ExitProcess, 0
Main Endp
End Main