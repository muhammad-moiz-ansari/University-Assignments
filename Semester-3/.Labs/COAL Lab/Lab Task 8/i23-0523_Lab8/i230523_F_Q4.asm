.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

GetStdHandle PROTO, nStdHandle:dword
WriteConsoleA PROTO, a1: Dword, a2: ptr Byte, a3: Dword, a4: ptr Dword, a5: Dword
ReadConsoleA PROTO, a1: Dword, a2: ptr Byte, a3: Dword, a4: ptr Dword, a5: Dword

.DATA
	str1 db "Enter an upper case character: ", 0
	str2 db 0Ah, "The lower case of entered character is: ", 0
	str3 db 0Ah, "That's not an upper case letter...Enter again: ", 0
	char db ?
	x dd ?

.CODE
main PROC
	mov bl, "A"
	mov bh, "Z"

	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset str1, lengthof str1, offset x, 0
	jmp No

	Again:
	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset str3, lengthof str3, offset x, 0

	No:
	Invoke getstdhandle, -10
	Invoke ReadConsoleA, eax, offset char, lengthof char, offset x, 0

	;----- Input Validation -----
	cmp char, bl
	jl Again
	cmp char, bh
	jg Again

	;Output:
	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset str2, lengthof str2, offset x, 0
	Invoke getstdhandle, -11
	Invoke WriteConsoleA, eax, offset char, lengthof char, offset x, 0

Invoke ExitProcess, 0
main Endp
End main