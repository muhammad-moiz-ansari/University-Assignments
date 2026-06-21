.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	n = 23
	arrsize = n/2
	arr db arrsize dup(?)

.CODE
main PROC
	mov esi, offset arr
	mov ecx, arrsize
	mov al, 2

	L1:
		mov [esi], al
		inc esi
		add al, 2

	Loop L1

Invoke ExitProcess, 0
Main Endp
End Main