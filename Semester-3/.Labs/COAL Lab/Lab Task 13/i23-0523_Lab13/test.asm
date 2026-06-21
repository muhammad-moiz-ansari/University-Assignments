.model small
.stack 100
.data

;triangle

a2 dw 40
a1 dw 40

b1 dw 40
b2 dw 40

c1 dw 40
c2 dw 40

.code

jmp start

clear proc

mov ax, 0
mov bx, 0
mov cx, 0
mov dx, 0

ret
clear endp

start:

main proc
mov ax, @DATA 

mov ds, ax
mov ax, 0

mov ax, 0
mov al, 13h
int 10h

call clear

mov ah, 06h         ; background
mov al, 0
mov cx, 0           ; x-axis
mov dx, 100000      ; y-axis
mov bh, 14h         ; color
int 10h

call clear


l1:
    mov ah, 0cH     ; for pixels
    mov al, 4h
    mov cx, a2      ; x axis
    mov dx, a1      ; y axis
    int 10h
 
    dec a2
    inc a1          ; print line
    inc bx
    cmp bx, 20

je j1
jne L1

j1:

call clear

l2:
    mov ah, 0cH     ; for pixels
    mov al, 4h
    mov cx, b2      ; x axis
    mov dx, b1      ; y axis
    int 10h
 
    inc b2
    inc b1          ; print line
    inc bx
    cmp bx, 20

je j2
jne L2

j2:

mov ax, a1
mov bx, a2

mov c1, ax
mov c2, bx

call clear

l3:
    mov ah, 0cH     ; for pixels
    mov al, 4h
    mov cx, c2      ; x axis
    mov dx, c1      ; y axis
    int 10h
 
    inc c2
    ;inc b1          ; print line
    inc bx
    cmp bx, 40

je j3
jne L3

j3:

; square

call clear



main endp

mov ah, 4ch
int 21h
end
