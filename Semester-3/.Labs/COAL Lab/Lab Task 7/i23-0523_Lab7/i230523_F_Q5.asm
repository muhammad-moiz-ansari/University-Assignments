.386
.model flat, stdcall
.stack 4096

ExitProcess Proto, dwExitCode:Dword

.DATA
	rev_reg_value dd 4 dup(?)
	n = 12345678h
	code dd 10000000h
	scode dd 10h
	sscode dd 100h

	mr dd	  0000000Fh
	ml dd	 0F0000000h
	invert = 0FFFFFFFFh

.CODE
main PROC
	mov esi, offset rev_reg_value
	
	;;;;;;;; EAX ;;;;;;;;

	mov eax, n
	mov ecx, (type dword)
	L1:
		mov ebp, eax
		mov esp, eax

		and ebp, ml		;Masking
		and esp, mr

		mov edi, eax	;Saving value of eax

			mov eax, ebp	;Shifting ebp to right
			mov edx, 0
			div code
			mov ebp, eax

			mov eax, esp	;Shifting esp to left
			mul code
			mov esp, eax

		mov eax, edi	;Returning value to eax


		mov edi, invert		;Clearing value from right
		sub edi, mr
		and eax, edi

		mov edi, invert		;Clearing value from left
		sub edi, ml
		and eax, edi

		or eax, ebp		;Putting value
		or eax, esp
		
		mov edi, eax	;Saving value of eax

			mov eax, mr		;Shifting mr to left
			mul scode
			mov mr, eax

			mov eax, ml		;Shifting ml to right
			mov edx, 0
			mov esp, scode
			div esp
			mov ml, eax

			mov eax, code	;Dividing code
			mov edx, 0
			mov esp, sscode
			div esp
			mov code, eax

		mov eax, edi	;Returning value to eax

	dec ecx             ; Decrementing loop counter manually
    jnz L1  

	mov [esi], eax
	add esi, type dword

	;;;;;;;;;;;;;;;; EBX ;;;;;;;;;;;;;;;;

	mov code, 10000000h
	mov mr, 0000000Fh
	mov ml, 0F0000000h
	mov ebx, n
	mov ecx, (type dword)
	L2:
		mov ebp, ebx
		mov esp, ebx

		and ebp, ml		;Masking
		and esp, mr

			mov eax, ebp	;Shifting ebp to right
			mov edx, 0
			div code
			mov ebp, eax

			mov eax, esp	;Shifting esp to left
			mul code
			mov esp, eax

		mov edi, invert		;Clearing value from right
		sub edi, mr
		and ebx, edi

		mov edi, invert		;Clearing value from left
		sub edi, ml
		and ebx, edi

		or ebx, ebp		;Putting value
		or ebx, esp
		
			mov eax, mr		;Shifting mr to left
			mul scode
			mov mr, eax

			mov eax, ml		;Shifting ml to right
			mov edx, 0
			mov esp, scode
			div esp
			mov ml, eax

			mov eax, code	;Dividing code
			mov edx, 0
			mov esp, sscode
			div esp
			mov code, eax

	dec ecx             ; Decrementing loop counter manually
    jnz L2  

	mov [esi], ebx
	add esi, type dword

	;;;;;;;;;;;;;;;; ECX ;;;;;;;;;;;;;;;;

	mov code, 10000000h
	mov mr, 0000000Fh
	mov ml, 0F0000000h
	mov ecx, n
	mov edi, (type dword)
	L3:
		mov ebp, ecx
		mov esp, ecx

		and ebp, ml		;Masking
		and esp, mr

			mov eax, ebp	;Shifting ebp to right
			mov edx, 0
			div code
			mov ebp, eax

			mov eax, esp	;Shifting esp to left
			mul code
			mov esp, eax

		mov eax, invert		;Clearing value from right
		sub eax, mr
		and ecx, eax

		mov eax, invert		;Clearing value from left
		sub eax, ml
		and ecx, eax

		or ecx, ebp		;Putting value
		or ecx, esp
		
			mov eax, mr		;Shifting mr to left
			mul scode
			mov mr, eax

			mov eax, ml		;Shifting ml to right
			mov edx, 0
			mov esp, scode
			div esp
			mov ml, eax

			mov eax, code	;Dividing code
			mov edx, 0
			mov esp, sscode
			div esp
			mov code, eax

	dec edi             ; Decrementing loop counter manually
    jnz L3

	mov [esi], ecx
	add esi, type dword

	;;;;;;;;;;;;;;;; EDX ;;;;;;;;;;;;;;;;

	mov code, 10000000h
	mov mr, 0000000Fh
	mov ml, 0F0000000h
	mov edx, n
	mov ecx, (type dword)
	L4:
		mov ebp, edx
		mov esp, edx

		and ebp, ml		;Masking
		and esp, mr

		mov edi, edx	;Saving value of edx

			mov eax, ebp	;Shifting ebp to right
			mov edx, 0
			div code
			mov ebp, eax

			mov eax, esp	;Shifting esp to left
			mul code
			mov esp, eax

		mov edx, edi	;Returning value to edx

		mov edi, invert		;Clearing value from right
		sub edi, mr
		and edx, edi

		mov edi, invert		;Clearing value from left
		sub edi, ml
		and edx, edi

		or edx, ebp		;Putting value
		or edx, esp
		
		mov edi, edx	;Saving value of edx

			mov eax, mr		;Shifting mr to left
			mul scode
			mov mr, eax

			mov eax, ml		;Shifting ml to right
			mov edx, 0
			mov esp, scode
			div esp
			mov ml, eax

			mov eax, code	;Dividing code
			mov edx, 0
			mov esp, sscode
			div esp
			mov code, eax

		mov edx, edi	;Returning value to edx

	dec ecx             ; Decrementing loop counter manually
    jnz L4   

	mov [esi], edx
	add esi, type dword

Invoke ExitProcess, 0
main Endp
End main