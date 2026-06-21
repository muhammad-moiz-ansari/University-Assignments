include irvine32.inc

.DATA
	arr dw 8, 4, 3, 7, 6

	address dd ?

.CODE
bubblesort Proc

AgainWeGo:
	mov cx, 0
	mov [ebp+4], cx			;Reset swap local var to 0		
	dec dword ptr [ebp+8]	;decreasing size
	mov esi, [ebp+12]		;moving address of array
	mov ebx, 0				;initialize array index to zero
Loop1:
	mov ax,[esi]		;load number to ax
	cmp ax,[esi+2]		;compare with next number
	jle noswap				;no swap if already inorder

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
	je AgainWeGo				;if yes than make another pass

	ret 8
bubblesort Endp

main Proc
	mov eax, 0
	push offset arr 
	push lengthof arr
	sub esp, 4
	push ebp
	mov ebp, esp
	
	call bubblesort
	add esp, 8


	mov ecx, lengthof arr
	mov edi, 0
	L3:
		movzx eax, arr[edi]			; Move the address of the string into EDX
		call WriteInt			; Call the WriteString procedure to print the string
		call CrLf					; Move to the next line after printing
		add edi, 2
	Loop L3

	exit						; Exit the program

main endp
end main