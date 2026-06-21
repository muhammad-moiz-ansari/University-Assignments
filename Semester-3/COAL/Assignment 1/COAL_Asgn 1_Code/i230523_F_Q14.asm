.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    bary BYTE 0ABh,045O, 17h,25T,50q
	wary WORD 3456O,20Bh ,'cd'
	Dary dd 1776403o,'ABcd','ansa',0AB12CD34h
	Qary dq	12345678abcdefh,'AbCd'

.CODE
main PROC
	mov al,bary
	mov bl,bary+1
	mov cl,bary+2
	mov dl,bary+3
	

	mov ax,wary
	mov bx,wary+2
	mov cx,wary+6
	mov dx,wary+12
	
 	mov eax,dary+4
	;mov ebx,wary+8	;error
	;mov edx,wary	;error

Invoke ExitProcess, 0

main ENDP
END main