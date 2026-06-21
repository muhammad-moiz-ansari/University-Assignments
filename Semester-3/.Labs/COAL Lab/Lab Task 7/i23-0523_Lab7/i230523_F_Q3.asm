.386
.model flat, stdcall
.stack 4096

ExitProcess Proto, dwExitCode:Dword

.DATA
	n dw 8575h
	mask1 = 7000h
	mask1_2 = 7F0Fh
	mask3 = 0FFFh
	mask4 = 0FF0Fh

.CODE
main PROC
	;5 in AL
	;75 in AH
	;0575 in BX
	;8505 in CX

	mov ax, n
	or ax, mask1
	and ax, mask1_2

	mov bx, n
	and bx, mask3

	mov cx, n
	and cx, mask4

Invoke ExitProcess, 0
main Endp
End main