.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	arrW  word  1122h, 3344h, 5566h
	arrDW dword 12345678h, 68374591h

.CODE
main PROC


INVOKE ExitProcess, 0

main ENDP
END main