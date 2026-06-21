include irvine32.inc
include Macros.inc

.data
	str1 db "Enter the filename: ", 0
	str2 db "File created successfully! :)", 0
	errormessage db "File failed to open! :(", 0

	;--------- Q-1 ---------;
	filename db 100 dup(0)
	filehandle dd 1
	qdef1 db "Hello my name is Moiz_Ansari. My hometown is Wah-Cantt. My roll number is 23i-0523. I love assembly language and I mind repeating it.", 0
	buffsize1 = 500
	byteswritten1 dd ?
	buffer1 db buffsize1 dup(0)

	;--------- Q-2 ---------;
	bytesread1 dd ?
	countv db 0
	countc db 0
	countword db 0
	myname db 20 dup(?)
	hometown db 20 dup(?)
	rollno db 20 dup(?)

	;--------- Q-4 ---------;
	q4str1 db "Enter the text to append: ", 0
	q4str2 db "Appended Text: ", 0Ah, 0
	newfilename db "NewFile.txt", 0
	buffsize2 = 400
	buffer2 db buffsize2 dup(0)
	newtext db 100 dup(?)

.code
Q1 PROC
	;---------------------------- Q-1 ----------------------------;
	mov edx, offset str1
	call Writestring 

	mov edx, offset filename
	mov ecx, 96
	call ReadString

	mov esi, offset filename
	dec esi
	L1:
		inc esi
		mov al, [esi]
		cmp al, 0
		jne L1
	
	mov al, '.'
	mov ah, 't'
	mov bl, 'x'
	mov bh, 't'
	mov cl, 0
	mov [esi], al
	inc esi
	mov [esi], ah
	inc esi
	mov [esi], bl
	inc esi
	mov [esi], ah
	inc esi
	mov [esi], cl
	inc esi

	;--- Creating file ---;
	mov edx, offset filename
	call CreateOutputFile
	mov filehandle, eax

	cmp eax, 0
	je notcreated
		mov edx, offset str2
		call Writestring
		call Crlf

	notcreated:

	;--- Write file ---;
	mov eax, filehandle
	mov edx, offset qdef1
	mov ecx, buffsize1
	call WritetoFile
	jc errorcame
	mov byteswritten1, eax

	mov eax, filehandle
	call CloseFile




	jmp finish1
ErrorCame:
	mov edx, offset errormessage
	call Writestring
	call Crlf

Finish1:

	ret
Q1 Endp

