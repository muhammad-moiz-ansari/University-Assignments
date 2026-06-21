.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.data
	Wvall WORD 0FFFFH
	saveFLag WORD 0

.code
main PROC
	mov ax, 0
	mov ax, Wvall
	add ax,1
	PUSHF			;store flag register
	POP saveFlag	;Cannot move flag register value to other register/or
					;to memory

	;Push Flag & pop to local could be used

	mov bx,saveFlag
	PUSHF
	mov cx, 0FFFFH
	add cx, 1		 ;will update flag register
	POPF

Invoke ExitProcess, 0
main Endp
End main