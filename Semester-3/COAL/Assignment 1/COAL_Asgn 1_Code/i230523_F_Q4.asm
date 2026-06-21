.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    word1 DW 1
	word2 DW -1
	word3 SWORD -1
	word4 SWORD +1
	word5 DW 'AB'
	;word6 DW 'ABC'
	list1 DW 2 DUP(214h)		
	list2 DW 1024o,2
	list3 WORD 3 DUP(0)		
	list4 WORD 2 DUP(0AB12H)
	List5 WORD 01F2BH,01101011001011b, 523d
	list6 DW 3 DUP('AB')

.CODE
main PROC
	mov edi, offset list1
	;mov al, word1
	mov bx, List1+4
	mov cx, List2+1
	mov dx, List4+2
    mov ax, List6+1
    mov cx, word5+2
    mov cx, word5+4	

Invoke ExitProcess, 0

main ENDP
END main