.386
.model flat, stdcall
.stack 4096

ExitProcess Proto, dwExitCode:Dword

.DATA
	arr db -10, 4, -5, 2, -8, -7, 1, 0, -1, -128
	arrsize = lengthof arr
	negarr db arrsize dup(?)
	posarr db arrsize dup(?)

.CODE
main PROC
	mov esi, offset arr
	mov edi, offset negarr
	mov esp, offset posarr
	mov ecx, arrsize

	L1:
		movsx eax, byte ptr [esi]
		add ax, 0		;It will update sign flag

		mov bl, [esi]
		js skip
			; +ve Numbers:
			mov [esp], bl
			inc esp
			jns skip2
		skip:
			; -ve Numbers:
			mov [edi], bl
			inc edi
			skip2:

		inc esi
	Loop L1

Invoke ExitProcess, 0
main Endp
End main