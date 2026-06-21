INCLUDE Irvine32.inc

.data

ground BYTE "------------------------------------------------------------------------------------------------------------------------",0
ground1 BYTE "|",0ah,0
ground2 BYTE "|",0

temp byte ?

strScore BYTE "Your score is: ",0
score BYTE 0

xPos BYTE 20
yPos BYTE 20

xCoinPos BYTE ?
yCoinPos BYTE ?

inputChar BYTE ?

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
scores dw 20 dup(0)
;scores dw 20, 34, 57, 0, 9

;readtext db 100 dup(0)
readtext db "20,30,40,", 0
filename db "score.txt", 0
filehandle dd ?
bytesread dd ?
errormess db "Failed to open file!", 0
sbstr db "Score Board:", 0Ah, 0
dot db ". ", 0

address dd ?
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.code
main PROC

    ;;;; I dont know why this is giving bugs and not let the game work  :(
    
    ;;Open scores file;
    ;mov edx, offset filename
    ;call OpenInputFile
    ;mov filehandle, eax

    ;mov edx, offset readtext
    ;mov ecx, 20
    ;call ReadFromFile
    ;mov filehandle, eax
    ;jc showerror
    ;mov bytesread, eax
    ;mov eax, filehandle
    ;call CloseFile

    ;jmp skip
    ;ShowError:
    ;mov edx, offset errormess
    ;call Writestring
    ;call Crlf
    ;Skip:



    ; draw ground at (0,29):
    mov eax,blue ;(black * 16)
    call SetTextColor
    mov dl,0
    mov dh,29
    call Gotoxy
    mov edx,OFFSET ground
    call WriteString
    mov dl,0
    mov dh,1
    call Gotoxy
    mov edx,OFFSET ground
    call WriteString

    mov ecx,27
    mov dh,2
    l1:
        mov dl,0
        call Gotoxy
        mov edx,OFFSET ground1
        call WriteString
        ;inc dh
    loop l1


    mov ecx,27
    mov dh,2
    mov temp,dh
    l2:
        mov dh,temp
        mov dl,119
        call Gotoxy
        mov edx,OFFSET ground2
        call WriteString
        inc temp
    loop l2
    call DrawPlayer

    call CreateRandomCoin
    call DrawCoin

    call Randomize

    gameLoop:

        ; getting points:
        mov bl,xPos
        cmp bl,xCoinPos
        jne notCollecting
        mov bl,yPos
        cmp bl,yCoinPos
        jne notCollecting
        ; player is intersecting coin:
        inc score
        call CreateRandomCoin
        call DrawCoin
        notCollecting:

        mov eax,white (black * 16)
        call SetTextColor

        ; draw score:
        mov dl,0
        mov dh,0
        call Gotoxy
        mov edx,OFFSET strScore
        call WriteString
        mov al,score
        call WriteDec

        ; gravity logic:
        gravity:
        cmp yPos,27
        jg onGround
        ; make player fall:
        call UpdatePlayer
        inc yPos
        call DrawPlayer
        mov eax,80
        call Delay
        jmp gravity
        onGround:

        ; get user key input:
        call ReadChar
        mov inputChar,al

        ; exit game if user types 'x':
        cmp inputChar,"x"
        je exitGame

        cmp inputChar,"w"
        je moveUp

        cmp inputChar,"s"
        je moveDown

        cmp inputChar,"a"
        je moveLeft

        cmp inputChar,"d"
        je moveRight

        moveUp:
        ; allow player to jump:
        mov ecx,1
        jumpLoop:
            call UpdatePlayer
            dec yPos
            call DrawPlayer
            mov eax,70
            call Delay
        loop jumpLoop
        jmp gameLoop

        moveDown:
        call UpdatePlayer
        inc yPos
        call DrawPlayer
        jmp gameLoop

        moveLeft:
        call UpdatePlayer
        dec xPos
        call DrawPlayer
        jmp gameLoop

        moveRight:
        call UpdatePlayer
        inc xPos
        call DrawPlayer
        jmp gameLoop

    jmp gameLoop

    exitGame:

    mov esi, offset scores
    dec esi
    L3:
        inc esi
        mov ebx, 0
        mov bx, [esi]
        cmp ebx, 0          ;;;;Currently ignoring score = 0...poor guy
    jne L3
    movsx ax, score
    mov [esi], ax
    call sortscores

    call displayscores



    exit
main ENDP


SortScores Proc
    pop address

	mov eax, 0
	push offset scores
	push lengthof scores
	sub esp, 4
	push ebp
	mov ebp, esp

AgainWeGo:
	mov cx, 0
	mov [ebp+4], cx			;Reset swap local var to 0		
	dec dword ptr [ebp+8]	;decreasing size
	mov esi, [ebp+12]		;moving address of array
	mov ebx, 0				;initialize array index to zero
Loop1:
	mov ax,[esi]		;load number to ax
	cmp ax,[esi+2]		;compare with next number
	jg noswap				;no swap if already inorder

	mov dx,[esi+2]		;load second element in dx
	mov [esi+2],ax		;store first number in second
	mov [esi],dx		;store second number in first
	mov dword ptr [ebp+4], 1				;flag that a swap has been done
noswap:
	inc bx				;advance bx to next index
	add esi, 2				;incrementing pointer
	cmp bx, [ebp+8]				;are we at last index
	jne loop1				;if not than compare next 2

	cmp dword ptr [ebp+4],1				;check if swap has been done
	je AgainWeGo				;if yes than make another pass

    push address
	ret 16
SortScores Endp


DisplayScores Proc
    call Clrscr

    mov edx, offset sbstr
    call Writestring

    mov esi, 0
    mov eax, 0
    mov ecx, 1
    L1:
        mov ebx, 0
        mov bx, scores[esi]
        cmp ebx, 0          ;;;;Currently ignoring score = 0...poor guy
        je finish

        mov eax, ecx
        call WriteDec
        mov edx, offset dot
        call Writestring

        movsx eax, scores[esi]
        call WriteDec
        call Crlf

        add esi, type scores
        inc ecx
    jmp L1

    Finish:
    ret
DisplayScores Endp

DrawPlayer PROC
    ; draw player at (xPos,yPos):
    mov eax,yellow ;(blue*16)
    call SetTextColor
    mov dl,xPos
    mov dh,yPos
    call Gotoxy
    mov al,"X"
    call WriteChar
    ret
DrawPlayer ENDP

UpdatePlayer PROC
    mov dl,xPos
    mov dh,yPos
    call Gotoxy
    mov al," "
    call WriteChar
    ret
UpdatePlayer ENDP

DrawCoin PROC
    mov eax,yellow ;(red * 16)
    call SetTextColor
    mov dl,xCoinPos
    mov dh,yCoinPos
    call Gotoxy
    mov al,"."
    call WriteChar
    ret
DrawCoin ENDP

CreateRandomCoin PROC
    mov eax,55
    inc eax
    call RandomRange
    mov xCoinPos,al
    mov yCoinPos,27
    ret
CreateRandomCoin ENDP

End main