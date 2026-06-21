.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.DATA
	parity DQ 0A1B2C3D4E5F67890h
	isparity db 0

.CODE
main PROC
	m = 0001b

	mov al, 0
	mov esi, offset parity
	mov ecx, 8

	L1:	
		mov ebx, ecx
		mov ah, [esi]
		
		mov ecx, 8
		L2:
			mov dl, m
			and dl, ah
			XOR al, dl
			shr ah, 1
		Loop L2
		inc esi
		mov ecx, ebx
	Loop L1

	cmp al, 0
	jnz skip
		mov al, 1
		mov isparity, al
	skip:


Invoke ExitProcess, 0
main Endp
End main