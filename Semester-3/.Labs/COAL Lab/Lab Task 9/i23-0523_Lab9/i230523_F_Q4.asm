include irvine32.inc

.DATA
	;;arr db "9 2 - 2 / 5 * 7 - 9 - 9 -", 0
	arr db "5 6 + 2 *", 0
	arrl = lengthof arr - 1
	answer dd ?

	str1 db "Output: ", 0
	address dd ?

.CODE
solvePostfix Proc
	pop address
	mov eax, 0
	mov [esp], eax
	mov [esp - 4], eax

	mov ecx, arrl
	mov ebx, 0
	mov esi, offset arr
	L1:
		mov bl, 20h			;SPACE ' '
		cmp [esi], bl
		je skip			;if space comes
		
		;Checking for operators
		mov bh, "+"
		cmp [esi], bh
		je operatorhandle
		mov bh, "-"
		cmp [esi], bh
		je operatorhandle
		mov bh, "*"
		cmp [esi], bh
		je operatorhandle
		mov bh, "/"
		cmp [esi], bh
		je operatorhandle
		mov bh, "%"
		cmp [esi], bh
		je operatorhandle


		;Push operand
		mov ebx, 0
		mov bl, [esi]
		sub bx, 48
		push ebx
		jmp skip

		operatorhandle:
		;    '+'    ;
		cmp bh, "+"
		jne minus

		pop ebx
		pop eax
		add eax, ebx
		push eax

		jmp skip
		;    '-'    ;
		minus:
		cmp bh, "-"
		jne multiply
		
		pop ebx
		pop eax
		sub eax, ebx
		push eax

		jmp skip
		;    '*'    ;
		multiply:
		cmp bh, "*"
		jne divide
		
		pop ebx
		pop eax
		mul ebx
		push eax

		jmp skip
		;    '/'    ;
		divide:
		cmp bh, "/"
		jne modulus
		
		mov edx, 0
		pop ebx
		pop eax
		div ebx
		push eax

		jmp skip
		;    '%'    ;
		modulus:
		cmp bh, "%"
		jne skip
		
		mov edx, 0
		pop ebx
		pop eax
		div ebx
		;mov al, ah
		;mov ah, 0
		push edx				;;;;;;;;;;;;;

		jmp skip
		skip:
		inc esi

		dec ecx
		cmp ecx, 0
		jne L1
	;Loop L1

	mov eax, [esp]
	mov answer, eax

	push address
	ret
solvePostfix Endp

main Proc
	call solvePostfix

	mov edx, offset str1			; Move the address of the string into EDX
	call WriteString			; Call the WriteString procedure to print the string

	mov eax, answer				; Move the address of the string into EDX
	call WriteInt				; Call the WriteString procedure to print the string
	call CrLf					; Move to the next line after printing



	exit						; Exit the program

main endp
end main