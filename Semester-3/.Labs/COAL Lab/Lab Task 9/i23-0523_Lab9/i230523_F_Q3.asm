include irvine32.inc

.DATA
	arr db "madam", 0
	arrl = lengthof arr - 1
	iseven db 0
	address dd ?

	output1 db "Palindrome", 0
	output2 db "Not a palindrome", 0


.CODE
Ispalindrome Proc
	pop address
	mov eax, 0
	mov [esp], eax
	mov [esp - 4], eax

	; ---Check if length is even or odd---
	mov eax, 0
	mov edx, 0
	mov ax, arrl
	mov bx, 2
	div bx
	mov ebx, eax

	cmp edx, 0
	je J1
	jmp else1
	J1:
		mov dl, 1
		mov iseven, dl
	else1:
	
	; Pushing half string
	mov ecx, ebx
	mov esi, offset arr
	mov dx, 0
	L1:
		mov dl, [esi]
		push dx
		inc esi
	Loop L1

	;;;;;
	mov dl, 1
	cmp iseven, dl
	je hehe
		inc esi
	hehe:

	mov ecx, ebx
	mov edx, 0
	L2:
		mov dl, [esi]
		cmp dx, [esp]
		je J2
		jmp else2
		J2:
			pop dx
		else2:
		inc esi
	Loop L2

	mov edx, 0
	cmp dx, [esp]
	je yes
	jmp no
	yes:
		mov bx, 1
		jmp finish
	no:
		mov bx, 0

	finish:
	push address
	ret
IsPalindrome Endp

main Proc
	Call IsPalindrome

	mov ax, 0
	cmp bx, ax
	je nopal

	mov edx, offset output1			; Move the address of the string into EDX
	call WriteString			; Call the WriteString procedure to print the string
	call CrLf					; Move to the next line after printing
	jmp boo

	nopal:
	mov edx, offset output2			; Move the address of the string into EDX
	call WriteString			; Call the WriteString procedure to print the string
	call CrLf					; Move to the next line after printing

	boo:

	exit						; Exit the program

main endp
end main