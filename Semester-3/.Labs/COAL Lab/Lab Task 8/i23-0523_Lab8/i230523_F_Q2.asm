.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

.DATA
	arr db 0, -1, 2, 4, 6, 8, -5, 12, 3, 10
	large db 0
	small db 0

.CODE
main Proc
	mov esi, offset arr
	mov al, [esi]
	mov dl, [esi]
	mov bx, lengthof arr - 1
	mov edi, esi
	add di, bx
	mov ah, [edi]
	mov dh, [edi]

	;Largest and smallest
	mov ecx, lengthof arr
	L1:
		mov bl, [esi]

		;;;For smaller num:
		cmp bl, al
		jl J1
		jmp else1
		J1:
			mov al, bl
		else1:
		
		;;;For larger num:
		cmp bl, ah
		jg J2
		jmp else2
		J2:
			mov ah, bl
		else2:

		inc esi
	Loop L1

	mov esi, offset arr

	;Sec Largest and sec smallest
	mov ecx, lengthof arr
	L2:
		mov bh, [esi]

		;;;For smaller num:
		cmp bh, al
		je else3
		mov bl, bh
		cmp bl, dl
		jl J3
		jmp else3
		J3:
			mov dl, bl
		else3:
		
		;;;For larger num:
		cmp bh, ah
		je else4
		mov bl, bh
		cmp bl, dh
		jg J4
		jmp else4
		J4:
			mov dh, bl
		else4:

		inc esi

	Loop L2
	mov large, dh
	mov small, dl

Invoke EXitProcess, 0
main Endp
End main