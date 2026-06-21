.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.data
	temp db 0

.code
main Proc
	mov ax,0
	mov ecx,5
Outer:
	mov temp,cl
	mov ecx,3
Inner:
	add ax,1
Loop Inner
	mov cx,0
	mov cl,temp
Loop Outer

main ENDP
END main

Invoke ExitProcess, 0
main Endp
End main