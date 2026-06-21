.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
        v1 db 1
		exp textequ %(2*5)		
		exp textequ %(20)		
		txt textequ <"Message">
		txt2 textequ txt		
		move textequ <MOV>
		axmov textequ < move al,v1>
		msg db txt,txt2

.CODE
main PROC
	mov edi,Offset v1
	mov al,v1 
    axmov
    mov al,exp
    exp textequ %(30)					
    axmov textequ < move bl,v1>		
    axmov
    mov Cl,exp

Invoke ExitProcess, 0

main ENDP
END main