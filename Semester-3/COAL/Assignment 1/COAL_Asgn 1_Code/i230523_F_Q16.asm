.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    bval1 DB 034h, 0101b
	wval2 DW 20Bh 
	dval3 DD 01111111110100000011b  

.CODE
main PROC
	mov esi,OFFSET bval1	
	mov ax, WORD PTR bval1	
	mov al, BYTE PTR wval2		 
	mov bx, WORD PTR dval3
	mov cx, WORD PTR [dval3+2]

Invoke ExitProcess, 0

main ENDP
END main