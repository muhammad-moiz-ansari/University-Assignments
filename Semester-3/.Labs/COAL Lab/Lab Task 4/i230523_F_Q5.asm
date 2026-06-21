.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	arrW  word  1122h, 3344h, 5566h

.CODE
main PROC
	;ODD

	mov ax, [arrW+3]
	add ax, 1h
	mov [arrW+3], ax

INVOKE ExitProcess, 0

main ENDP
END main