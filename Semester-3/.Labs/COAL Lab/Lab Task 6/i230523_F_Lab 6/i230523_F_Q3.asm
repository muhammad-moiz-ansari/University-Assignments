.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	arr db 1, 2, 3, 4, 5, 6
	arrsize = lengthof arr

.CODE
main Proc
	mov ecx, arrsize / 2
	mov esi, offset arr
	mov edi, esi
	add edi, arrsize - 1 

	L1:
		mov al, [esi]
		mov bl, [edi]
		mov [esi], bl
		mov [edi], al
		inc esi
		dec edi

	loop L1

Invoke ExitProcess, 0
main ENDP
END main