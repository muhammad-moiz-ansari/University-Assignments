.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    valb LABEL Byte
	valw LABEL WORD
	vald LABEL DWORD 
	;valq LABEL dq 		;error
	valt Tbyte 12345678abcdef123456h

.CODE
main PROC
	mov al,valb
	mov bx,valw
	mov ecx,vald

Invoke ExitProcess, 0

main ENDP
END main