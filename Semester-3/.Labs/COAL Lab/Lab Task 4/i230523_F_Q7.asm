.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	var1 sbyte -7
	var2 sbyte 4,6,-7,-8,9
	var3 sword ?
	var4 sdword -6,-2
	var5 sword 3 dup(10)
	var6 sdword 5 dup(-30)

.CODE
main PROC
	

INVOKE ExitProcess, 0

main ENDP
END main