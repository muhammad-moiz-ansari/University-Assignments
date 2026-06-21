; Name:    M. Moiz Ansari
; Roll No: 23i-0523
; Section: F

include irvine32.inc
include macros.inc

StudentRec STRUCT
	pname db 20 dup(?)
	id db 10 dup(?)
	age db 0
	grade db 3 dup(?)
StudentRec ENDS

.DATA
	students StudentRec 2 dup(<>)

	num db ?
	isPrime db 1

.CODE
main Proc
	;call Q1
	;call Q2
	call Q3

	exit
main Endp

Q1 Proc
	mov ecx, 2
	mov esi, offset students
	mov ebp, 1
	L1:
		mov ebx, ecx
		mov eax, ebp
		mWrite 0Ah, " "
		mWrite "Student ", 0
		call Writedec
		mWrite ":", 0
		mWrite 0Ah, " "

		mWrite "Enter name: ", 0
		mov edx, esi
		mov ecx, sizeof StudentRec.pname
		call Readstring

		add esi, sizeof StudentRec.pname
		mWrite "Enter roll no: ", 0
		mov edx, esi
		mov ecx, sizeof StudentRec.id
		call Readstring

		add esi, sizeof StudentRec.id
		mWrite "Enter age: ", 0
		call Readint
		mov [esi], al

		add esi, sizeof StudentRec.age
		mWrite "Enter Grade: ", 0
		mov edx, esi
		mov ecx, sizeof StudentRec.grade
		call Readstring

		add esi, sizeof StudentRec.grade
		inc ebp
		mov ecx, ebx
	dec ecx
	cmp ecx, 0
	jg L1
	;;Loop L1

	mWrite 0Ah, " "
	mWrite "Student Record:", 0
	
	mov esi, offset students
	mov ebp, 1
	mov ecx, 2
	L2:
		mov ebx, ecx
		mov eax, ebp
		mWrite 0Ah, " "
		mWrite "Student ", 0
		call Writedec
		mWrite ":", 0
		mWrite 0Ah, " "

		mWrite "Name: ", 0
		mov edx, esi
		call Writestring

		mWrite 0Ah, " "
		add esi, sizeof StudentRec.pname
		mWrite "Roll no: ", 0
		mov edx, esi
		call Writestring

		mWrite 0Ah, " "
		add esi, sizeof StudentRec.id
		mWrite "Age: ", 0
		mov al, [esi]
		call Writedec

		mWrite 0Ah, " "
		add esi, sizeof StudentRec.age
		mWrite "Grade: ", 0
		mov edx, esi
		call Writestring

		mWrite 0Ah, " "
		add esi, sizeof StudentRec.grade
		inc ebp
		mov ecx, ebx
	dec ecx
	cmp ecx, 0
	jg L2
	;;Loop L2

	ret
Q1 Endp


Q2 Proc
	Input:
	mWrite "Enter a number: ", 0
	call Readint
	mov num, al

	.if num < 0
		mWrite "Number is negative...enter again", 0
		jmp input
	.endif

	.if num == 1
		mov isprime, 0
		jmp finish
	.endif

	.if num == 2
		mov isprime, 1
		jmp finish
	.endif

	mov ecx, 2
	mov bl, 2
	movzx ax, num
	div bl
	mov bl, al
	.while cl <= bl
		mov al, num
		div cl
		.if ah == 0
			mov isprime, 0
			jmp finish
		.endif
		inc ecx
	.endw

	Finish:
	.if isprime == 1
		mWrite "The number is prime", 0Ah, 0
	.else
		mWrite "The number is not prime", 0Ah, 0
	.endif
	mWrite 0Ah, " "
	
	ret
Q2 Endp


Q3 Proc
	mov ecx, 1
	mov bl, 3
	mov bh, 5
	.while ecx <= 100
		movzx ax, cl
		div bl
		.if ah == 0
			movzx ax, cl
			div bh
			.if ah == 0		; Both 3 & 5
				mWrite "FizzBuzz", 0
			.else
				mWrite "Fizz", 0
			.endif
		 
		.else 
			 movzx ax, cl
			 div bh
			.if ah == 0
				mWrite "Buzz", 0
			.else
				mov eax, ecx
				call WriteDec
			.endif
		.endif
		mWrite "  ", 0

		inc ecx
	.endw

	ret
Q3 Endp
End main