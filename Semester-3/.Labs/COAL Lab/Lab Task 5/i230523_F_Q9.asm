.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.DATA
	dynamicArray db 1, 2, 3
	copyarray dword 3 DUP(?)
	dynamicPtr dword offset dynamicArray
	count = 0

.CODE
main proc
	mov ecx, 3
	
	mov dynamicptr,offset dynamicarray
	;mov eax, [esi]
	mov al, [dynamicPtr]
	mov [copyarray + 0], eax
	add dynamicPtr, type dynamicArray	

	mov esi, dynamicPtr
	mov eax, [esi]
	mov [copyarray + 4], eax
	add dynamicPtr, type dynamicArray	

	mov esi, dynamicPtr
	mov eax, [esi]
	mov [copyarray + 8], eax
	add dynamicPtr, type dynamicArray	

Invoke ExitProcess, 0
main ENDP
End main