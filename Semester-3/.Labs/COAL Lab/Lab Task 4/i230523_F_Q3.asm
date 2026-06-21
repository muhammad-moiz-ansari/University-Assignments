.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	arrB  byte  1, 2, 3, 4
	arrW  word  1122h, 3344h, 5566h
	arrDW dword 12345678h, 68374591h

	typeB	db ?
	typeW	dw ?
	typeDW	dd ?

	lengthB		db ?
	lengthW		dw ?
	lengthDW	dd ?

	sizeB	db ?
	sizeW	dw ?
	sizeDW	dd ?

	offsetB		db ?
	offsetW		dw ?
	offsetDW	dd ?

.CODE
main PROC
	mov typeB, type arrB
	mov typeW, type arrW
	mov typeDW, type arrDW

	mov lengthB, lengthof arrB
	mov lengthW, lengthof arrW
	mov lengthDW, lengthof arrDW

	mov sizeB, sizeof arrB
	mov sizeW, sizeof arrW
	mov sizeDW, sizeof arrDW

	mov eax, offset arrB
	mov ebx, offset arrW
	mov ecx, offset arrDW


INVOKE ExitProcess, 0

main ENDP
END main