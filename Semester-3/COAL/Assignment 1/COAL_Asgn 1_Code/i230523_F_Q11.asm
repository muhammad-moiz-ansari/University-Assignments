.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    val1 db 1001b
	val2 db -10010011y
	val3 dw 1.0
	val4 db -34o	
	val5 dw 5732q
	val6 db 2.5	
	val7 db 1+'a'+4/2
	val8 dw 5*3/4*2+8
	val9 db -255
	;val4 dd 1.0	;error		
    wval WORD 0
	result word ?

.CODE
main PROC
	mov edi,Offset val1
	;mov ax,3.5		;error
	;mov bl,val2*2	;error
	;mov al,2*(128+1)	;error
	;mov cl, val3 - 1		;error
    ;mov cl,val1 + val1a	
	mov al,-45o						
	mov ax,'a'			
	mov ax,'ab'  						
	;mov ax,AB12h	;error		
	mov al,5*(-3)			
	mov al,-(5*3)	
	;mov al,(-3)5	;error
    ;mov al,val3	;error		
	;mov bx,val1	;error				
	;add bx,al		;error				
	mov result,bx			
	;mov result,bl	;error
	;add val1,val2	;error			
	;mov 3,val2		;error

Invoke ExitProcess, 0

main ENDP
END main