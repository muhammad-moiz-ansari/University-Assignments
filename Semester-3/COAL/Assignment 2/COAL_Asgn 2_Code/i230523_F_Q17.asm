.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.data
	data dd 66h, 0h, 045h, 5h, 040h, 2h, -025h, 3h, -010h, 011h
	swap db 0
.code
	main PROC
Start:
	mov swap,0				;Reset swap flag to no swap
	mov ebx,0				;initialize array index to zero
loop1:
	mov eax,[ebx+data]		;load number to ax
	cmp eax,[ebx+data+4]	;compare with next number
	jge noswap				;no swap if already inorder

	mov edx,[ebx+data+4]	;load second element in dx
	mov [ebx+data+4],eax	;store first number in second
	mov [ebx+data],edx		;store second number in first
	mov swap,1				;flag that a swap has been done
noswap:
	add bx,4				;advance bx to next index
	cmp bx,36				;are we at last index
	jne loop1				;if not than compare next 2

	cmp swap,1				;check if swap has been done
	je start				;if yes than make another pass

	INVOKE ExitProcess,0
	main ENDP
	END main