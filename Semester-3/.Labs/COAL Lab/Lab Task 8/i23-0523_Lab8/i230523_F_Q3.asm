.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

GetStdHandle PROTO, nStdHandle: DWORD
WriteConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ReadConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword

.data
	str1 db "Enter character: ", 0
	str2 db 0Ah, "The character entered is: ", 0
	num db ?
	x dd ?

.code
main proc
	invoke getstdhandle, -11
	invoke WriteConsoleA, eax, offset str1, lengthof str1, offset x, 0
	invoke getstdhandle, -10
	invoke ReadConsoleA, eax, offset num, lengthof num, offset x, 0
	invoke getstdhandle, -11
	invoke WriteConsoleA, eax, offset str2, lengthof str2, offset x, 0
	invoke getstdhandle, -11
	invoke WriteConsoleA, eax, offset num, lengthof num, offset x, 0

Invoke EXitProcess, 0
main Endp
End main