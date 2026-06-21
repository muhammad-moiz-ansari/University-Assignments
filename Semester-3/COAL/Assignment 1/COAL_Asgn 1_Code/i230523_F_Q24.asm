.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
	arr BYTE '!egaugnal ylbmessA eroda I'

.CODE
main PROC
	arrsize = lengthof arr

	mov ecx, arrsize / 2

	mov esi, offset arr
	mov edi, offset arr + arrsize - 1

	L1:
		mov al, [esi]
		mov ah, [edi]

		mov [esi], ah
		mov [edi], al

		inc esi
		dec edi

	Loop L1


Invoke ExitProcess, 0

main ENDP
END main