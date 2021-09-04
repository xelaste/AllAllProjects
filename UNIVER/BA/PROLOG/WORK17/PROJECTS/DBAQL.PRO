

/*------------------------------------------------------*/
/*                                                      */
/*       'DBAQL' SIMPLE GENERAL PURPOSE DATABASE        */ 
/*       ---------------------------------------        */
/*                                                      */
/*            Expert Systems Limited. 1983.             */
/*                                                      */
/*   This is a simple general purpose database query    */
/*   program which operates on a general database of    */
/*   records having an externally defined format.       */
/*                                                      */
/*------------------------------------------------------*/

/*
     The DBfile contains four distinct groups of Prolog
     facts; 'verbs' and 'constructors', described later, as 
     well as the 'format' structure, which defines the contents
     of each data record, and the 'record' structures themselves
     which contain the actual data.

     Each 'record' is of the form:
     
     record( S1,S2,S3....Sn ).

     where each Si holds an appropriate datum and
     corresponds to the 'search field' of the record.
     This is a name defined in the 'format' specifier in
     the external database file, DBfile. For example:

     format( [ title, surname, age,... company ] ).
    
     The user may construct queries for the database and
     specify the format of the report to be produced. Each
     database query has the form:

     all <report spec.> <verb> <search spec.> .

     where:-
     <report spec.>   determines the report produced by the
                      query.i.e. the display produced.

     <verb>           is a defined link word such as 'having'.

     <search spec.>   is a spec. of the requirements for each
                      item in the output report.
*/
/*
.pa
*/
/*

     The <report spec.> may also make use of 'constructors'
     which allow the insertion of pre-defined text into the
     body of the report. Each constructor has:

     (1) A symbolic name which is used to refer to it in the
         database query.
     (2) A text body which is inserted in the output report
         at the place indicated by its name in the query.


     Constructors may be defined as follows:

     add constructor( works_at, ' is employed by ').

     - so that if works_at is included in a <report spec.>, 
     the text ' is employed by ' will appear in its place.

     The user may also define 'verbs' which delimit the report
     specifier part of a query from the search specifier part.
     For example:

     add verb( given_that ).

     New data 'records' may also be added to the database using
     the 'add' command. Thus:

     add record( dr, williams, 65,... bakoe-company ).

     A 'delete' command is also provided which removes all
     'record(s)' satisfying the search specification.
     The general form is as follows:

     delete <search spec.>. 

     There is also a 'help' command. Entering this in
     response to the DBAQL> prompt, displays the search fields,
     verbs and constructors currently in effect as well as
     listing the available commands and their associated syntax.

     It should be noted that, although there are facilities
     for manipulating the contents of the database, this does
     not extend to the contents of the DBfile itself.
 
*/
/*
.pa
*/
/*

     The program functions as follows.
  
     After defining the required operators to the system, the
     user is prompted for the name of the DBfile which is to be 
     consulted. The 'format' and 'record(s)' are then read into
     the database. This information is then compiled into a form
     appropriate to the system; firstly the data contained in the
     'records' is associated with the corresponding name in the
     'format', and then 3 rules not directly accessible to the 
     user are asserted:
  
     'select' points the program to the first 'record' to be
              examined, by asserting it as an 'instance'. On
              backtracking, it removes this 'instance' and 
              creates a new one from the next 'record',
              and so on until all 'records' have been processed.

     'kill'   is used to remove individual 'records' from the
              database.

     'new'    tidies up the database by removing all 'instances'.

     It should be noted that these rules may not be predefined
     because their successful operation depends upon the
     number of arguments (search-fields) on a record (as specified
     by the format) and this might differ from one database
     to another.  
     
     The dbaql predicate is now called and this loop prompts
     the user for command and/or queries. Queries are handled
     by identifying the report and search specs. Constructors
     are substituted at this point and the format of the output
     (the variable 'Term' in the program) is established. Using
     'select' the program then tests each 'instance' to see if a
     match may be found with the search specification.

     If so, 'Goal' is called which has the effect of binding
     the free variables in 'Term' with the appropriate data in
     'instance', and 'Term' is written out to the terminal.
     At this point the predicate 'solve' backtracks to process 
     the next record and so on, until every 'record' has been
     examined.

     If any 'instance' should fail to match, 'Goal' is not
     called and the program proceeds with the next 'record'
     instead.

*/
/*
.pa
*/
/*

     The commands all work by asserting new facts, except for
     'delete'. This removes facts (in particular - 'records')
     using 'select' and a search spec analogous to that of
     the 'all' enquiry, as well as the 'kill' rule described
     above.

     The 'help' facility is serviced by the help_text
     predicate. 

     Verbs, constructors and the translations
     of 'and' and 'or' into Prolog appear at the end, as do 
     the general utility predicates required by the program.

*/
/*
.pa
*/

/* General database query operators */

?-op( 55, fx, all ).          
?-op( 250,fx, having ).
?-op( 250,fx, with ).
?-op( 250,fx, of ).
?-op( 240,xfy, and ).
?-op( 240,xfy, or ).
?-op( 10,xfy,' ').
?-op( 10,fx,add ).
?-op( 255,fx,delete ).
?-op( 100,fx,@ ).
?-op( 100, fx, once ).
?-op( 180,xfy,& ).
?-op( 1,xf,\ ).

/*
.pa
*/

/* Top-Level Database Compiler */

database_system:-
     nl,
     write('DBAQL  DataBase And Query Language demonstration.   Version 1.0'),nl,
     write('---------------------------------------------------------------'),nl,
     nl,
     write('File containing database : '),
     read( DBfile ),
     consult( DBfile ),
     compile_database( DBfile ),
     dbaql.

