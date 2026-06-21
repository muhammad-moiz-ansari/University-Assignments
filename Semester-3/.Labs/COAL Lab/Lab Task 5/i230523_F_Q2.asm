.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	var1 byte 11
	var2 word 2222
	var3 dword 00000000
	var4 dword 12345678

.CODE
main proc
	mov esi, offset var2
	mov edi, offset var4
	mov al, type var2
	mov bx, [esi + 2]	;edi + 2 is the address of var3

Invoke ExitProcess, 0
main ENDP
End main