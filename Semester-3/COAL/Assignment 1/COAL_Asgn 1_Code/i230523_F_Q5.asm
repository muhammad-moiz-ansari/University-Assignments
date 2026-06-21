.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    dword1 DD 1
	dword2 DD -1
	dword3 DWORD -1
	dword4 DWORD 65536
	dword5 DD 'XY'
	dword6 DD 'EFGH'		
	List1 DWORD 012345678H,0011010011101011001011b,65	
	list4 DWORD 2 DUP(0AB123456H)

.CODE
main PROC
	mov edi,Offset dword1
	mov ebx, dword2
	mov ecx, dword5
	mov edx, dword6
    mov eax, List1+4
    mov ebx, list4+2
    mov ecx, List1+8
    mov ecx, dword5+4	

Invoke ExitProcess, 0

main ENDP
END main