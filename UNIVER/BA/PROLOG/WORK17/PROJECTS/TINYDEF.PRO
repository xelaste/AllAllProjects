
/*-------------------------------------------------------

     Formal Grammar Specification for Language
     
                 T I N Y

     Version 1.0
     Expert Systems Limited. Oxford UK.


     This file contains a semi-complete description 
     of the small programming language 'TINY'.
                    +++++++
     [1] Syntactic Description in terms of grammar rules.
     [2] Lexical Description in terms of KEYWORDS.
     [3] Machine Code Description in terms of TEMPLATES.

---------------------------------------------------------*/


/*--[1]--Top-Level Program Structure---------------------*/

program(  Prog  )        -->  block( Prog ).

block( Actions )         -->  [begin], actions(Actions), [end].

actions( [A1|A2] )       -->  action( A1 ), more_actions( A2 ).

more_actions( A )        -->  [ ';' ], actions( A ).
more_actions( [] )       -->  { true } .


/*---[2]--- Actions -----------------------------------*/

action( if(C,T,F) )      -->  [if], cond(C), [then],
                                   block(T),
                              [else],
                                   block(F).

action( while(C,A) )     -->  [while], cond(C), [do],
                                   block(A).

action( assign(I,E) )    -->  [ id(I) ], [=], expr(E).


/*---[3]--- Expressions & Conditions -------------------*/

expr(E)                  -->  term(T), exprtail(T,E).

exprtail(T,+(T,E))       -->  [+], term(T0), exprtail(T0,E).
exprtail(T,-(T,E))       -->  [-], term(T0), exprtail(T0,E).
exprtail(T,*(T,E))       -->  [*], term(T0), exprtail(T0,E).
exprtail(T,/(T,E))       -->  [/], term(T0), exprtail(T0,E).
exprtail(T,T)            -->  { true } .

term( id(I) )            -->  [ id(I) ].
term( const(V) )         -->  [ const(V) ].

cond( C )                -->  [ id(I) ], ctail( I,C ).

ctail( I,eq(I,E))        -->  [=], expr(E).
ctail( I,ne(I,E))        -->  [#], expr(E).
ctail( I,idtest(I))      -->  { true } .



/*---[4]--- Lexical Definitions ----------------------*/

keyword( if ).
keyword( then ).
keyword( else ).
keyword( while ).
keyword( do ).
keyword( begin ).
keyword( end ).

symbol_char( ";" ).
symbol_char( "+" ).
symbol_char( "-" ).
symbol_char( "*" ).
symbol_char( "/" ).
symbol_char( "=" ).
symbol_char( "#" ).

statement_delimiter(  ';' ).
statement_delimiter( end ).


/*---[5]--- Machine Code Template Definitions --------*/

[]             --}        ?true.
[A|B]          --}        @A & @B.

if(C,T,F)      --}        @C~L1 &
                          @T &
                          'LABEL'(L2) &
                          'JUMP' &
                     L1:  & @F &
                     L2:  .

while(C,A)     --}   L1:  &
                          @C~L2 &
                          @A &
                          'LABEL'(L1) &
                          'JUMP' &
                     L2:  .

assign(I,E)    --}        'ID'(I) & @E & 'STORE'.


+(E1,E2)       --}        @E1 & @E2 & 'ADD'.
-(E1,E2)       --}        @E1 & @E2 & 'SUB'.
*(E1,E2)       --}        @E1 & @E2 & 'MUL'.
/(E1,E2)       --}        @E1 & @E2 & 'DIV'.

eq(I,E2)~L     --}        'ID'(I) & @E2 & 'LABEL'(L) & 'JNE'.
ne(I,E2)~L     --}        'ID'(I) & @E2 & 'LABEL'(L) & 'JEQ'.
idtest(I)~L    --}        'IDTEST'(I) & 'LABEL'(L) & 'JFALSE'.

id(I)          --}        'ID'(I).
const(V)       --}        'CONST'(V).

