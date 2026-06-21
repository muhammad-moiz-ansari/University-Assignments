.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	Var1 db 10h
	Var2 db 66h, 55h
	Var3 db 'abcd', 0
	Var4 db 11h, 22h, 30h
	Var5 db 50h, 60h, 70h, 80h
	Var6 db ?, ?
	Var7 db 4 DUP(?)

.CODE
main PROC
	



INVOKE ExitProcess, 0

main ENDP
END main