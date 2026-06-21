.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	vbyte byte 12h
	align dword
	vdword dword 345678ABh

.CODE
main proc
	

Invoke ExitProcess, 0
main ENDP
End main