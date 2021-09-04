title EX14_1
;--------------------------------------------------------
SHOW_MONTH macro N ;macro for print string onto screen
push dx;save value of dx
push ax
mov dx,offset new_line
call write
mov dx,offset MONTH&N
call write
mov dx,offset DAYS&N
call write
pop ax;return value of AX
pop dx;return value of DX
endm ;SHOW_MONTH
;------------------------------------------------------------
SHOW_ALL_MONTHS macro
 i=1
 rept 12
 SHOW_MONTH %i
 i=i+1
 endm ;rept
endm ;SHOW_ALL_MONTH
;----------------------------------------------------------
dseg segment
   MONTH1 db 'MONTH1 $'
   MONTH2 db 'MONTH2 $'
   MONTH3 db 'MONTH3 $'
   MONTH4 db 'MONTH4 $'
   MONTH5 db 'MONTH5 $'
   MONTH6 db 'MONTH6 $'
   MONTH7 db 'MONTH7 $'
   MONTH8 db 'MONTH8 $'
   MONTH9 db 'MONTH9 $'
   MONTH10 db 'MONTH10 $'
   MONTH11 db 'MONTH11 $'
   MONTH12 db 'MONTH12 $'
   DAYS1 db '31$'
   DAYS2 db '28$'
   DAYS3 db '31$'
   DAYS4 db '30$'
   DAYS5 db '31$'
   DAYS6 db '30$'
   DAYS7 db '31$'
   DAYS8 db '31$'
   DAYS9 db '30$'
   DAYS10 db '31$'
   DAYS11 db '30$'
   DAYS12 db '31$'
   new_line  db 0dh,0ah,'$' ;cr+lf ascii codes
dseg ends
;------------------------------------------------------
sseg segment stack
     dw 100 dup(?)
sseg ends
;------------------------------------------------------
cseg segment
     assume cs:cseg,ds:dseg,ss:sseg
;------------ROUTINE TO PRINT A STRING -------------------------
write proc
      mov ah,9
      int 21h
      ret
write endp
;-----------------------------------------------------------------
main proc far
     push ds     ; /---------------------------\
     xor  ax,ax  ; | Save return address to Dos|
     push ax     ; \---------------------------/
     mov ax,dseg ;points the ds register to the
     mov ds,ax   ;data segment of this program
;=========================================================
SHOW_ALL_MONTHS
;=========================================================
finish: ret ;return from procedure "main"
;-------------------------------------------------------------------
main endp
cseg ends
end main ;do not forget the starting address
;---------------------------------------------------------------------
