if1
%out	LPA PROLOG Professional - Assembler Code Interface
%out	Compiler Version
endif
;
	title	Assembler coded predicate extensions for PROLOG Professional
page	64,132
;	***************************************************************
;	*                                                             *
;	*       Machine Code Interface for PROLOG Professional        *
;	*       ----------------------------------------------        *
;	*	Compiler Version				      *
;	*	----------------				      *
;	*                                                             *
;	*       (c) 1984,1985,1986 Logic Programming Associates Ltd   *
;	*                                                             *
;	*          written by Brian D Steel, 14 Feb 84                *
;	*                                                             *
;	***************************************************************
.xlist
;	***************************************************************
;	*                                                             *
;	*  Macro Defintion for Dictionary Link: SYSDEF		      *
;	*  -------------------------------------------		      *
;	*                                                             *
;	*  SYSDEF defines a new system constant. The macro should be  *
;	*  'called' within the SYSSEG segment below		      *
;	*  							      *
;	*  This macro should be used instead of the DLINK and DNAME   *
;	*  macros in the interpreter				      *
;	*                                                             *
;	*                                                             *
;	***************************************************************
;
;	*** SYSDEF: a macro for defining the name of a new built in 
;		    primitive ***
;
;	SYSDEF takes two arguments as follows:
;
;	1: (daddr) - This is the name of the label used as the entry point
;	   into the user program code itself.
;
;	2: (dtext) - This is the name of the predicate itself, as accessed 
;	   from PROLOG Professional.
;	   Note that the first character of the name must be an UPPER-CASE 
;	   letter, otherwise the dictionary entry will not be accessible 
;	   from within LPA PROLOG Professional.
;
;	*** SYSDEF should only be used in the SYSSEG segment ***
;
;	The following is an example dictionary of three entries:
;
;		SYSDEF	ranprg,RAND
;		SYSDEF	sinprg,SIN
;		SYSDEF	cosprg,COS
;
; where ranprg, sinprg and cosprg label the entry points of the 
; programs that implement the primitive. (These labels will be in the 
; PLPROG code segment.)
;
; The first entry will be tagged automatically on to the end of PROLOG's own 
; system dictionary.
;
SYSDEF	macro	dattr, dtext
	local	start

	X	=	0
start	db	BLTTG			;; constant defines a built in prim
	IRPC	ch, <dtext>
		X = X + 1
	ENDM
	Y	= (X + 6 + 15)/16
	dw	Y
	dw	&dattr
	db	X
	IRPC	c, <dtext>
		db	'&c'
	endm
	ORG	start + ((X + 6 + 15)/16) * 16
	endm

;
;	***************************************************************
;	*                                                             *
;	*             Parameters used by PROLOG                       *
;	*             -------------------------                       *
;	*                                                             *
;	*  These parameters should be used whenever referring values  *
;	*  or data types used by PROLOG                               *
;	*                                                             *
;	***************************************************************
;
;	*** General parameters ***
;
NIL	equ	-1	; nil pointer - used at end of list
MAXCON	equ	122	; maximum length of a constant
TYSIZE	equ	128	; size of type-ahead buffer TYPBUF
STSIZE	equ	512	; length of machine stack for CALL, RET, PUSH, POP etc.
;
;	*** List cell types ***
;
UNBNDTG	equ	 0		; unbound variables
LINKTG	equ	 2		; variable links
INTTG	equ	 4		; integer
REALTG	equ	 6		; real number
CONTG	equ	 8		; constant
NILTG	equ	10		; nil list
LISTTG	equ	12		; list 
TPLTG	equ	14		; n-tuple
;
;	*** Constant types ***
;
UNUSED	equ	0		; constant is just data
MODTG	equ	2		; constant that is name of a module
FILETG	equ	4		; constant that is name of a file
BUFTG	equ	6		; constant that is name of a buffer 
OPRTG	equ	8		; constant is name of binary operator
FUNCTG	equ	10		; constant is name of a unary function
BLTTG	equ	12		; built in predicate
DPROGTG	equ	14		; "interpreted" relation (ie decompilable)
PROGTG	equ	16		; constant that is name of a program 
CBLTTG	equ	18		; C built in primitive
ARRTG	equ	20		; an array - bds 10 may 88
MODENTG	equ	30		; module entry management tag
ARRENTG	equ	32		; array entry management tag
;
;	*** System register slot defintions ***
;
SLTLEN	equ	6	; length of an system register slot
NOSLTS	equ	8	; the number of system register slots provided
SLTBND	equ	0	; output value type
SLTDTA	equ	1	; output value data
SLTINT	equ	3	; input value type
SLTSKL	equ	4	; input value data
.list
page
;	***************************************************************
;	*                                                             *
;	*      PLDATA: Data segment definition for list structures    *
;	*      ---------------------------------------------------    *
;	*                                                             *
;	*  The DS register of the 8086 addresses a 64 kilobyte area   *
;	*  of memory that is used by PROLOG almost entirely stack     *
;	*  and heap list structures: in addition a few system         *
;	*  variables are maintain in this segment. All data 	      *
;	*  structures except for constants (predicate names) should   *
;	*  be placed in the PLDATA segment			      *
;	*                                                             *
;	***************************************************************
;
PLDATA	SEGMENT WORD PUBLIC 'PDATA'
ASSUME	CS:PLPROG,DS:PLDATA
.xlist
;	***************************************************************
;	*                                                             *
;	*  The following data structures may be of use in assembler-  *
;	*  coded programs                                             *
;	*                                                             *
;	***************************************************************
;
;	*** I/O Pointers. All PROLOG I/O programs use the following
;	    three addresses for character level I/O. The addresses of
;	    user-written character level I/O programs can be placed in
;	    these three locations, prior to a call to some system I/O
;	    program for higher-level I/O ***
;
	extrn	GETCH:word	; address of a character-in routine
	extrn	SENDCH:word	; address of a character-out routine
	extrn	BAKCH:word	; address of a one-char put-back routine
