.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

.DATA
	decimal_two BYTE "052052305230523"
	decimal_one BYTE "985123456789765"
	diff BYTE (SIZEOF decimal_one) DUP(0), 0

.CODE
main Proc
	mov esi, OFFSET decimal_two
	dec esi
	mov edi, OFFSET decimal_one
	dec edi
	mov dl, 0

L2:
	inc esi
	inc edi
	mov al, [esi]
	cmp al, [edi]

	je L2
;Loop L2

	jg skipit
		mov dl, 1
	Skipit:



	mov esi, OFFSET decimal_two
	add esi, SIZEOF decimal_two - 1
	mov edi, OFFSET decimal_one
	add edi, SIZEOF decimal_one - 1
	mov ebp, OFFSET diff
	add ebp, SIZEOF diff - 1
	mov ecx, SIZEOF decimal_two
	mov bh, 0

	cmp dl, 0
	je L1
	xchg esi, edi

L1:
	mov ah, 0
	mov al, [esi]
	sub al, bh					;Subtracting borrow
	aas

	mov bh, ah
	mov ah, 0
	sub al, [edi]
	aas

	or bh, ah
	or al, 30h
	mov [ebp], al

	cmp bh, 0
	je skip1
		mov bh, 1
	skip1:

	dec esi
	dec edi
	dec ebp
Loop L1
	mov bh, 30h
	cmp dl, 0
	je skip
		mov bh, '-'
	Skip:
	mov [ebp], bh

Invoke EXitProcess, 0
main Endp
End main