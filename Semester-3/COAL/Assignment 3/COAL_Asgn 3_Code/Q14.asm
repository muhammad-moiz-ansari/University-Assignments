include irvine32.inc

.DATA
	bval sbyte -125
	wval sword 0FF17h
	dval sdword 0FFFF1705h

	q1 byte ?
	r1 byte ?
	q2 word ?
	r2 word ?
	q3 dword ?
	r3 dword ?

	q db "Quotient = ", 0
	r db "Remainder = ", 0

.CODE
main Proc
	mov al, bval
	cbw
	mov bl, 5
	idiv bl
	mov q1, al
	mov r1, ah


	mov ax, wval
	cwd
	mov bx, 7
	idiv bx
	mov q2, ax
	mov r2, dx


	mov eax, dval
	cdq
	mov ebx, 6
	idiv ebx
	mov q3, eax
	mov r3, edx


	;---Output---;
	mov edx, offset q
	call WriteString
	movsx eax, q1
	call WriteInt
	call Crlf
	mov edx, offset r
	call WriteString
	movsx eax, r1
	call WriteInt
	call Crlf
	call Crlf
	
	mov edx, offset q
	call WriteString
	movsx eax, q2
	call WriteInt
	call Crlf
	mov edx, offset r
	call WriteString
	movsx eax, r2
	call WriteInt
	call Crlf
	call Crlf
	
	mov edx, offset q
	call WriteString
	mov eax, q3
	call WriteInt
	call Crlf
	mov edx, offset r
	call WriteString
	mov eax, r3
	call WriteInt
	call Crlf
	call Crlf
	

Invoke ExitProcess, 0
main Endp
End main