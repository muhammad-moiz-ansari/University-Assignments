.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    list1 BYTE 1,0101b
	list2 BYTE 3 DUP(-2,00010111b )
	list3 DB 2 DUP(?,1, 'm')
	list4 BYTE 3 DUP('AB')
	list5 BYTE 2 DUP('moiz')

.CODE
main PROC
	mov edi,offset list1
	mov al, List2+2
	mov bl, List3+4
	mov cl, List4+3
	mov dl, List5+3

Invoke ExitProcess, 0

main ENDP
END main