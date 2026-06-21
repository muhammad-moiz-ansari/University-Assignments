include irvine32.inc

.DATA
	arr db "((())())", 0
	str1 db "Balanced", 0
	str2 db "Not balanced", 0
	br1 = "("
	br2 = ")"
	bool db 0
	temp dd 0

.CODE
isValid Proc
	pop temp

	mov bl, br1
	mov bh, br2
	mov dl, 0

	mov eax, 0
	mov esi, offset arr
	mov [esp], dl

	cmp [esi], dl
	je finish

	mov ecx, lengthof arr

	L1:
		cmp [esi], bl
		je J1
		jmp else1
		J1:
			mov al, byte ptr [esi]
			push eax
			inc esi
			jmp skip
		else1:

		cmp [esi], bh
		je J2
		jmp else2
		J2:
			cmp [esp], dl	;if stack is empty
			je Jumps
			jmp elses
			Jumps:
				jmp finish
			elses:
				pop edi


		else2:

		inc esi
		skip:
	Loop L1
	
	cmp [esp], dl	;if stack is empty
	je J3
	jmp else3
	J3:
		mov bl, 1
		mov bool, bl
	else3:
		

	finish:

	push temp
	ret
isValid Endp

main Proc
	call isValid

	mov dl, 1
	cmp bool, dl
	je yes
	jmp no
	yes:
		mov edx, offset str1			; Move the address of the string into EDX
		jmp nooo
	no:
		mov edx, offset str2			; Move the address of the string into EDX

	nooo:
	call WriteString			; Call the WriteString procedure to print the string
	call CrLf					; Move to the next line after printing

	exit						; Exit the program

main endp
end main