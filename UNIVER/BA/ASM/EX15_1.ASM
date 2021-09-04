N equ 5 ;size of board;
ALIVE equ '*'
DEAD  equ ' '
title EX15_1
;--------------------------------------------------------
WRITELN macro STRING ;macro for print string onto screen
push dx;save value of dx
push ax;save value of ax
mov dx,offset new_line
call write
mov dx,offset STRING
call write
pop ax;restore value of AX
pop dx;restore value of DX
endm ;WRITELN;
;------------------------------------------------------------
LINE Macro Num,FIRST,CELL,LAST
LINE&Num db FIRST
         db (N-1) dup (CELL),&LAST
i=i+1
endm;
;------------------------------------------------------------
SHOW_MATRIXE macro
 i=0
 rept Number_of_line
 WRITELN LINE&%i
 i=i+1
 endm ;rept
endm ;SHOW_MATRIXE
;----------------------------------------------------------
dseg segment
MATRIXE: ;used for display current generation
i=0
LINE %i,'Ú','ÄÄÄÂ','ÄÄÄ¿$'
LINE %i,'³','   ³','   ³$'
rept N-1
LINE %i,'Ã','ÄÄÄÅ','ÄÄÄ´$'
LINE %i,'³','   ³','   ³$'
endm
LINE %i,'À','ÄÄÄÁ','ÄÄÄÙ$'
Number_of_line=i
UP_BORDER   db (N)   dup (DEAD);help area for making check easer
board       db (N*N) dup (DEAD);array of current generation
DOWN_BORDER db (N)   dup (DEAD);help area for making check easer
New_board   db (N*N) dup (DEAD);array of new generation
GO_ON_MESSAGE db 'Press  E to stop , any other key to continue$'
counter dw 0 ;counter of generation
INNER_CELL_AREA   dw -N-1,-N,-N+1,1,N+1,N,N-1,-1;offsets of NEIGHBOUR cells
FIRST_COLUMN_AREA dw    0,-N,-N+1,1,N+1,N,  0, 0;relative to checked cell
LAST_COLUMN_AREA  dw -N-1,-N,   0,0,  0,N,N-1,-1
;   *----*----*----*----*----*
;   | 0  | 1  | 2  | 3  | 4  |  Upper border  all cells are dead
;   *----*----*----*----*----*  N=5
;0  |-N-1| -N |-N+1|    |    |  checking the inner cell X
;   *----*----*----*----*----*  if cell from last or first column is checked
;1  | -1 | X  | 1  |    |    |  corresponding values of offsets gets zero
;   *----*----*----*----*----*
;2  | N-1| N  | N+1|    |    |
;   *----*----*----*----*----*
;3  |    |    |    |    |    |
;   *----*----*----*----*----*
;4  |    |    |    |    |    |
;   *----*----*----*----*----*
;   |    |    |    |    |    | Down border all cells are dead
;   *----*----*----*----*----*
new_line  db 0dh,0ah,'$' ;cr+lf ascii codes
counter_msg db 0dh,0ah,'Generation number: $'
KEYBOARD_INPUT LABEL BYTE
MAX_NUM_LENTH  db 2
NUM_DIGIT_READ db 0
INPUT_NUMBER   db '  ','$' ;string for storing input number
INVALID_NUMBER db 'Invalid digit',0dh,0ah,'$'
ENTER_PROMPT   db 'Input lineNo and columnNo from 1 to $'
STOP_PROMPT    db '.  0 , 0 to stop $'
LINE_PROMPT    db 'I= $'
COL_PROMPT     db 'J= $'
INVALID_PLACE  db 'Invalid line or column$'
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
;-------------------------------------------------------------
getchar proc
;Getting charcter from the keyboard
;return AL with ASCII code of accepted character
;------------------------------------------------------------------
mov ah,8
int 21h
ret
getchar endp
;-----------------------------------------------------------------
board2Matrixe proc
;copying data from board to display matrixe
;----------------------------------------------------------------
push ax
push bx
push cx
push bp
push si
;---------------------------------------------------------------
mov bp,sp
lea bx,LINE0 ;pointer to matrixe
mov si,[bp+12] ;pointer to board
mov cx,N
fill_matrixe:
push cx
mov cx,N
add bx,4*(N+1)
NEXT_CELL:
mov al,[si]
mov LINE0[bx],al
inc si
add bx,4
loop NEXT_CELL
pop cx
loop fill_matrixe
pop si
pop bp
pop cx
pop bx
pop ax
ret
board2Matrixe endp
;---------------------------------------------------------------
proc new2board
;this procedure copying data from new_board to board
;----------------------------------------------------------------
push di; /--------------------------\
push si; | saving registers         |
push cx; |                          |
push es; \--------------------------/
push ds
pop es
mov si,offset New_board
mov di,offset board
mov cx,N*N
cld
rep movsb ;copy from new board to board
pop es; /----------------------------\
pop cx; |   restoring  registers     |
pop si; |                            |
pop di; \----------------------------/
ret
new2board endp
;---------------------------------------------------------------
proc PUT_DIGIT
;routine for printing decimal DIGIT
;On entry DL Lower 4 bits contain number to be printed
;------------------------------------------------------------------
push dx ;save register used
push ax
add dl,'0'
mov ah,2
int 21h
pop ax ;restore old values of registers
pop dx
ret
PUT_DIGIT endp
;-----------------------------------------------------------------
proc PrintNum
;This procdure writes a 16-bit unsigned number in decimal notation
;On entry DX N:16-bit insigned number
;--------------------------------------------------------------
push ax
push cx
push dx
push si
mov ax,dx
mov si,10 ;will divide by 10 using si
xor cx,cx ;count of digit placed in stack
NON_ZERO:
 XOR dx,dx
 div si   ;calculate n/10 and n mod 10
 push dx  ;push digit onto stack
 inc cx   ;one more digit added
 or ax,ax ;n=0 yet
 jne NON_ZERO
