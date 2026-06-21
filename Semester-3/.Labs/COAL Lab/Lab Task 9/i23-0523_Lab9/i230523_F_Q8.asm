include irvine32.inc

.DATA
	str1 db "Max = ", 0
	arr db 2, 9, 4, 6
	arrl = lengthof arr
	max db ?
	temp dd ?
	address dd ?

.CODE
Findmax Proc
	pop address

	mov esi, offset arr
	mov ecx, arrl
	L1:
		mov eax, 0
		mov al, [esi]
		push eax
		inc esi
	Loop L1

	mov ah, [esp]

	;Largest find
	mov ecx, lengthof arr
	L2:
		pop temp
		mov ebx, temp

		cmp bl, ah
		jg J1
		jmp else1
		J1:
			mov ah, bl
		else1:

	Loop L2
	mov max, ah

	push address
	ret
Findmax Endp

main Proc
	call Findmax

	mov edx, offset str1			; Move the address of the string into EDX
	call WriteString
	movzx eax, max			; Move the address of the string into EDX
	call WriteInt				; Call the WriteString procedure to print the string
	call CrLf						; Move to the next line after printing

	exit						; Exit the program

main endp
end main