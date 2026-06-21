include irvine32.inc

.DATA
	op1 db "Add:", 0Ah, 0
	op2 db "Subtract:", 0Ah, 0
	op3 db "Multiply:", 0Ah, 0
	op4 db "Divide:", 0Ah, 0

	;-- Q1 --
	num dw 0ABCDh

	;-- Q2 --
	cstr1 db "Enter two numbers: ", 0Ah, 0
	cstr2 db "Enter number 1: ", 0
	cstr3 db "Enter number 2: ", 0
	cstr4 db "Result: ", 0
	x1 dd ?
	x2 dd ?
	res1 dd 0
	result dd 0

	;-- Q3 --
	q3str1 db "Quotient: ", 0
	q3str2 db "Remainder: ", 0
	
	;-- Q4 --
	arr4size = 7
	arr4 db arr4size dup(?)
	index4 Label Byte
	index4dd dd ?
	num4 db ?

	q4str1 db "Enter the elements of array: ", 0Ah, 0
	q4str2 db "arr[", 0
	q4str3 db "]: ", 0
	q4str4 db 0Ah, "Enter value to find: ", 0
	q4str5 db "Enter the index: ", 0
	q4str6 db "Is value found? ", 0
	q4str7 db "True", 0
	q4str8 db "False", 0

	;q4str1 db "Enter size of array (1-10)"

	;-- Q5 --
	q5str1 db "Number: ", 0
	num5 db 10100011b
	res5 dw ?


	;-- Q6 --
	educationLevel db ?
	yearsOfExperience db ?
	hasRelevantCertification db ?
	hasProgrammingSkills dw ?

	strinp1 db "Enter your education level:", 0Ah, "1: High School", 0Ah, "2: Bachelor's", 0Ah, "3: Master's", 0Ah, "4: Ph.D", 0Ah, "Choose: ", 0;
	strinp2 db "Enter your years of professional experience: ", 0
	strinp3 db "Do you have a relevant certification (1 = Yes, 0 = No): ", 0
	strinp4 db "Do you have programming skills (1 = Yes, 0 = No): ", 0

	strif db "Congratulations! You are eligible for the senior software engineer position.", 0Ah, 0
	strelseif1 db "You are eligible for the software engineer position.", 0Ah, 0
	strelseif2 db "You are eligible for the junior software engineer position.", 0Ah, 0
	strelse db "Sorry, you are not eligible for any software engineering position at this time.", 0Ah, 0

	striff db "You have a relevant certification.", 0Ah, 0
	strelsee db "Consider obtaining a relevant certification for better career prospects.", 0Ah, 0
	
	strifff db "You are eligible for a management role.", 0Ah, 0

	;-- Q11 --
	maxsize = 100
	str11 dw maxsize dup(?)
	stri db "Enter some text: ", 0
	strl db "Length = ", 0
	strs db "Size = ", 0
	strt db "Type = ", 0
	length11 db ?
	size11 db ?
	type11 db 20 dup(?)
	
	t1 db "Byte", 0
	t2 db "Word", 0
	t3 db "Double Word", 0
	t4 db "Quadword", 0

.CODE
Q1 Proc
	mov ebp, 0
	mov edi, 0
	mov ax, num
	mov bx, num
	mov cx, num
	mov dx, num
	mov bp, num
	mov di, num

	rol ax, 4
	ror di, 8

	shl bx, 4
	sal cx, 4

	shr dx, 4
	sar bp, 4


	ret
Q1 Endp

takeinput Proc
	;Input;
	mov edx, offset cstr1
	call WriteString

	mov edx, offset cstr2
	call WriteString
	mov eax, 0
	call ReadInt
	mov x1, eax

	mov edx, offset cstr3
	call WriteString
	mov eax, 0
	call ReadInt
	mov x2, eax

	ret
takeinput Endp


Q2 Proc
	mov edx, offset op3
	call Writestring

	call takeinput

	;Calculation;
	mov eax, x1
	mov edx, 0
	imul x2

	mov res1, edx
	mov result, eax

	;Output;
	mov edx, offset cstr4
	call WriteString
	;mov eax, res1
	;call WriteInt
	mov eax, result
	call WriteInt
	call CrLf
	call CrLf

	ret
Q2 Endp


Q3 Proc
	mov edx, offset op4
	call Writestring

	call takeinput

	;Calculation;
	mov eax, x1
	mov edx, 0
	idiv x2

	mov res1, edx
	mov result, eax

	;Output;
	mov edx, offset q3str1
	call WriteString
	mov eax, result
	call WriteInt
	call CrLf

	mov edx, offset q3str2
	call WriteString
	mov eax, res1
	call WriteInt
	call CrLf

	ret
Q3 Endp


Q4 Proc
	;Input;
	mov edx, offset q4str1
	call WriteString

	mov ecx, arr4size
	mov bl, 0
	mov esi, offset arr4
	L1:
		mov edx, offset q4str2
		call WriteString

		mov eax, 0
		mov al, bl
		call WriteDec

		mov edx, offset q4str3
		call WriteString

		mov eax, 0
		call Readint
		mov [esi], al

		inc esi
		inc bl
	Loop L1

	;Input-2;
	mov edx, offset q4str4
	call WriteString
	mov eax, 0
	call readInt
	mov num4, al

	mov edx, offset q4str5
	call WriteString
	mov eax, 0
	call readInt
	mov index4dd, eax
	call Crlf

	;Finding;
	mov edx, offset q4str6
	call Writestring

	mov esi, offset arr4
	add esi, index4dd
	mov bl, [esi]
	cmp bl, num4
	je J1
	jmp else1
	J1:
		mov edx, offset q4str7
		jmp skip
	else1:
		mov edx, offset q4str8
	skip:
	call Writestring 
	call crlf
		
	ret
