.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

.DATA
	nameSTRING db 'M', 'O', 'I', 'Z', 'A', 'N', 'S', 'A', 'R', 'I', 0 
	X dd 3

.CODE
main Proc
	mov ecx, lengthof nameSTRING
	mov esi, offset nameSTRING
	mov edi, esi
	add edi, X

	L1:
		mov al, [edi]
		mov [esi], al
		inc esi
		inc edi
	Loop L1
	

	;Q-7;
	;mov al, 05Fh
	;rol al, 1

	;mov al, 0F5h
	;rcl al, 1


Invoke EXitProcess, 0
main Endp
End main