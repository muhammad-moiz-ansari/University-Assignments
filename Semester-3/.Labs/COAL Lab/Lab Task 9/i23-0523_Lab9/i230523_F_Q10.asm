include irvine32.inc

.DATA
	arr db "hello", 0
	arrs = lengthof arr - 1

.CODE
reverse Proc
	mov ecx, arrs
	mov esi, offset arr
	mov eax, 0

	L1:
		mov al, byte ptr [esi]
		push eax
		inc esi
	Loop L1

	mov ecx, arrs
	mov esi, offset arr

	L2:
		pop [esi]
		inc esi
	Loop L2

	ret
reverse Endp

main Proc
	call reverse
	mov ecx, arrs
	mov edi, 0

	mov edx, offset arr		; Move the address of the string into EDX
	call WriteString			; Call the WriteString procedure to print the string
	call CrLf					; Move to the next line after printing

	exit						; Exit the program

main endp
end main
