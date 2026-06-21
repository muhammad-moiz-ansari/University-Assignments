.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

.data
	decimal_one BYTE "985123456789765"
	decimal_two BYTE "052052305230523"
	sum BYTE (SIZEOF decimal_one + 1) DUP(0),0

.code
main Proc
	mov esi,SIZEOF decimal_one - 1
	mov edi,SIZEOF decimal_one		; SIZEOF sum - 1
	mov ecx,SIZEOF decimal_one
	mov bh,0						; set carry value to zero

L1: mov ah,0						; clear AH before addition
	mov al,decimal_one[esi]			; get the first digit
	add al,bh						; add the previous carry
	aaa								; adjust the sum (AH = carry)

	mov bh,ah						; save the carry in carry1
	or bh,30h						; convert it to ASCII
	add al,decimal_two[esi]			; add the second digit
	aaa								; adjust the sum (AH = carry)

	or bh,ah						; OR the carry with carry1
	or bh,30h						; convert it to ASCII
	or al,30h						; convert AL back to ASCII
	mov sum[edi],al					; save it in the sum
	dec esi							; back up one digit
	dec edi
loop L1
	mov sum[edi],bh					; save last carry digit
	mov bx,0


Invoke EXitProcess, 0
main Endp
End main