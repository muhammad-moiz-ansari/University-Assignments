include irvine32.inc

.DATA
	;--- Q1 --- 
	inp1 db 0Ah, "Enter x-corrdinate: ", 0
	inp2 db "Enter y-corrdinate: ", 0
	x db ?
	y db ?
	star db "*", 0

	;--- Q2 ---
	q2str1 db "---Choose any of the following colors---", 0Ah
	colors db "Black = 0", 0Ah, "Blue = 1", 0Ah, "Green = 2", 0Ah, "Cyan = 3", 0Ah, "Red = 4", 0Ah, "Magenta = 5", 0Ah, "Brown = 6", 0Ah, "Light Grey = 7", 0Ah, "Gray = 8", 0Ah, "Light Blue = 9", 0Ah, "Light Green = 10", 0Ah, "Light Cyan = 11", 0Ah, "Light Red = 12", 0Ah, "Light Magenta = 13", 0Ah, "Yellow = 14", 0Ah, "White = 15", 0 
	textcol db "Text color: ", 0
	textvar db ?
	bgcol db "Background color: ", 0
	bgvar db ?
	invalid db "Invalid input...Plz choose btw 0 & 15...(Now choose both again)", 0Ah, 0

	;--- Q3 ---
	inputstr db "Enter some text...", 0Ah, 0
	q3str db 100 dup(?)

	;--- Q4 ---
	q4input db "Enter you marks: ", 0
	q4input2 db "Invalid input...Enter you marks again: ", 0

	marks db ?
	q4output db "Unfortunately, your grade is "
	grade dw 0, 0, 0

.CODE

Q1 Proc
	;;Input;;
	mov edx, offset inp1
	call WriteString
	
	call ReadInt
	mov x, al

	mov edx, offset inp2
	call WriteString

	call ReadInt
	mov y, al
	call CrLf

	;;Print star;;
	call clrscr
	
	mov dh, y
	mov dl, x
	call gotoxy

	call colorsetting

	mov edx, offset star
	call WriteString
	call CrLf

	mov eax, 15
	call settextcolor

	ret
Q1 Endp

ColorSetting Proc
	;---Setting color---;
	mov eax, 0
	mov al, 16
	mul bgvar
	add al, textvar

	call SetTextColor

	ret
ColorSetting Endp

Q2 Proc
	;;Input;;
	mov edx, offset q2str1
	call WriteString
	call CrLf
	call CrLf


	;---Text color---;
	mov edx, offset textcol
	call WriteString

	mov eax, 0
	call ReadInt
	mov textvar, al

	;;;Validation:


	;---BG color---;
	mov edx, offset bgcol
	call WriteString

	mov eax, 0
	call ReadInt
	mov bgvar, al

	;;;Validation:
	

	ret
Q2 Endp

Q3 Proc
	mov edx, offset inputstr
	call WriteString

	mov edx, offset q3str
	mov ecx, 100
	call ReadString

	call clrscr

	mov dh, y
	mov dl, x
	call gotoxy

	call colorsetting

	mov edx, offset q3str
	call WriteString

	mov eax, 15
	call settextcolor

	ret
Q3 Endp

Q4 Proc

	mov edx, offset q4input
	call WriteString
	jmp hehe
	
	Again:
	mov edx, offset q4input2
	call WriteString

	hehe:
	mov eax, 0
	call ReadInt
	mov marks, al

	;---Checking Grade---
	mov al, marks

	cmp al, 100
	jg again
	cmp al, 90
	jg gradeA

	cmp al, 80
	jg gradeB
	
	cmp al, 70
	jg gradeC

	cmp al, 60
	jg gradeD
	
	cmp al, 50
	jg gradeE

	cmp al, 40
	jg gradeEe

	cmp al, 0
	jl again
	jmp gradeF




	GradeA:
	mov cl, "A"
	mov grade, cx
	jmp printit

	GradeB:
	mov cl, "B"
	mov grade, cx
	jmp printit

	GradeC:
	mov cl, "C"
	mov grade, cx
	jmp printit

	GradeD:
	mov cl, "D"
	mov grade, cx
	jmp printit
	
	GradeE:
	mov cl, "E"
	mov grade, cx
	jmp printit
	
	GradeEe:
	mov cx, "E-"
	mov grade, cx
	jmp printit
	
	GradeF:
	mov cl, "F"
	mov grade, cx

	printit:
	mov edx, offset q4output
	call WriteString
	call CrLf
	

	ret
Q4 Endp

main Proc
	call Q2

	call Q1
	
	call Q3
	
	call Q4



Invoke ExitProcess, 0
main Endp
End main