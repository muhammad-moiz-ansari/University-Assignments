.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	arr db 1, 2, 3, 4, 5
	arrsize = lengthof arr

.CODE
main Proc
	mov ecx, arrsize
	mov esi, offset arr

	L1:
		mov al, [esi] 
		mov bl, [esi]

		mul bl

		mov [esi], al
		inc esi

	Loop L1


Invoke ExitProcess, 0
main ENDP
END main