Q2 Proc
	;---------------------------- Q-2 ----------------------------;
	
	mov edx, offset filename
	call OpenInputFile
	mov filehandle, eax

	mov eax, filehandle 
	mov edx, offset buffer1
	mov ecx, buffsize1
	call ReadFromFile
	jc errorcame
	mov bytesread1, eax
	mov eax, filehandle
	call CloseFile

	;---- Vowels & Consonants ----;

	mov ecx, bytesread1
	mov esi, offset buffer1
	L2:
		;Vowels;
		mov al, 'a'
		mov ah, 'e'
		mov bl, 'i'
		mov bh, 'o'
		mov dl, 'u'

		cmp [esi], al
		je vowel
		cmp [esi], ah
		je vowel
		cmp [esi], bl
		je vowel
		cmp [esi], bh
		je vowel
		cmp [esi], dl
		je vowel

		mov al, 'A'
		mov ah, 'E'
		mov bl, 'I'
		mov bh, 'O'
		mov dl, 'U'

		cmp [esi], al
		je vowel
		cmp [esi], ah
		je vowel
		cmp [esi], bl
		je vowel
		cmp [esi], bh
		je vowel
		cmp [esi], dl
		je vowel

		;Consonants;
		mov al, 'a'
		mov ah, 'z'
		mov bl, 'A'
		mov bh, 'Z'

		cmp [esi], al
		jl hehe
		cmp [esi], ah
		jl consonants
		Hehe:
		cmp [esi], bl
		jl none2
		cmp [esi], bh
		jl consonants
		
		Vowel:
			inc countv

		jmp none2
		Consonants:
			inc countc

		None2:
		inc esi

	Loop L2

	;---- Number of Words ----;
	mov ecx, bytesread1
	mov esi, offset buffer1
	mov al, ' '
	mov ah, '.'
	L3:
		cmp [esi], al
		je space
		cmp [esi], ah
		je dot
		jmp noneword
	Dot:
		inc esi 
	
	Space:
		inc countword

	Noneword:
	inc esi
	Loop L3

	;---- Extracting Text ----;
	mov ecx, bytesread1
	mov esi, offset buffer1
	mov al, ' '
	add esi, 17
	mov edi, offset myname
	L4:
		cmp [esi], al
		je next
		mov bl, [esi]
		mov [edi], bl
		inc esi
		inc edi
	Loop L4
	Next:

	add esi, 16
	mov edi, offset hometown
	L5:
		cmp [esi], al
		je nextt
		mov bl, [esi]
		mov [edi], bl
		inc esi
		inc edi
	Loop L5
	Nextt:

	add esi, 19
	mov edi, offset rollno
	L6:
		cmp [esi], al
		je nexttt
		mov bl, [esi]
		mov [edi], bl
		inc esi
		inc edi
	Loop L6
	Nexttt:


	movsx eax, countv
	call WriteDec
	call Crlf

	movsx eax, countc
	call WriteDec
	call Crlf

	movsx eax, countword
	call WriteDec
	call Crlf
	call Crlf

	mov edx, offset myname
	call WriteString
	call Crlf

	mov edx, offset rollno
	call WriteString
	call Crlf

	mov edx, offset hometown
	call WriteString
	call Crlf
	call Crlf

	jmp finish1
ErrorCame:
	mov edx, offset errormessage
	call Writestring
	call Crlf

Finish1:
	ret
Q2 Endp


Q4 Proc
	mov edx, offset filename
	call OpenInputFile
	mov filehandle, eax

	mov edx, offset buffer2
	mov ecx, buffsize2
	call ReadFromFile
	jc errorcame
	mov bytesread1, eax
	mov eax, filehandle
	call CloseFile

	;Print text;
	mov edx, offset buffer2
	call WriteString
	call Crlf

	;Write String;
	;--- Creating file ---;
	mov edx, offset newfilename
	call CreateOutputFile
	mov filehandle, eax

	cmp eax, 0
	je notcreated
	mov edx, offset str2
	call Writestring
	call Crlf

	call Crlf
	mov edx, offset q4str1
	call Writestring

	mov edx, offset newtext
	mov ecx, 100
	call ReadString
	call Crlf

	;--- Write on file ---;
	mov eax, filehandle
	mov edx, offset newtext
	mov ecx, 100
	call WriteToFile
	jc errorcame
	mov byteswritten1, eax
	mov eax, filehandle
	call CloseFile

	;Append;
	mov esi, offset buffer2
	dec esi
	mov al, 0
	L2:
		inc esi
		cmp [esi], al
		jne L2

	mov al, 0Ah
	mov [esi], al
	inc esi

	mov edi, offset newtext
	L1:
		mov al, [edi]
		cmp al, 0
		je dodo

		mov [esi], al
		inc esi
		inc edi
	jmp L1

	Dodo:

	mov edx, offset q4str2
	call Writestring

	mov edx, offset buffer2
	call Writestring
	call Crlf

	;Append in file;
	mov edx, offset newfilename
	call OpenInputFile
	mov filehandle, eax
	mov edx, offset buffer2
	mov ecx, buffsize2
	call WriteToFile
	jc errorcame
	mov byteswritten1, eax
	mov eax, filehandle
	call CloseFile


	notcreated:

	jmp finish1
ErrorCame:
	mov edx, offset errormessage
	call Writestring
	call Crlf

Finish1:

	ret
Q4 Endp


main Proc
	call Q1
	call Q2
	call Q4



exit
main Endp
End Main