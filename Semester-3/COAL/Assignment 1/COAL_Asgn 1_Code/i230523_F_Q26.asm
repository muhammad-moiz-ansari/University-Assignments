.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
	ary DWORD 100 dup(0abcdef12h)

.CODE
main PROC
	mov eax, 00000001
	mov esi, offset ary
	mov ecx, 100

	L1:
		mov [esi], eax
		inc eax
		add esi, 4

	Loop L1
	
Invoke ExitProcess, 0

main ENDP
END main