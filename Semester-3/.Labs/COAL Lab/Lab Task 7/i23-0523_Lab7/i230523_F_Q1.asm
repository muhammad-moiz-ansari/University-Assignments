.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

.DATA
	arr1 db 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	arr2 db 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
	evenarr db 10 dup(?)
	oddarr db 10 dup(?)

.CODE
main Proc
	mov ecx, (lengthof arr1) + (lengthof arr2)
	mov esi, offset arr1
	mov edi, offset evenarr
	mov esp, offset oddarr

	L1:
		mov dx, 0
		mov ax, [esi]
		mov bx, 2
		div bx

		;cmp ah, 0
		cmp dx, 0

		mov bl, [esi]

		jz Evench
		jnz Oddch

		Evench:
			mov [edi], bl
			inc edi
			cmp dx, 0

		jz jumpeven
		
		Oddch:
			mov [esp], bl
			inc esp
			
		jumpeven:
		inc esi

	Loop L1

Invoke ExitProcess, 0
main ENDP
END main