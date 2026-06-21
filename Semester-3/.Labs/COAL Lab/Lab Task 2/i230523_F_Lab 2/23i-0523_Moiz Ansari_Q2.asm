.386
.model flat, stdcall
.stack 4026
ExitProcess proto, dwExitCode:dword

.DATA
	

.CODE
main PROC
	
	;---------- Q-2 ----------;
	MOV ax, 2		; al = 2, ah = 0
	MOV cx, 5		; cl = 5, ch = 0
	MOV bx, 10		; bl = 10, bh = 0
	MOV dx, 5		; dl = 5, dh = 0

	ADD ax, cx		; ax = 7, cx = 5
	SUB bx, dx		; bx = 5, dx = 5

	MOV al, 9
	MOV ah, 7
	MOV bl, 8
	MOV bh, 6
	MOV cl, 5
	MOV ch, 5
	MOV dl, 5
	MOV dh, 5

	ADD al, ch		; al = 14, ch = 5
	ADD ah, cl		; ah = 12, cl = 5
	
	SUB bl, dl		; bl = 3, dl = 5
	SUB bh, dh		; bh = 1, dh = 5


INVOKE ExitProcess, 0

main ENDP
END main