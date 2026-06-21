.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

.data
	 multiplicand dq 02140214h			;Hexa of assigned word
	 multiplier dw 0214h
	 result dq 0

.code
main PROC
	mov eax,0
	mov cx,32							;initialize bit count to 16
	mov dx, multiplier					;initialize bit mask
checkbit:
	shr dx,1
	jnc noadd							;skip addition if no carry
	mov eax, dword ptr[multiplicand]	;mov LSW of multiplicand to ax
	add dword ptr[result], eax			;add LSW of multiplicand to result
	mov ebx, dword ptr[multiplicand+4]	;mov MSW of multiplicand to bx
	adc dword ptr[result+4], ebx		;add MSW of multiplicand to result
noadd:
	shl dword ptr[multiplicand],1		;shift LSW multiplicand to left
	rcl dword ptr[multiplicand+4],1		;rotate MSW of multiplicand to left
Loop checkbit

Invoke ExitProcess, 0
main Endp
End main