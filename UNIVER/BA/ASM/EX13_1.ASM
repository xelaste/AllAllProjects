title EX13_1
;--------------------------------------------------------
dseg segment
   N dw 3
   array1 db 9 dup (1)
   array2 db 1,2,3,4,5,6,7,8,9
   new_line  db 0dh,0ah,'$' ;cr+lf ascii codes
   SUM1  dw 0
   SUM2  dw 0
   LENTH dw 0
   msg_KESEM          db 'KESEM=1$'
   msg_NOT_KESEM      db 'KESEM=0$'
   msg_FIRST_MATRIXE  db 'The first matrixe$'
   msg_SECOND_MATRIXE db 'The second matrixe$'
dseg ends
;------------------------------------------------------
sseg segment stack
     dw 100 dup(?)
sseg ends
;------------------------------------------------------
cseg segment
     assume cs:cseg,ds:dseg,ss:sseg
;--------- ROUTINE TO PRINT A NEW LINE -------------------
writeln proc
        mov dx, offset new_line
        mov ah,9
        int 21h
        ret
writeln endp
;------------ROUTINE TO PRINT A STRING -------------------------
write proc
      mov ah,9
      int 21h
      call writeln
      ret
write endp
;------------------------------------------------------------------
check_matrixe proc
mov bp,sp
mov bx,[bp+2] ;pointer to matrixe
mov cx,[bp+4] ;value of N
mov LENTH,cx
mov SUM1,0
LOOPD1:  ;compute sum of the main diagonal
xor ah,ah
mov al,[bx]
add SUM1,ax
add bx,LENTH
inc bx
loop LOOPD1
;---------------------------------------------------
mov bp,sp
mov bx,[bp+2] ;pointer to matrixe
mov cx,LENTH  ;value of N
LOOPD2:  ;compute sum of the second diagonal
add bx,LENTH
sub bx,1
xor ah,ah
mov al,[bx]
add SUM2,ax
loop LOOPD2
mov ax,SUM1
cmp ax,SUM2
jne NOT_KESEM
;-------------- LINES: ;checking lines of matrixe
mov bp,sp
mov bx,[bp+2] ;pointer to matrixe
mov cx,LENTH  ;value of N
mov si,LENTH
NEXT_LINE:
mov SUM2,0
mov cx,LENTH  ;value of N
NEXT_ITEM:
xor ah,ah
mov al,[bx]
add SUM2,ax
inc bx
loop NEXT_ITEM
mov ax,SUM1
cmp ax,SUM2
jne NOT_KESEM
dec si
jnz NEXT_LINE
;-------------- COLUMNS: checking the columns of the matrixe
mov bp,sp
mov si,LENTH
NEXT_COL:
mov SUM2,0
mov cx,LENTH  ;value of N
mov bx,[bp+2] ;pointer to matrixe
NEXT_ROW:
xor ah,ah
mov al,[bx+si]
add SUM2,ax
add bx,LENTH
loop NEXT_ROW
mov ax,SUM1
cmp ax,SUM2
jne NOT_KESEM
dec si
jnz NEXT_COL
KESEM:
mov dx,offset msg_KESEM
call write
jmp STOP_SHECK
NOT_KESEM:
mov dx,offset msg_NOT_KESEM
call write
STOP_SHECK:
ret
check_matrixe endp
;-----------------------------------------------------------------
main proc far
     push ds     ; /---------------------------\
     xor  ax,ax  ; | Save return address to Dos|
     push ax     ; \---------------------------/
     mov ax,dseg ;points the ds register to the
     mov ds,ax   ;data segment of this program
;=========================================================
mov dx,offset msg_FIRST_MATRIXE
call write
push N
push offset array1
call check_matrixe
pop N
pop ax
;--------------------------------------------------
mov dx,offset msg_SECOND_MATRIXE
call write
push N
push offset array2
call check_matrixe
pop N
pop ax
;*******************************************************************
finish: ret ;return from procedure "main"
;-------------------------------------------------------------------
main endp
cseg ends
end main ;do not forget the starting address
;---------------------------------------------------------------------
