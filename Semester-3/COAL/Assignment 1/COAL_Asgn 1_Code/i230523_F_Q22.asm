.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
     Ary1 BYTE 'm',2, 17h,4
     ary2 WORD 'a',05678h, 1024o,567o
     ary3 DWORD 'n',012345678h, 07FD03h,567o

.CODE
main PROC
	mov ESI, 0
    mov EDI, 3
    mov ECX, 2
    mov al,ary1[ESI+1]	
	mov ESI,1 * TYPE ary1
    mov bl,ary1[ESI+ECX-1]	
	mov ESI,2 * TYPE ary1
    mov cl,ary1[ESI]	
	
    mov ESI,0
    mov ax,ary2[ESI]	
	mov ESI,1 * TYPE ary2
    mov bx,ary2[ESI]	
	mov ESI,2 * TYPE ary2
    mov cx,ary2[ESI]		
     
    mov ESI,0
    mov eax,ary3[ESI]	
	mov ESI,1 * TYPE ary3
    mov ebx,ary3[ESI]	
	mov ESI,2 * TYPE ary3
    mov ecx,ary3[ESI]

Invoke ExitProcess, 0

main ENDP
END main