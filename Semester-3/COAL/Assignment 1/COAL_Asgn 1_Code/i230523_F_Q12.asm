.386
.model flat, stdcall
.stack 4026
ExitProcess Proto, dwExitcode: DWord

.DATA
    bval1 BYTE 16
	bv2 BYTE -16
	wval WORD 0

.CODE
main PROC
	movsx bx,al				
	movsx cx,bv2
	movsx eax,bv2
	movsx ebx,bval1
	movzx ecx,bv2
	movzx edx,bval1

Invoke ExitProcess, 0

main ENDP
END main