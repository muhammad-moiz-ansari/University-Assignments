include irvine32.inc

.DATA
	arr db "3 + 4 * 2", 0
	arrl = lengthof arr - 1
	outarr db arrl dup(?), 0
	temp db 30 dup(0)

	str1 db "Output: ", 0
	address dd ?

.CODE
convert Proc
	pop address
	mov eax, 0
	mov [esp], eax
	mov [esp - 4], eax

	mov ecx, arrl
	mov ebx, 0
	mov esi, offset arr
	mov edi, offset outarr
	mov ebp, -1
	L1:
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


		;Cancatenate operand
		mov bl, [esi]
		mov [edi], bl
		inc edi
		jmp skip

		operatorhandle:
		inc esi
		dec ecx
		;    '+'    ;
		cmp bh, "+"
		jne minus

		mov dh, "-"
		cmp [esp], dh
		je equalprecltr
		mov dh, "*"
		cmp [esp], dh
		je lowerprec
		mov dh, "/"
		cmp [esp], dh
		je lowerprec
		mov dh, "%"
		cmp [esp], dh
		je lowerprec

		jmp higherprec

		jmp skip
		;    '-'    ;
		minus:
		cmp bh, "-"
		jne multiply
		
		mov dh, "+"
		cmp [esp], dh
		je equalprecltr
		mov dh, "*"
		cmp [esp], dh
		je lowerprec
		mov dh, "/"
		cmp [esp], dh
		je lowerprec
		mov dh, "%"
		cmp [esp], dh
		je lowerprec
		
		jmp higherprec

		jmp skip
		;    '*'    ;
		multiply:
		cmp bh, "*"
		jne divide
		
		mov dh, "+"
		cmp [esp], dh
		je higherprec
		mov dh, "-"
		cmp [esp], dh
		je higherprec
		mov dh, "/"
		cmp [esp], dh
		je equalprecltr
		mov dh, "%"
		cmp [esp], dh
		je equalprecltr
		
		jmp higherprec

		jmp skip
		;    '/'    ;
		divide:
		cmp bh, "/"
		jne modulus
		
		mov dh, "+"
		cmp [esp], dh
		je higherprec
		mov dh, "-"
		cmp [esp], dh
		je higherprec
		mov dh, "*"
		cmp [esp], dh
		je equalprecltr
		mov dh, "%"
		cmp [esp], dh
		je equalprecltr
		
		jmp higherprec

		jmp skip
		;    '%'    ;
		modulus:
		cmp bh, "%"
		jne skip
		
		mov dh, "+"
		cmp [esp], dh
		je higherprec
		mov dh, "-"
		cmp [esp], dh
		je higherprec
		mov dh, "/"
		cmp [esp], dh
		je equalprecltr
		mov dh, "*"
		cmp [esp], dh
		je equalprecltr
		
		jmp higherprec


		;;;;;;;;;;;
		higherprec:
		cmp ebp, -1
		jne lowerprec2

		mov bl, bh
		mov bh, 0
		push bx
		jmp skip

		;;;;;;;;;;;
		lowerprec:
		pop dx
		inc ebp
		mov temp[ebp], dl

		jmp operatorhandle
		jmp skip

		lowerprec2:
		mov bl, bh
		mov bh, 0
		push bx

		mov bx, 0
		mov bl, temp[ebp]
		mov [edi], bx
		dec ebp

		cmp ebp, -1
		jne lowerprec2
		jmp skip

		;;;;;;;;;;;;;
		equalprecltr:
		pop dx
		inc ebp
		mov temp[ebp], dl

		mov bl, bh
		mov bh, 0
		push bx


		jmp skip

		skip:
		inc esi
		dec ecx
		cmp ecx, 0
		jne L1
	;Loop L1

	;;;Cancatenate all stack
	canst:
	mov dx, [esp]
	cmp dx, 0
	je theend
	mov dx, 20h
	mov [edi], dx
	inc edi
	pop dx
	mov [edi], dx
	inc edi
	jmp canst

	theend:
	mov eax, [esp]

	push address
	ret
convert Endp

main Proc
	call convert

	mov edx, offset str1			; Move the address of the string into EDX
	call WriteString			; Call the WriteString procedure to print the string

	mov edx, offset outarr				; Move the address of the string into EDX
	call WriteString				; Call the WriteString procedure to print the string
	call CrLf					; Move to the next line after printing



	exit						; Exit the program

main endp
end main