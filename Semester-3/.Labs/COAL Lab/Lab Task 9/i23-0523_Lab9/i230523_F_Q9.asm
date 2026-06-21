include irvine32.inc

.DATA
	arr dw 101 dup(?)
	arrsize dw ?
	inputval dw ?

	str1 db "Enter the size of stack (0 - 100): ", 0
	str2 db "Out of range... Enter again (0 - 100): ", 0
	emptymess db "Oh no! STACK UNDERFLOW :( ", 0
	fullmess db "Oh no! STACK OVERFLOW :( ", 0
	disp1 db "Stack: [ ", 0
	disp2 db ", ", 0
	disp3 db " ]", 0
	peek1 db "Peek: ", 0

.CODE
CreateStack Proc
	mov eax, offset arr - 2
	mov ebp, eax

	;Message
	mov edx, offset str1		; Move the address of the string into EDX
	call WriteString			; Call the WriteString procedure to print the string
	jmp TakeInput

	AgainMessage:
	mov edx, offset str2		; Move the address of the string into EDX
	call WriteString			; Call the WriteString procedure to print the string

	TakeInput:
	mov eax, 0
	mov ax, arrsize		
	call ReadInt
	mov arrsize, ax
	call CrLf
	
	;----- Input Validation -----
	cmp arrsize, bx
	jl AgainMessage
	cmp arrsize, cx
	jg AgainMessage


	ret
CreateStack Endp

IsFull Proc
	mov dx, 0
	mov eax, offset arr
	mov ebx, 0
	mov bx, arrsize
	dec bx
	add bx, bx
	add eax, ebx

	cmp ebp, eax
	jne notfull
	mov dx, 1

	notfull:

	ret
IsFull Endp

IsEmpty Proc
	mov dx, 0
	mov eax, offset arr
	sub eax, 2

	cmp ebp, eax
	jne notempty
	mov dx, 1

	notempty:

	ret
IsEmpty Endp

Pushst Proc
	Call isFull
	cmp dx, 1
	je itsfull
		add ebp, 2
		mov dx, inputval
		mov [ebp], dx
		jmp ohh
	itsfull:
		Call CrLf
		mov edx, offset fullmess
		call WriteString
		call CrLf

	ohh:
	ret
Pushst Endp

Popst Proc
	Call isEmpty
	cmp dx, 1
	je itsempty
		sub ebp, 2
		jmp yaaay
	itsempty:
		Call CrLf
		mov edx, offset emptymess
		call WriteString
		call CrLf

	yaaay:
	ret
Popst Endp

Peekst Proc
	Call isEmpty
	cmp dx, 1
	je itsempty
		mov edx, offset peek1
		Call WriteString

		mov eax, 0
		mov ax, [ebp]	
		call WriteInt
		call CrLf
		jmp yaay
	itsempty:
		Call CrLf
		mov edx, offset emptymess
		call WriteString
		call CrLf

	yaay:
	ret
Peekst Endp

Display Proc
	mov edx, 0
	mov eax, 0
	mov edi, offset arr

	Call CrLf
	mov edx, offset disp1
	Call WriteString

	Call isEmpty
	cmp dx, 1
	je itsempty
	mov eax, 0

		PrintL:
			mov ax, [edi]
			Call WriteInt

			cmp edi, ebp
			je Exitploop

			mov edx, offset disp2
			Call WriteString

			add edi, 2
			jmp PrintL
		Exitploop:

	itsempty:
		mov edx, offset disp3
		Call WriteString
		Call CrLf

	ret
Display Endp

main Proc
	mov bx, 0
	mov cx, 100

	Call CreateStack

	mov bx, 3
	mov inputval, bx
	Call Pushst
	
	mov bx, 5
	mov inputval, bx
	Call Pushst

	mov bx, 7
	mov inputval, bx
	Call Pushst
	
	mov bx, 6
	mov inputval, bx
	Call Pushst
	
	mov bx, 4
	mov inputval, bx
	Call Pushst

	mov bx, 2
	mov inputval, bx
	Call Pushst

	Call Display

	Call Popst
	Call Popst
	Call Popst
	Call Popst
	Call Popst
	Call Popst
	
	Call Display

	exit						; Exit the program

main endp
end main