Q4 Endp


Q5 Proc
	clc
	mov ax, 0
	mov al, num5
	mov res5, ax	; cf = 0
	shl res5, 1		; cf = 1

	mov edx, offset q5str1
	call Writestring
	mov eax, 0
	mov al, num5
	call writedec
	call Crlf

	mov edx, offset cstr4
	call Writestring
	mov eax, 0
	mov ax, res5
	call writedec
	call Crlf
	
	ret
Q5 Endp


Q6 Proc
	;---Input---;

	mov edx, offset strinp1
	call WriteString
	mov eax, 0
	call ReadInt
	mov educationLevel, al
	
	mov edx, offset strinp2
	call WriteString
	mov eax, 0
	call ReadInt
	mov yearsOfExperience, al
	
	mov edx, offset strinp3
	call WriteString
	mov eax, 0
	call ReadInt
	mov hasRelevantCertification, al
	
	mov edx, offset strinp4
	call WriteString
	mov eax, 0
	call ReadInt
	mov hasProgrammingSkills, ax
	

	;--Checking Nested Conditions--;

	mov al, educationLevel
	mov bl, yearsOfExperience
	mov cl, hasRelevantCertification
	mov bp, hasProgrammingSkills

	;IF
	cmp al, 3
	jb elseif11
	cmp bl, 5
	jb elseif11
	cmp cl, 1
	jne elseif11
	cmp bp, 1
	jne elseif11

	mov edx, offset strif
	jmp skip6

	ELSEIF11:
	cmp al, 2
	jb elseif22
	cmp bl, 3
	jb elseif22
	cmp bp, 1
	jne elseif22

	mov edx, offset strelseif1
	jmp skip6

	ELSEIF22:
	cmp al, 2
	jb elsee
	cmp bl, 2
	jb elsee

	mov edx, offset strelseif2
	jmp skip6

	ELSEE:
	mov edx, offset strelse

	Skip6:
	call Crlf
	call WriteString
	call Crlf

	;;;;;
	cmp cl, 1
	jne elseee
	;IFF
	mov edx, offset striff
	jmp skipp6
	ELSEEE:
	mov edx, offset strelsee
	Skipp6:
	call WriteString
	call Crlf

	;;;;;
	cmp al, 3
	jb endee
	cmp bl, 7
	jb endee

	mov edx, offset strifff
	call WriteString
	call Crlf

	ENDEE:

	ret
Q6 Endp


printoutput Proc
	mov edx, offset cstr4
	call WriteString

	mov eax, result
	call WriteInt
	call Crlf
	call Crlf

	ret
printoutput Endp


Q7 Proc
	mov edx, offset op1
	call Writestring

	call takeinput

	mov ebx, x1
	add ebx, x2
	mov result, ebx

	call printoutput
	
	ret
Q7 Endp


Q8 Proc
	mov edx, offset op2
	call Writestring

	call takeinput

	mov ebx, x1
	sub ebx, x2
	mov result, ebx

	call printoutput
	
	ret
Q8 Endp


Q9 Proc
	call Q2
	
	ret
Q9 Endp


Q10 Proc
	call Q3
	
	ret
Q10 Endp


Q11 Proc
	mov edx, offset stri
	call Writestring
	call Crlf

	mov edx, offset str11
	mov ecx, maxsize
	call ReadString
	call Crlf

	;Length
	mov ecx, maxsize
	mov esi, offset str11
	Ll:
		mov bl, [esi]
		cmp bl, 0
		je exitl

		inc esi
		inc length11
	Loop Ll
	exitl:

	;Size
	mov al, type str11
	mul length11
	mov size11, al

	;Type
	mov al, type str11
	mov ecx, 0

	cmp al, 1
	je jt1
	cmp al, 2
	je jt2
	cmp al, 4
	je jt3
	cmp al, 8
	je jt4
	
	Jt1:
		mov cl, lengthof t1
		mov edi, offset t1
		jmp skip11
	Jt2:
		mov cl, lengthof t2
		mov edi, offset t2
		jmp skip11
	Jt3:
		mov cl, lengthof t3
		mov edi, offset t3
		jmp skip11
	Jt4:
		mov cl, lengthof t4
		mov edi, offset t4
		jmp skip11

	skip11:
	mov esi, offset type11
	Looop:
		mov bl, [edi]
		mov [esi], bl
		inc esi
		inc edi
	Loop Looop


	;Print;
	mov edx, offset strl
	call Writestring
	mov eax, 0
	mov al, length11
	call WriteDec
	call Crlf

	mov edx, offset strs
	call Writestring
	mov eax, 0
	mov al, size11
	call WriteDec
	call Crlf

	mov edx, offset strt
	call Writestring
	mov edx, offset type11
	call WriteString
	call Crlf

	
	ret
Q11 Endp


main Proc
	;call Q1

	;call Q2

	;call Q3

	;call Q4

	;call Q5

	;call Q6

	;call Q7

	;call Q8

	;call Q9

	;call Q10

	call Q11

Invoke ExitProcess, 0
main Endp
End main