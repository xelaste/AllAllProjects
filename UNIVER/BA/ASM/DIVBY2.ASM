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
read_ch1: mov ah,1   ; /-----------------------------------------------\
          int 21h    ; |read the sign (ch1) using dos function 1 (ah=1)|
          mov bh,al  ; | the sign in register BH.                      |
                     ; \-----------------------------------------------/

;---------- check if (ch='+') or (ch1='-')
          cmp bh ,'+'
          je read_ch2
          cmp bh, '-'
          jne syntax_error
;*********************************************************************
read_ch2: mov ah,1   ;same as read_ch1
          int 21h
          mov bl,al  ;store digit in register BL

;------- check if ch2 in ('0'...'9');
         cmp bl , '0'
         jb syntax_error
         cmp bl , '9'
         ja syntax_error
;******************************************************************
translate: sub bl,48d  ;Form an integer digit from ASCII code
           cmp bh ,'+' ;find out if the digit should be positive
           je divide   ;if yes , skip to "divide",else
           not bl      ;first form 1 compliment and then
           add bl,1    ;form to  compliment. finally
                       ;you have the negative representation
;*********************************************************************
divide: sar bl,1       ;divide by 2
        jc not_correct ;if carry flag ="1" then result incorrect.
;----------- before changing again to ASCII code ---------------
        cmp bh,'+' ;find out if the number is positive
        je print   ;if yes , skip to "print else
        not bl     ;form 1's compliment again and then
        add bl,1    ; add 1 to get the unsigned number
;******************************************************************
print:  add bl,48  ;form ASCII code of the digit
;------------------------------------------------
        mov dx, offset new_line
        mov ah,9 ;dos function 9
        int 21h
;------------------------ print sign :
        mov dl,bh
        mov ah,2
        int 21h
;------------ print digit (as character):
        mov dl,bl
        mov ah,2
        int 21h
        jmp finish
;***************************************************************
not_correct: mov dx, offset new_line
             mov ah,9
             int 21h

             mov dx, offset msg2
             mov ah,9
             int 21h

             jmp finish
;****************************************************************
syntax_error: mov dx, offset new_line
              mov ah,9
              int 21h

              mov dx, offset msg1
              mov ah,9
              int 21h
;*******************************************************************
finish: ret ;return from procedure "main"
;-------------------------------------------------------------------
main endp
cseg ends
end main ;don'nt forget the starting address
