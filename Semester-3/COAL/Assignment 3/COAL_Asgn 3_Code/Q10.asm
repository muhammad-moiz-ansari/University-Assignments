include irvine32.inc

.DATA
	key byte -5, 2, 3, 0, -1, -4, 3, -2, 4, 6
	t1 dd 0
	t2 dw 0
	t3 dd 0
	count dd 0
	mess db "Hello World! This is text.", 0
	

.CODE
RotateRight PROC
	movsx ebp, al
	mov ebx, dword ptr [esi+4]
	mov eax, dword ptr [esi]
	mov dx, [esi+8]
	L2:
		movsx ecx, dh
		mov t3, ecx

		mov ecx, ebx
		shr ecx, 24
		mov t2, cx
		

		mov ecx, eax
		shr ecx, 24
		mov t1, ecx


		shl eax, 8
		shl ebx, 8
		shl dx, 8

		or eax, t3
		or ebx, t1
		or dx, t2

		dec bp
		cmp bp, 0
		jge L2
	;Loop L2

	mov dword ptr [esi+4], ebx
	mov dword ptr [esi], eax
	mov [esi+8], dx

	ret
RotateRight Endp

RotateLeft PROC
	movsx ebp, al
	mov ebx, dword ptr [esi+4]
	mov eax, dword ptr [esi]
	mov dx, [esi+8]
	L3:
		movsx ecx, dl
		shl ecx, 24
		mov t3, ecx

		mov ecx, eax
		shl ecx, 24
		shr ecx, 16
		mov t2, cx
		

		mov ecx, ebx
		shl ecx, 24
		mov t1, ecx


		shr eax, 8
		shr ebx, 8
		shr dx, 8

		or eax, t1
		or ebx, t3
		or dx, t2

		dec bp
		cmp bp, 0
		jge L3
	;Loop L2

	mov dword ptr [esi+4], ebx
	mov dword ptr [esi], eax
	mov [esi+8], dx

	ret
RotateLeft Endp

main Proc
	mov esi, offset mess
	mov edi, offset key
	mov ecx, lengthof mess - 1
	mov count, ecx

Start:
	mov count, ecx
	mov al, [edi]
	cmp al, 0
	jl negative
	jmp pos
Pos:
	call RotateRight
	jmp Checkit
Negative:
	mov bl, -1
	mul bl
	call RotateLeft

Checkit:
	add esi, 10

	mov ecx, count
Loop start


	mov edx, offset mess
	call WriteString
	call Crlf
	

Invoke ExitProcess, 0
main Endp
End main