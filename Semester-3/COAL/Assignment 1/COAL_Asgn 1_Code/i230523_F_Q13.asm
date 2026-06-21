.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    bval1 BYTE 5
	bval2 BYTE 7
	wval1 WORD 0ABCDH
	wval2 word 01234h

.CODE
main PROC
	mov al,bval1
	mov bl,bval2
	xchg al,bl				;
	mov bval1,bl
	mov bval2,al
	mov cx,wval1
	xchg cx,wval2			
	mov wval2,cx

Invoke ExitProcess, 0

main ENDP
END main