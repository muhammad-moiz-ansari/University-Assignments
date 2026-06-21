.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
     Ary1 BYTE 'm',29, 27o
     ary2 WORD 'a',05678h, 001000001011b

.CODE
main PROC
	 mov ESI, OFFSET Ary1
     mov al,[ESI]
     add ESI,1
     mov bl,[ESI]
     inc ESI
     inc BYTE PTR [ESI]	
     mov cl,[ESI]

     mov ESI, OFFSET Ary2
     mov ax,[ESI]
     add ESI,2
     mov bx,[ESI]
     inc ESI
     inc ESI
     inc WORD PTR [ESI]	
     mov cx,[ESI]

Invoke ExitProcess, 0

main ENDP
END main