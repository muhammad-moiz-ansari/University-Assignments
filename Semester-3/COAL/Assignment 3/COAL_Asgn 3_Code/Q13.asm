include irvine32.inc

.DATA
	arr db 0, 1, 2, 9, 3, 4, 5
	n db LENGTHOF arr
	max db ?

.CODE
FindMaxRec Proc
	push ebp
	mov ebp, esp

	;--if(n==1)--;
	mov bl, 1
	cmp n, bl
	je J1
	jmp else1
	J1:
		mov dl, arr[0]
		pop edi			;Pop n Discard
		ret 4
		
	Else1:

	movzx eax, n
	push eax

	dec n
	call FindMaxRec

	;--Finding Max--;
	mov bl, dl
	mov esi, [ebp+8]
	cmp esi, LENGTHOF arr	;Comparing n & LENGTHOF arr
	jne skip3
		mov [ebp], ebp
	Skip3:
	dec esi
	mov al, arr[esi]	;arr[n-1]

	cmp al, bl
	jg J2
	jmp else2
	J2:
		mov dl, al
	Else2:

	pop ebp
	ret 4
	
FindMaxRec Endp

main Proc
	mov eax, 0
	mov edx, 0
	call FindMaxRec

	mov max, dl
	movsx eax, max
	call WriteDec
	call Crlf


Invoke ExitProcess, 0
main Endp
End main