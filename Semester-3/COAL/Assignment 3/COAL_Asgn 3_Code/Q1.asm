.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

.data
	 multiplicand dd 0214h		;Hexa of assigned word
	 multiplier dw 05AAh
	 result dd 0

.code
main PROC
	mov eax,0
	mov cx,16							;initialize bit count to 16
	mov dx, multiplier					;initialize bit mask
checkbit:
	shr dx,1
	jnc noadd							;skip addition if no carry
	mov ax, word ptr[multiplicand]		;mov LSW of multiplicand to ax
	add word ptr[result],ax				;add LSW of multiplicand to result
	mov bx, word ptr[multiplicand+2]	;mov MSW of multiplicand to bx
	adc word ptr[result+2],bx			;add MSW of multiplicand to result
noadd:
	shl word ptr[multiplicand],1		;shift LSW multiplicand to left
	rcl word ptr[multiplicand+2],1		;rotate MSW of multiplicand to left
Loop checkbit

Invoke ExitProcess, 0
main Endp
End main