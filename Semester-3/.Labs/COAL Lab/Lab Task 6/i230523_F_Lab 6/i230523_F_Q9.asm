.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	n = 3
	P dd 1

.CODE
main PROC
	mov ecx, n

	L1:
		mov eax, P
		mul ecx
		mov P, eax

	Loop L1

Invoke ExitProcess, 0
Main Endp
End Main