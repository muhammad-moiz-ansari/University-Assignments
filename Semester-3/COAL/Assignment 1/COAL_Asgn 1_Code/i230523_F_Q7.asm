.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    ;v3 db count		;error
    count=2*2+4-2		
	v1 db count			
	count= 00010111b
	v2 db count
    count2= 'A'
    v3 db count2
	count2='ABCD'
    ;count3= 'moiza'    ;error
	v4 dd count2			
	;fcount=2.5			;error		
	;CountMax=4294967296	;error	
	CountMax=4294967294		;;;NO error

.CODE
main PROC
	mov edi,Offset v1       
    count = 5	
	mov ax,0
	mov al,v1				
	mov bl,v2				
	mov cl,count			
	count=257
	;mov cl,count	;error		
	mov cx,count

Invoke ExitProcess, 0

main ENDP
END main