.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    bval1 DB 'm'
	wval2 DW 0ABCDH,'o'  
	dval3 DD 07FD03h
	qval4 QWORD 01243567812435678H
	tval5 tbyte -1

.CODE
main PROC
	mov al, TYPE bval1
	mov bl, TYPE wval2
	mov cl, TYPE dval3
	mov dl, TYPE qval4
	mov ah, TYPE tval5

Invoke ExitProcess, 0

main ENDP
END main