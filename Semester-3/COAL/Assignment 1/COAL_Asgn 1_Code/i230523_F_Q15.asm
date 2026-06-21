.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    bval1 DB 1,2, 23d
	Align 2
	wval2 DW 001000001011b
	bval2 db 05d
	Align dword 			
	dval3 DD 7FD03h
	Align 4
	val4 DB 'm'
	ALIGN WORD
	val5 DB 'a'
	pary DD bval1

.CODE
main PROC

Invoke ExitProcess, 0

main ENDP
END main