.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.data
	data dw 66h, 0h, 045h, 5h, 040h, 2h, -025h, 3h, -010h, 011h

.code
Sort PROC
Start:
	mov cx, 0
	mov [ebp+4], cx			;Reset swap local var to 0		
	dec dword ptr [ebp+8]	;decreasing size
	mov esi, [ebp+12]		;moving address of array
	mov ebx, 0				;initialize array index to zero
loop1:
	mov ax,[esi]		;load number to ax
	cmp ax,[esi+2]		;compare with next number
	jbe noswap				;no swap if already inorder

	mov dx,[esi+2]		;load second element in dx
	mov [esi+2],ax		;store first number in second
	mov [esi],dx		;store second number in first
	mov dword ptr [ebp+4], 1				;flag that a swap has been done
noswap:
	inc bx				;advance bx to next index
	add esi, 2				;incrementing pointer
	cmp bx, [ebp+8]				;are we at last index
	jne loop1				;if not than compare next 2

	cmp dword ptr [ebp+4],1				;check if swap has been done
	je start				;if yes than make another pass

	ret 8
Sort Endp

main PROC
	mov eax, 0
	push offset data 
	push lengthof data
	sub esp, 4
	push ebp
	mov ebp, esp
	
	call sort
	add esp, 8

INVOKE ExitProcess,0
main ENDP
END main