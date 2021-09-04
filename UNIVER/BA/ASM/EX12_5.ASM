title EX12_5
;--------------------------------------------------------
ARRAY_SIZE EQU 10D
ZERO EQU '0'
;--------------------------------------------------------
dseg segment
   array db ARRAY_SIZE DUP (?)
   NUM   db 5          DUP ('0'),'$' ;array for display results
   new_line  db 0dh,0ah,'$' ;cr+lf ascii codes
   msg_sum   db 'sum=$'
   msg_avg   db 'avg=$'
   msg_found db 'THERE IS AT LEAST ONE ITEM EQUAL TO AVERAGE$'
   msg_index db 'INDEX=$'
   msg_not_found db 'THERE IS NONE ITEM EQUAL TO AVERAGE$'
   INDEX dw 0
   AVG   dw 0
   TEN   dw 10D
   Count dw ARRAY_SIZE
dseg ends
;------------------------------------------------------
sseg segment stack
     dw 100 dup(?)
sseg ends
;------------------------------------------------------
cseg segment
     assume cs:cseg,ds:dseg,ss:sseg
;------------ROUTINE TO PRINT A NEW LINE -------------------------
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
      ret
write endp
;----------ROUTINE FOR TRANSFORM NUM VALUE TO STRING FOR DISPLAY ---------
strval proc
mov bx,4
putzero:   ;put zero to string num
       mov NUM[bx],ZERO
       dec bx
       cmp bx,0
       jge putzero
mov bx,4
        transform:
        mov dx,0
        div TEN
        add NUM[bx],dl
        dec bx
        cmp ax,0
        jne transform
        ret
strval endp
;----------------------------------------------------------
main proc far
     push ds     ; /---------------------------\
     mov ax,0    ; | Save return address to Dos|
     push ax     ; \---------------------------/
     mov ax,dseg ;points the ds register to the
     mov ds,ax   ;data segment of this program
;=========================================================
mov array[0],10    ;
mov array[1],12    ;
mov array[2],35    ;
mov array[3],53    ;
mov array[4],61    ;
mov array[5],100   ; starting the array
mov array[6],110   ;
mov array[7],90    ;
mov array[8],45    ;
mov array[9],16    ;
;=============================================================
mov bx,0
calc_sum:        ;calculation sum of array elements
mov ax,0         ;
mov al,array[bx]
add AVG,AX
inc bx           ;increment index
cmp bx,ARRAY_SIZE
jb calc_sum      ;do while bx<ARRAY SIZE

mov ax,AVG
call strval
call writeln
mov dx,offset msg_sum
call write
mov dx,offset NUM
call write
;==============================================================
mov ax,AVG        ; /---------------------------------\
mov dx,0          ; |                                 |
div Count         ; | compute average                 |
mov AVG,ax        ; \---------------------------------/
;==================================================================
display_avg:
mov ax,AVG
call strval
call writeln
mov dx,offset msg_avg
call write
mov dx,offset NUM
call write
;===================================================================
;find item equal to average
mov bx,0
mov ax,avg
check_next:
cmp array[bx],al
je found ;if found stop loop and print message
inc bx ;next index
cmp bx,ARRAY_SIZE
jl check_next
not_found: ;if found none item equal to avg print suit message
call writeln
mov dx,offset msg_not_found
call write
jmp finish
found:
mov INDEX,bx;save value of index item equal to avearge
mov ax,INDEX
call strval
call writeln
mov dx,offset msg_found
call write
call writeln
mov dx,offset msg_index
call write
mov dx,offset NUM
call write
;*******************************************************************
finish: ret ;return from procedure "main"
;-------------------------------------------------------------------
main endp
cseg ends
end main ;don'nt forget the starting address