/* Association of records with name format and the   */
/* assertion of the 'select', 'kill' and 'new' rules */

compile_database( Name ):-
     nl,
     writef('Compiling DATABASE: ' & Name\ \),
     format( Key ),
     length( Nkeys,Key ),
     decode_keys( Key,1,Nkeys ),
     read_verbs,
     read_constructors,
     length( Nkeys,Keylist ),
     length( Nkeys,Rlist ),
     G2=..[instance|Keylist],
     G3=..[record|Keylist],
     G4=..[instance|Rlist],
     assert( ( select:-G3,retractall(G4),asserta(G2) )),
     assert( ( kill:-G2,deny( G3,true ) )),
     assert( new:-retractall(G2)),
     write('OK.'),nl.

/*
.pa
*/
              
/* Define and display verbs */

read_verbs:-
     verb(V),
     writef(@nl & '   Verb: ' & V \),
     op( 250,fx,V ),
     fail.
read_verbs.

/* Define and display constructors */

read_constructors:-
     constructor(C,Text),
     writef(@nl & '   Constructor: ' & C & ' : ' & Text & @nl),
     op(200,fx,C ),
     fail.
read_constructors.
 
/* Define and display search keys      */
/* and relate search keys to instances */

decode_keys( [],_,_ ). 
decode_keys( [K1|K2], N ,NK ):-
     writef('   Search Key: ' & K1 & @nl),
     op( 200,fx,K1 ),
     G1 =.. [K1,X],
     L1 is N-1,
     L2 is NK-N,
     length( L1, P1),
     length( L2, P2),
     append( P1,[X|P2],List ),
     Op =..[instance|List],
     assert( G1:-Op ),
     M is N+1,
     decode_keys( K2,M,NK ).



/* Main Database Command Service Procedure */

dbaql :-
    repeat,
       new,
       nl,nl,write('DBAQL> '),
       once read( Q ),
       once call( Q ),
    fail.

/*
.pa
*/
/* Database Query Procedures */

all T:-
     goallist( T,G,Search ),
     formgoal( G,Goal,Term ),nl,
     solve( Search,Goal,Term ).    

/* Separate into report and search specifiers */

goallist( T, [G1], Search ):-
     T =.. [G1,T1],
     T1=.. [V,Search],
     verb(V).
goallist( T, [G1|G2], Search ):-
     T =..[G1,T1 ],
     goallist( T1, G2, Search ).

/* Use constructors to insert text */

formgoal( [], true,'  ').
formgoal( [G1|G2], S1, T1 & T2 ):-
     constructor(G1,T1),
     formgoal( G2, S1, T2 ).
formgoal( [G1|G2], (S1,S2), T1 & ' ' & T2 ):-
     S1=..[G1,T1],
     formgoal( G2, S2, T2 ).

/* Check for match. If successful, bind Term  */
/* accordingly and print. Backtracking causes */
/* select to be resatisfied.                  */

solve( Search,Goal,Term ):-
     select,
     Search,
     Goal,
     writef( Term \),
     fail.
solve(_,_,_).


/*
.pa
*/

/* 'add' procedures */

add verb(V):-
     assert( verb(V) ),
     op( 250,fx,V ).

add constructor(C,F):-
     assert( constructor(C,F)),
     op( 200,fx,C ).

add Rspec :-
     functor( Rspec,record,_ ),
     assert( Rspec ).

/* 'delete' procedure */

delete Spec:-
     select,
     Spec,
     once kill,
     fail.
delete Spec.

/*
.pa
*/

/* User Information Help Clauses */

help:- help_text.
h:- help_text.

help_text:-
     writef( @nl & 'Search fields defined are:-' \ \),
     format( Search_fields ),
     putlist( Search_fields ),
     nl,nl,
     writef('Verbs defined are:-'\ \ ),     
     print_verbs,
     nl,nl,
     writeln('Constructors defined are:-'),
     print_constructors,
     nl,
     writef('Commands:'\ & 
             'all <report spec> <verb> <search spec>'\ &
             'add verb( <verbname> ).'\ &
             'add constructor( <name>,<format> ).'\ &
             'add record( <field contents> ).'\ &
             'delete <search spec>.'\   ),
     nl.

print_verbs:-
     verb(V),writef(V & ' '),fail.
print_verbs.

print_constructors:-
     constructor(C,T),writef(C & ' : ' & T),
     nl,fail.
print_constructors.


/*
.pa
*/

/* Translation of 'and' and 'or' into Prolog */

and(X,Y):- X,Y.
or(X,Y) :- X;Y.

/* General utility predicates */

append( [], X, X ).
append( [X|Y], Z, [X|P] ):- append( Y,Z,P ).

length( 0, [] ).
length( X, [P|Q] ):-
     length( Z,Q ), X is Z+1.

putlist( [] ).
putlist( [X|Y] ):-
     write( X ),
     write(' '),
     putlist( Y ), !.

writef( X & Y ):- !,writef(X),writef(Y).
writef( @X ):- !,call(X).
writef( X\ ):- !,writef(X),nl.
writef( X ):- write(X).
writeln( X ):- writef( X\ ).


once(X) :- call(X), !.

/* Start up the program, ensuring reports */
/* are directed to the terminal and that  */
/* the user is correctly returned to      */
/* Prolog at the end of the DBAQL session */

?-seeing(F),see(user),database_system,see(F).



     
