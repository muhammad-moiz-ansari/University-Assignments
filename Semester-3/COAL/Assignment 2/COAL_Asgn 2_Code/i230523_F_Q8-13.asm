.386
.model flat, stdcall
.stack 4096
ExitProcess proto dwExitcode:dword

.DATA
	

.CODE
main PROC
; ------- Q - 8 ------- ;
		mov ax,0FFFEh
		add ax,0FC70h
		jc l1
	L1: jz L2
	L2: jo L3
	L3: js L4
	L4: jp L5
	L5:

; ------- Q - 9 ------- ;
		mov ax,07B1Ah
		sub ax,0CEEBh
		jc l_1
	L_1: jz L_2
	L_2: jo L_3
	L_3: js L_4
	L_4: jp L_5
	L_5:

; ------- Q - 10 ------- ;
		mov cx,0FBCDh
		add cx,0E4AAh
		jnc l__1
	L__1: jnz L__2
	L__2: jo L__3
	L__3: js L__4
	L__4: jnp L__5	;ERROR: L__5 not defined
	L__5:

; ------- Q - 11 ------- ;
		mov bx,0FABDh
		add bx,0684Ah
		jc l___1
	L___1: jz L___2
	L___2: jno L___3
	L___3: jns L___4
	L___4: jp L___5
	L___5: mov ah,04ch

; ------- Q - 12 ------- ;
		mov bx,0A5A5h
		not bx
		cmp bx,05A5Ah
		jz I1
	I1: je I2
	I2: jnz I3
	I3: jne I4
	I4:

; ------- Q - 13 ------- ;
	mov ecx,5
	mov ax,1
	I_1:
		inc ax
		dec ecx
		jcxz end_loop
	jmp I_1
	end_loop:


Invoke ExitProcess, 0
main Endp
End main