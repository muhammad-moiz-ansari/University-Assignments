.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	arrW  word  1122h, 3344h, 5566h
	n db 1

.CODE
main PROC
	;-- ODD --

	;mov bl, 1
	mov ecx, 3
L1:
inc arrW
inc arrW
	mov ax, [arrW]
	add ax, 9h
	mov [arrW], ax

Loop L1

INVOKE ExitProcess, 0

main ENDP
END main