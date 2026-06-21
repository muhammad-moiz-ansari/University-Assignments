.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
        v1 db 1
		exp equ 2*5		
		;exp = 75		;error
		;exp = 9 		;error
								 
		txt textequ <"ABC">	
		txt equ <"abc">			
		txt2 equ <10*10>       
		symb equ exp            
		mv equ mov
		axmov equ <mv al,v1>	    
		axmove equ <mov al,v1>	
		VAL1 db 6		
		list db exp,txt,txt2,symb
		axmov equ <mv bl,v1>	

.CODE
main PROC
	mov edi,Offset VAL1
	mov ax,0
    mov al,v1
	mov dx,txt2 				
	axmov						
	axmove						
	axmov equ <mv cl,v1>		
	axmov
	;exp equ 255		;error		
	mov BX,exp

Invoke ExitProcess, 0

main ENDP
END main