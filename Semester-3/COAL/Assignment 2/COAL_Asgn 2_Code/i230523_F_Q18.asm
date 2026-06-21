.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.data
	string1 BYTE "Computer Organization & Assembly language",0
	len_str1 = ($ - string1 - 1)

.CODE
main PROC
	mov ecx, len_str1
	mov esi, OFFSET string1
L1:
	mov eax, 0
	mov al, [esi]
	inc esi
	PUSH eax
LOOP L1
	mov ecx, len_str1
	mov esi, OFFSET string1
L2:
	mov eax, 0
	pop eax
	mov [esi], byte PTR al
	inc esi
LOOP L2	

Invoke ExitProcess, 0
main Endp
End main