.386
.model flat, stdcall
.stack 4096
ExitProcess Proto, dwExitCode:dword

.DATA
	mDATA dd 0
	mFLAGS dw 30523		;773Bh
	X db ?
	Y db ?

.CODE
main Proc
	;----- Operation-1 -----;
	mov ax, mflags
	and ax, 0F000h
	shr ax, 12
	mov X, al

	mov ax, mFLAGS
	and ax, 001Fh
	mov Y, al

	movsx ecx, X
	L1:
		shl mDATA, 1
		pushf

		shl mFLAGS, 1
		jc J1
		jmp else1
		J1:
			mov eax, 1
		jmp skip1
		ELSE1:
			mov eax, 0
		Skip1:
		OR mDATA, eax

		popf
	Loop L1

	;----- Operation-2 -----;

	movsx ecx, Y
	L2:
		shr mDATA, 1

		jc J2
		jmp else2
		J2:
			mov eax, 8000h
		jmp skip2
		ELSE2:
			mov eax, 0
		Skip2:
		OR mDATA, eax
	Loop L2

Invoke EXitProcess, 0
main Endp
End main