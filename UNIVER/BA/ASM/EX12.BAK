title divide_by_2
;--------------------------------------------------------
dseg segment
     msg1      db 'Syntax error or missing signs$'
     msg2      db 'Odd number - incorect divisions$'
     new_line  db 0dh,0ah,'$' ;cr+lf ascii codes
dseg ends
;------------------------------------------------------
sseg segment stack
     dw 100 dup(?)
sseg ends
;------------------------------------------------------
cseg segment
     assume cs:cseg,ds:dseg,ss:sseg
main proc far
     push ds     ; /---------------------------\
     sub ax,ax   ; | Save return address to Dos|
     push ax     ; \---------------------------/

     mov ax,dseg ;points the ds register to the
     mov ds,ax   ;data segment of this program
;=========================================================
;=========================================================




