.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
	ary WORD 'a',05678h, 001000001011b,567o
.CODE
main PROC
	mov ESI,0
    mov ax,ary[ESI * TYPE ary]	
	INC ESI
    mov BX,ary[ESI * TYPE ary]	
	INC ESI
    mov CX,ary[ESI * TYPE ary]	
    INC ESI          

Invoke ExitProcess, 0

main ENDP
END main