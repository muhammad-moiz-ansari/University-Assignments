.386
.model flat, stdcall
.stack 4096

ExitProcess Proto, dwExitCode:Dword

.DATA
	arr db 2, 4, 3, 10, 6, 8, 5, 7, 9, -1
	arrsize = lengthof arr
	min db ?

.CODE
main PROC
	mov esi, offset arr
	mov ecx, arrsize
	mov al, [esi]
	mov min, al
	inc esi

	L1:
		mov al, [esi]
		cmp min, al
		jl skip
			mov min, al
		skip:
		inc esi

	Loop L1

	movsx ax, min

Invoke ExitProcess, 0
main Endp
End main