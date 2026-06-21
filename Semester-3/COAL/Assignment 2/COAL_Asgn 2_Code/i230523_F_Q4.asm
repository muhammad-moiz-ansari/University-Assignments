.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.data
	ary db 26 dup(?)
	arysize = $ - ary
	ary_copy db arysize dup(0)
	endmem db 1

.code
main Proc
	mov esi, OFFSET ary
	mov edi, OFFSET ary_copy
	mov ax, 0041h
	mov ecx, arysize
	mov bl, al
	or bl, 00100000b
	L1:
		mov [esi], al
		mov [edi], bl
		inc esi
		inc edi
		inc al
		inc bl
	Loop L1

Invoke ExitProcess, 0
main Endp
End main