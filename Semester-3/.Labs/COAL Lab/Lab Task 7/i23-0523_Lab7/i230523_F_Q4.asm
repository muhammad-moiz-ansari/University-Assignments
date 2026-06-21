.386
.model flat, stdcall
.stack 4096

ExitProcess Proto, dwExitCode:Dword

.DATA
	arr db 'moiz ansari', 0
	arrsize = lengthof arr
	res db arrsize dup(?), 0

.CODE
main PROC
	mov ecx, arrsize - 1
	mov esi, offset arr
	mov edi, offset res

	L1:
		mov al, [esi]

		cmp al, 20h
		jz jumpspace
			sub al, 20h
		jumpspace:
		mov [edi], al
		inc esi
		inc edi

	Loop L1

Invoke ExitProcess, 0
main Endp
End main