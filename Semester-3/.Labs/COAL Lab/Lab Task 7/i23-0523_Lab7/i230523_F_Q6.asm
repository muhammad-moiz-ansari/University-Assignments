.386
.model flat, stdcall
.stack 4096

ExitProcess Proto, dwExitCode:Dword

.DATA
	mask1 dd 0000FFFFh
	mask2 dd 0FFFF0000h

.CODE
main PROC
	mov eax, 12345678h
	;;; (a) ;;;
	and eax, mask1

	mov eax, 12345678h
	;;; (b) ;;;
	or eax, mask2

Invoke ExitProcess, 0
main Endp
End main