.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
     v db 0
	tval1 TBYTE 01234H   
	tval2 DT 80000000000000001234h
	tval3 TBYTE +1234   	
	tval4 TBYTE 1    		
	tval5 TBYTE -1   		
	val1 db 0EEH

.CODE
main PROC
	

Invoke ExitProcess, 0

main ENDP
END main