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
    r dq 2 dup(5),2 dup('abcd')

.CODE
main PROC
	mov bl, SIZEOF bAry					
	mov cl, SIZEOF wAry			
	mov dl, SIZEOF dAry			
	mov ah, SIZEOF string1		
	mov al, SIZEOF string2	     
    mov bl, SIZEOF r

Invoke ExitProcess, 0

main ENDP
END main