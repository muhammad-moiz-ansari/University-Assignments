.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    bAry BYTE 010H,020h,030H
	wAry WORD 5 DUP(?),0 ,0
	string1 BYTE 0FFH,0FFH
	dAry DWORD 2 DUP(3 DUP(0)),0
	string2 BYTE 'ABCDEFGHIJKLMNOPQRSTUVWXYZ',0
	str2len= $-string2
	bAry2 BYTE 1,2,3,
			   4,5,6
		  BYte 4,5,6
    r dq 2 dup(5),2 dup('abcd')

.CODE
main PROC
	mov bl, LENGTHOF bAry		
	mov cl, LENGTHOF wAry		
	mov dl, LENGTHOF dAry		
	mov ah, LENGTHOF string2    
	mov bh, str2len				
	mov al, LENGTHOF bAry2
    mov bl, LENGTHOF r

Invoke ExitProcess, 0

main ENDP
END main