WRITE_DIGIT_LOOP:
  pop dx
  call PUT_DIGIT
  LOOP WRITE_DIGIT_LOOP
pop si
pop dx
pop cx
pop ax
ret
PrintNum endp
;-----------------------------------------------------------------
COUNT_ALIVE_NEIGHBOURS proc
;procedure counts alive neighbour
;on entry di-adrress of offset table,
;output the number of alive NEIGHBOURs in dx
;------------------------------------------------
push ax
push bx
push cx
push si
xor dx,dx
mov cx,8
mov bx,si
CONTINUE:
xor ax,ax
mov ax,[di]
or ax,ax
jz END_NEIGHBOUR;if offset is 0 continue to next NEIGHBOUR
mov si,ax
mov ah,[bx+si]
mov al,ALIVE
cmp ah,al;if NEIGHBOUR alive
jnz END_NEIGHBOUR ;it is not
inc dx            ;yes it is
END_NEIGHBOUR:
add di,2
loop CONTINUE
pop si
pop cx
pop bx
pop ax
ret
COUNT_ALIVE_NEIGHBOURS endp
;-----------------------------------------------------------------
MAKE_NEW_GENERATION proc
;procedure that preparing new generation in memory (new_board)
;from the current generation (board)
;----------------------------------------------------------------
push ax
push bx
push cx
push dx
push di
push si
;-----------------------------------------------------------------
xor dx,dx
lea si,board
lea bx,New_board
mov cx,N
BUILD_NEW_board:
push cx
mov cx,N
CHECK_ROW:
mov ax,N
cmp cx,ax
je FIRST  ;first column
cmp cx,01h;
je LAST   ;last column
;-------------------------------------
INNER:
mov di,offset INNER_CELL_AREA
call COUNT_ALIVE_NEIGHBOURS
jmp END_CHECK_CELL
;-------------------------------------
FIRST:
mov di,offset FIRST_COLUMN_AREA
call COUNT_ALIVE_NEIGHBOURS
jmp END_CHECK_CELL
;-------------------------------------
LAST:
mov di,offset LAST_COLUMN_AREA
call COUNT_ALIVE_NEIGHBOURS
;-------------------------------------
END_CHECK_CELL:
mov al,ALIVE
mov ah,[si]
cmp al,ah    ;is cell alive ?
je ALIVE_CELL;yes it is
;-------------------------------------
DEAD_CELL:
cmp dx,3
je NEW_LIFE
jmp DEARTH
ALIVE_CELL:
cmp dx,4
jae DEARTH
cmp dx,1
jbe DEARTH
NEW_LIFE:
mov BYTE PTR [bx],ALIVE
jmp END_CELL_LOOP
DEARTH:
mov BYTE PTR [bx],DEAD
END_CELL_LOOP:
inc si
inc bx
loop CHECK_ROW
pop cx
loop BUILD_NEW_BOARD
pop si
pop di
pop dx
pop cx
pop bx
pop ax
ret
MAKE_NEW_GENERATION endp
;-----------------------------------------------------------------
disp_gen proc
;Procedure for display board with current generation of life
;-----------------------------------------------------------------
push ax
push bx
push dx
xor ax,ax
push offset board
call board2Matrixe
pop bx
SHOW_MATRIXE
;------------------------------
;print generation number
;------------------------------
mov dx,offset counter_msg
call write
mov dx,counter
call PrintNum
;---------------------------------
pop dx
pop bx
pop ax
ret
disp_gen endp
;----------------------------------------------------------------
convert_digit proc
;this procedure converts a character from ASCII to a nibble (4 bits)
;On entry AL character to convert
;Return   AL Nibble
;         CF set for error , cleared otherwise
;-----------------------------------------------------------------
cmp al,'0'
jb BAD_DIGIT
cmp al,'9'
ja BAD_DIGIT
sub al,'0'
clc
ret
BAD_DIGIT:
stc
ret
convert_digit endp
;----------------------------------------------------------------
read_string proc
;procedure for read string from keyboard
;on entry DS:DX Address of string area
;---------------------------------------------------------------
push ax
mov ah,0Ah
int 21h
pop ax
ret
read_string endp
;----------------------------------------------------------------
get_a_num proc
;gets decimal number from the keyboard
;return dx
;---------------------------------------------------------------
push ax
push bx
push cx
push si
mov si,10D
REPEAT_INPUT:
lea dx,KEYBOARD_INPUT
call read_string
cmp NUM_DIGIT_READ,1
jb NO_DIGITS
xor cx,cx
mov cl,NUM_DIGIT_READ
xor bx,bx
xor dx,dx
xor ax,ax
CALC_INPUT_NUMBER:
mov ax,dx
mul si
mov dx,ax
mov al,INPUT_NUMBER[bx]
call convert_digit
jc INPUT_ERROR
add dx,ax
loop CALC_INPUT_NUMBER
jmp END_GET_A_NUM
NO_DIGITS:
xor dx,dx
END_GET_A_NUM:
pop si
pop cx
pop bx
pop ax
ret
INPUT_ERROR:
writeln INVALID_NUMBER
jmp REPEAT_INPUT
get_a_num endp
;----------------------------------------------------------------
get_board proc
;procedure that getting start state of board
;--------------------------------------------------------------
push ax
push bx
push cx
push dx
push si
xor cx,cx
mov si,N
BEGIN_INPUT:
;------------------------------
;print input prompt
;------------------------------
writeln ENTER_PROMPT
mov dx,N
call PrintNum
mov dx,offset STOP_PROMPT
call write
;---------------------------------
writeln LINE_PROMPT
call get_a_num
mov al,dl;input I line
writeln COL_PROMPT
call get_a_num
mov ah,dl;input J column
or ax,ax
jz IF_WAS_INPUT
cmp al,1
jb OUT_OF_RANGE
cmp al,N
ja OUT_OF_RANGE
sub al,1
cmp ah,1
jb OUT_OF_RANGE
cmp ah,N
ja OUT_OF_RANGE
xor bx,bx
sub ah,1
mov bl,ah
xor ah,ah
mul si   ;compute offset of whole lines
add bx,ax
mov BYTE PTR board[bx],ALIVE
inc cx
jmp BEGIN_INPUT
OUT_OF_RANGE:
writeln INVALID_PLACE
jmp BEGIN_INPUT
IF_WAS_INPUT:
clc
or cx,cx
jnz END_GET_BOARD
stc
END_GET_BOARD:
pop si
pop dx
pop cx
pop bx
pop ax
ret
get_board endp
;----------------------------------------------------------------
main proc far
     push ds     ; /---------------------------\
     xor  ax,ax  ; | Save return address to Dos|
     push ax     ; \---------------------------/
     mov ax,dseg ;points the ds register to the
     mov ds,ax   ;data segment of this program
;=========================================================
call get_board
jc finish
NEW_GENERATION:
call disp_gen
writeln GO_ON_MESSAGE
call getchar
cmp al,45h;if pressed E or e get out
je finish
cmp al,65h; e pressed
je finish
inc counter
call MAKE_NEW_GENERATION
call New2board
jmp NEW_GENERATION
;=================================================================
finish: ret ;return from procedure "main"
;-----------------------------------------------------------------
main endp
cseg ends
end main ;do not forget the starting address
;-----------------------------------------------------------------
