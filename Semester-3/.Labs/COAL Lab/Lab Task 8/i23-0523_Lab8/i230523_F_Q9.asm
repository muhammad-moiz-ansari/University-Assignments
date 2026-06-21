.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

GetStdHandle PROTO, nStdHandle:dword
WriteConsoleA PROTO, a1: Dword, a2: ptr Byte, a3: Dword, a4: ptr Dword, a5: Dword
ReadConsoleA PROTO, a1: Dword, a2: ptr Byte, a3: Dword, a4: ptr Dword, a5: Dword

.DATA
	str1 db "Enter an integer (Range: 0-E): ", 0
	str21 db 0Ah, "Pattern 1: ", 0Ah, 0
	str22 db 0Ah, "Pattern 2: ", 0Ah, 0
	str3 db 0Ah, "Invalid input (Range: 0-E)...Enter again: ", 0
	num db ?
	stars1 db 500 dup(?)
	stars2 db 500 dup(?)
	x dd ?

.CODE
main PROC
	mov bl, 0
	mov bh, 45h

	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset str1, lengthof str1, offset x, 0
	jmp No

	Again:
	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset str3, lengthof str3, offset x, 0

	No:
	Invoke getstdhandle, -10
	Invoke ReadConsoleA, eax, offset num, lengthof num, offset x, 0

	;----- Input Validation -----
	cmp num, bl
	jl Again
	cmp num, bh
	jg Again

	mov bl, num
	mov bl, 48
	cmp num, bl
	jl skip
	sub num, bl
	skip:

	;--------- (a) ---------;

	mov dl, "*"
	mov dh, 0Ah
	mov esi, offset stars1
	mov ecx, 0
	mov cl, num
	L1:
		mov ebx, ecx
		mov ecx, 0
		mov cl, num 
		L2:
			mov [esi], dl
			inc esi
		Loop L2
		mov [esi], dh
		inc esi
		mov ecx, ebx
	Loop L1

	;--------- (b) ---------;

	mov dl, "*"
	mov dh, 0Ah
	mov esi, offset stars2
	mov ecx, 0
	mov cl, num
	mov ah, 1

	L3:
		mov ebx, ecx
		mov ecx, 0
		mov cl, ah
		L4:
			mov [esi], dl
			inc esi
		Loop L4
		mov [esi], dh
		inc esi
		inc ah
		mov ecx, ebx
	Loop L3

	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset str21, lengthof str21, offset x, 0
	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset stars1, lengthof stars1, offset x, 0

	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset str22, lengthof str22, offset x, 0
	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset stars2, lengthof stars2, offset x, 0

Invoke ExitProcess, 0
main Endp
End main