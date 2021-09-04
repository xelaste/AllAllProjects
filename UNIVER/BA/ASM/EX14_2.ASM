title EX14_2
;--------------------------------------------------------
sseg segment stack
     dw 100 dup(?)
sseg ends
;------------------------------------------------------
cseg segment
     assume cs:cseg,ss:sseg
;-----------------------------------------------------------
main proc far
     push ds     ; /---------------------------\
     xor ax,ax   ; | Save return address to Dos|
     push ax     ; \---------------------------/
;=========================================================
mov cx,25D
xor al,al
mov ah,-1;
Start:
add ah,2
add al,2
push ax
loop start
;=========================================================
mov cx,25D
clear_stack:
pop ax
loop clear_stack
;------------------------------------------
Finish: ret ;return from procedure "main"
;===========================================
main endp
cseg ends
end main ;do not forget the starting address
;---------------------------------------------------------------------
