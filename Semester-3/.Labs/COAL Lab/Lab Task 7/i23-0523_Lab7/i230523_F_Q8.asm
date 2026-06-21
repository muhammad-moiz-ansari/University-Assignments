.386
.model flat, stdcall
.stack 4096

ExitProcess Proto, dwExitCode:Dword

.DATA
	arr db 2, 4, 3, -1, 6, 8, 5, 7, 9, 10
	arrsize = lengthof arr
	max db ?

.CODE
main PROC
	mov esi, offset arr
	mov ecx, arrsize
	mov al, [esi]
	mov max, al
	inc esi

	L1:
		mov al, [esi]
		cmp max, al
		jg skip
			mov max, al
		skip:
		inc esi

	Loop L1

	movsx ax, max

Invoke ExitProcess, 0
main Endp
End main