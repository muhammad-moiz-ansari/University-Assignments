include irvine32.inc

.DATA
	arr db 3, 5, 7, 9, 11
	arrs = lengthof arr

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

	L3:
		movzx eax, arr[edi]			; Move the address of the string into EDX
		call WriteInt			; Call the WriteString procedure to print the string
		call CrLf					; Move to the next line after printing
		inc edi
	Loop L3

	

main endp
end main