;
;	*** Miscellaneous system variables ***
;
	extrn	SLOT1:word,SLOT2:word,SLOT3:word,SLOT4:word ; the system . . .
	extrn	SLOT5:word,SLOT6:word,SLOT7:word,SLOT8:word ; . . . registers
;
	extrn	QUOTES:word	; byte quote flag for PRTERM: 1 = quote, 0 = not
	extrn	RDSTT:word	; word = start of circular read buffer
	extrn	RDEND:word	; word = end of circular read buffer
	extrn	TYPCNT:word	; byte type-ahead counter for TYPBUF
;
;	***************************************************************
;	*                                                             *
;	*  Data structures except for constants should be 	      *
;	*  inserted here.					      *
;	*                                                             *
;	***************************************************************
.list
;
PLDATA	ENDS
;
page
;	***************************************************************
;	*                                                             *
;	*      SYSSEG: Segment for system constants 		      *
;	*      ------------------------------------                   *
;	*                                                             *
;	*  All user defined system constants must be declared with    *
;	*  SYSDEF in this segment. NO OTHER USES should be made of    *
;	*  segment SYSSEG.					      *
;	*                                                             *
;	***************************************************************
;
SYSSEG	segment	para public
	assume	cs:SYSSEG
.xlist
;
;	***************************************************************
;	*                                                             *
;	*  Predicate names (using SYSDEF) should be inserted here     *
;	*                                                             *
;	***************************************************************
;
.list
;	===============================================================
;	*****                                                     *****
;	 ***        U S E R   P R E D I C A T E   N A M E S        ***
;	  *                                                         *
;	---------------------------------------------------------------
;
;	---------------------------------------------------------------
;	  *                                                         *
;	 ***        U S E R   P R E D I C A T E   N A M E S        ***
;	*****                                                     *****
;	===============================================================
;

;
; define the end of the system constants. SYSEND must be present and it
; must be the last definition in the segment SYSSEG
; 
public	SYSEND
SYSEND	equ	$

SYSSEG	ENDS
page
;	***************************************************************
;	*                                                             *
;	*      PLPROG: Code segment for programs                      *
;	*      ---------------------------------                      *
;	*                                                             *
;	*  The CS register of the 8086 addresses a 64 kilobyte area   *
;	*  of memory that is used by micro-PROLOG to store machine    *
;	*  instructions. In addition, certain system arrays exist     *
;	*  in the code segment. 				      *
;	*  Only part of the potential 64 kilobytes is used by the     *
;	*  system, the rest overlapping the data segment. All code    *
;	*  should be placed in the PLPROG segment.                    *
;	*                                                             *
;	***************************************************************
;
PLPROG	segment	byte public 'pcode'
	assume	cs:PLPROG, ds:PLDATA
