.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
	firstoffset dd $		
	list1 db -1,-2,-3, 'm'
	list1size= $-list1
	list2 dw 1,2, 27o,4,5, 20Bh
	list2size= ($-list2)/2
	list3 dd 00010111b,2,0Bh
	list3size= ($-list3)/4

.CODE
main PROC
	mov edi,Offset firstoffset
	mov ah,list1+3
    mov bh,list1size
    mov cx,list2
    mov dh,list2size
    mov dL,list3size
    mov esi,$

Invoke ExitProcess, 0

main ENDP
END main