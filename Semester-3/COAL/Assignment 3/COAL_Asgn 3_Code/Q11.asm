include irvine32.inc

.DATA
	num dd 00100011
	intstr byte (SIZEOF num * 2) dup(0), 0

.CODE
main Proc	
	mov ecx, 8
	mov esi, offset intstr
	add esi, SIZEOF intstr - 2

	L1:
		mov eax, num
		mov edx, 0
		mov ebx, 10
		div ebx
		mov bl, dl
		mov num, eax

		and bl, 1
		cmp bl, 1
		je J1
		jmp else1
		J1:
			mov bh, 31h
			jmp skip1
		Else1:
			mov bh, 30h
		Skip1:
		mov [esi], bh
		dec esi

	Loop L1

	mov edx, offset intstr
	call WriteString
	call Crlf

Invoke ExitProcess, 0
main Endp
End main