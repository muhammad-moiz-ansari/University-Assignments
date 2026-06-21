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
	mov ax, 000FFh
	mov ecx, arysize
	and al, 061h
	mov bl, al
	and bl, 0CFh ;masking
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