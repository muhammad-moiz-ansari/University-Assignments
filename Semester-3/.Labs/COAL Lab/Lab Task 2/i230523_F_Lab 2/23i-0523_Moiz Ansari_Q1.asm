.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC
	
	;---------- Q-1 ----------;
	MOV ax, 2		; al = 2, ah = 0
	MOV cx, 3		; cl = 3, ch = 0
	MOV bx, 10		; bl = 10, bh = 0
	MOV dx, 5		; dl = 5, dh = 0

	ADD ax, cx		; ax = 5, cx = 3
	SUB bx, dx		; bx = 5, dx = 5

	MOV al, 9
	MOV ah, 7
	MOV bl, 8
	MOV bh, 6
	MOV cl, 7
	MOV ch, 5
	MOV dl, 6
	MOV dh, 4

	ADD al, ch		; al = 14, ch = 5
	ADD ah, cl		; ah = 14, cl = 7
	
	SUB bl, dl		; bl = 2, dl = 6
	SUB bh, dh		; bh = 2, dh = 4


INVOKE ExitProcess, 0

main ENDP
END main