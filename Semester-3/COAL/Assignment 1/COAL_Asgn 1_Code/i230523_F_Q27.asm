.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
	arr BYTE 'moiz ansari'

.CODE
main PROC
	arrsize = lengthof arr

	mov esi, offset arr
	mov ecx, arrsize

	L1:
		mov ah, [esi]
		CMP ah, 20h		;Compares the character with space char
		jz SKIP			;Skips if space is there

		mov al, [esi]
		sub al, 20h
		mov [esi], al

		SKIP:
		inc esi

	Loop L1

Invoke ExitProcess, 0

main ENDP
END main