.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
	valb_1 BYTE 'm'
	;valb_2 BYTE  1111d
	valb_3 DB  +127			
	;valb_3a DB  256      	
	valb_4 BYTE -128
	valb_4a BYTE -129		
	valb_4b SBYTE -128			 
	valb_5 BYTE 255
	valb1_6 SBYTE -129
	valb1_7 SBYTE +127 
    valb_8 SBYTE 'o'    
	;valb1_9 SBYTE -Ah

.CODE
main PROC
	mov edi,offset valb_1 
	mov al,valb_1 

Invoke ExitProcess, 0

main ENDP
END main