.xlist
	name	usercode
;
;	***************************************************************
;	*                                                             *
;	*  The following external symbols are subroutines and data    *
;	*  areas that may be of use in user programs:                 *
;	*                                                             *
;	***************************************************************
;
;	*** Input/Output related system calls ***
;
	extrn	CHROUT:near	; send the character in AL to the console
	extrn	INTCHK:near	; poll the console for interrupts
	extrn	INKEY:near	; grab a character from type-ahead or wait if
;				  none there - returns char in AL - no echo
	extrn	INIKEY:near	; reinitialise the console buffers
	extrn	RSETUP:near	; set up read stream - uses first argument of
;				  predicate as a file name and sets up to read
;				  from it
	extrn	WSETUP:near	; set up write stream - uses first argument of
;				  predicate as a file name and sets up to write
;				  to it
	extrn	PRTERM:near	; print term list at SLOT2 - via [SENDCH]
	extrn	RDTERM:near	; read a term into SLOT2 - via [GETCH] & [BAKCH]
	extrn	WNUM:near	; print 16 bit int in BX - via [SENDCH]
	extrn	WREAL:near	; print a real number at [BX] - via [SENDCH]
;
;	*** Miscellaneous system calls ***
;
	extrn	BLT_ERR:near	; standard error exit point - place error code
;				  in BX and then JMP BLT_ERR to handle an error
	extrn	TRWALK:near	; immediately prior to type tree CALL TRWALK
	extrn	MAKCON:near	; make a constant - set first byte of CONBUF to
;				  character count (0 < count < 61) of constant,
;				  and the next 1-60 bytes to text of constant.
;				  CALL MAKCON - BX will then contain the address
;				  of the new constant
	extrn	MAKLST:near	; create a list element - after a CALL MAKLST
;				  the BX register will contain the address of a
;				  new six-byte list cell
	extrn	REBOOT:near	; exit PROLOG and reboot MS-DOS
	extrn	SOLVE:near	; warm-start interpreter - reset subroutine
;				  stack with MOV SP,STSIZE and then JMP SOLVE
	extrn	SYSERR:near	; exit PROLOG with System Abort message
;				  and hex exit address - CALL SYSERR
;
;	*** Miscellaneous data structures in code segment ***
;
	extrn	CONBUF:near	; the constant buffer. Offset 0 is the character
;				  count (1-60), the next 1-60 bytes is the text
	extrn	TYPBUF:near	; the type-ahead buffer - TYSIZE bytes long
;
;	*** Public declarations for the linking loader ***
;
	public	usrmsg		; user-added start-up message
;
.xlist
;	***************************************************************
;	*                                                             *
;	*  USRMSG is a character string, terminated with a null       *
;	*  byte, and which is printed after PROLOG's start-up         *
;	*  message.                                                   *
;	*                                                             *
;	***************************************************************
;
;	*** USRMSG can be set to contain any message in single quotes ***
.list
;	===============================================================
;	*****                                                     *****
;	 ***       U S E R   S T A R T - U P   M E S S A G E       ***
;	  *                                                         *
;	---------------------------------------------------------------
;
USRMSG	db	0 	; message in single quotes goes before the zero byte
;
;	---------------------------------------------------------------
;	  *                                                         *
;	 ***       U S E R   S T A R T - U P   M E S S A G E       ***
;	*****                                                     *****
;	===============================================================
.xlist
;
;	***************************************************************
;	*                                                             *
;	*  User code should be inserted in the file below here.       *
;	*                                                             *
;	***************************************************************
;
;	*** A typical program consists of a predicate declaration using
;	    SYSDEF (in segment SYSSEG), then a call to TRWALK immediately
;	    preceeding the type-tree ***
;
;	For Example:
;
;	sentry:	call	trwalk
;		<type tree>
;		<rest of code>
;
;	The type tree node offsets are:
;
;	0 = Leaf  1 = Int  2 = Real  3 = Con  4 = List  5 = Tuple  6 = Var
.list
page
;	===============================================================
;	*****                                                     *****
;	 ***         U S E R   A S S E M B L E R   C O D E         ***
;	  *                                                         *
;	---------------------------------------------------------------
;
;	---------------------------------------------------------------
;	  *                                                         *
;	 ***         U S E R   A S S E M B L E R   C O D E         ***
;	*****                                                     *****
;	===============================================================
;
PLPROG	ENDS
	END

