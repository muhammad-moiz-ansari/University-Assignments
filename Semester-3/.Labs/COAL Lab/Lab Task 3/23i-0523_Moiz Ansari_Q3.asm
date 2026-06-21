.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	Var1 byte	10h
	Var2 dw		5566h
	Var3 db		'abcd',0
	Var4 byte	11h, 22h, 30h
	Var5 word	50h, 60h, 70h, 80h
	Var6 db		?,?
	Var7 byte	4 DUP(?)

.CODE
main PROC
	


INVOKE ExitProcess, 0

main ENDP
END main