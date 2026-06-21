.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	var1 Sbyte -5
	var2 sbyte -10,3,4,5
	var3 sword ?
	var4 sdword ?,?
	var5 sword 5 dup(-30)
	var6 sdword 10 dup(-10)

.CODE
main PROC
	

INVOKE ExitProcess, 0

main ENDP
END main