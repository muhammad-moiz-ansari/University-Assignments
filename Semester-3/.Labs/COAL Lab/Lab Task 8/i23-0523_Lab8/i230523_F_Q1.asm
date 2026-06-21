.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

.DATA
	num db 5

.CODE
main Proc
	mov dx, 0
	mov al, 1
	cmp num, al
	jnle J1
	mov dh, num
	jmp finish
J1:
	mov al, 2
	cmp num, al
	jne J2
	mov dl, num
	jmp finish
J2:
	mov bl, 2
	mov ecx, 0
	mov cl, num
	sub cl,  bl

	
	L1:
		mov ah, 0
		mov al, num
		div bl
		cmp ah, 0
		jne J3
		mov dh, num
		jmp finish
		J3:
		mov dl, num
		
		inc bl

	Loop L1


	finish:

Invoke EXitProcess, 0
main Endp
End main