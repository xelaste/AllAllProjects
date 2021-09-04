title EX13_2
NIL EQU -1
;--------------------------------------------------------
dseg segment
           l1 dw 1
              dw offset l2
           l2 dw 2
              dw offset l3
           l3 dw 3
              dw offset l4
           l4 dw 4
              dw offset l5
           l5 dw 5
              dw offset l6
           l6 dw 6
           dw NIL
;---------------------------------------------------
   ARRAY dw 6 dup (0)
   SUM   dw 0
   NUM   db 5 DUP ('0'),'$' ;array for display numbers
   TEN   dw 10D
new_line  db 0dh,0ah,'$' ;cr+lf ascii codes
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
;----------ROUTINE FOR TRANSFORM NUM VALUE TO STRING FOR DISPLAY ---------
strval proc
mov bp,4
putzero:   ;put zero to string num
       mov NUM[bp],'0'
       dec bp
       cmp bp,0
       jge putzero
mov bp,4
        transform:
        mov dx,0
        div TEN
        add NUM[bp],dl
        dec bp
        cmp ax,0
        jne transform
        ret
strval endp
;-----------------------------------------------------------------
put_sum proc far
mov ax,SUM
add ax,[bx]
mov SUM,ax
mov array[si],ax
add si,2
mov bx,[bx+2]
cmp bx,NIL
je last_node
call put_sum
last_node:
ret
put_sum endp
;------------------------------------------------------------------
main proc far
     push ds     ; /---------------------------\
     xor  ax,ax  ; | Save return address to Dos|
     push ax     ; \---------------------------/
     mov ax,dseg ;points the ds register to the
     mov ds,ax   ;data segment of this program
;=========================================================
mov bx,offset l1
mov si,0
cmp bx,NIL
je finish ;list is empty
call put_sum
mov cx,6
mov si,0
print_array:
mov ax,array[si]
call strval
mov dx,offset NUM
call write
add si,2
loop print_array
;=========================================================
finish: ret ;return from procedure "main"
;-------------------------------------------------------------------
main endp
cseg ends
end main ;do not forget the starting address
;---------------------------------------------------------------------
