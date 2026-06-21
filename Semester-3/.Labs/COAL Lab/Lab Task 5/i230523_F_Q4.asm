.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	align byte
	var1 byte 12h
	align word
	var2 word 3456h
	align dword
	var3 dword 78ABCDEFh

.CODE
main proc
	

Invoke ExitProcess, 0
main ENDP
End main