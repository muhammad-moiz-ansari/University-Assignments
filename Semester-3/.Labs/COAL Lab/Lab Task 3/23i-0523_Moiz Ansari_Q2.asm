.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	Var1 dw 010h
	Var2 dw 5566h
	Var3 dw 6261h, 64h
	Var4 dw 2211h, 030h
	Var5 dw 050h, 060h, 070h, 080h
	Var6 dw ?, ?
	Var7 dw 2 DUP(?)

.CODE
main PROC
	


INVOKE ExitProcess, 0

main ENDP
END main