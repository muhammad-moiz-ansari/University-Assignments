.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
          DB   -5
    List1 DB 10, 041h ,'A', 00111111b	
    List2 BYTE 1,2,3,4
		  BYTE 0101b,00010111b,5
	      BYTE 8,10,11,12		 
	string BYTE 'ABC',0
	string2 BYTE "abc",0
	string3 BYTE "moiz 'INSIDE''singlequote",0
	string7 db 'ansari "INSIDE " doublequote',0


	string4 DB \			    ;\ line continuation character
			"Hello"

    ;string5 b  \	
 	; yte "hello"

	string5 \  
			DB "Hello again"
	list3 db 1,2,   \ ;no need of \ here
		    3,4


.CODE
main PROC
	mov edi,Offset List1
    mov al,list1-1
	mov al,List1+5
	mov bl,string+4
	mov cl,string2+3
	mov dl,string3+5
	mov ah,string4+1
	mov bh,string5+4
	mov ch,string7+3

Invoke ExitProcess, 0

main ENDP
END main