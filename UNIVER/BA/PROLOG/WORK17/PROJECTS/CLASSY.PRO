
/*------------------------------------------------------------------------*/
/*                                                                        */
/*        'CLASSIFY' DEMONSTRATION EXPERT SYSTEM SHELL.                   */
/*        ---------------------------------------------                   */
/*                                                                        */
/*            Expert Systems Limited. Oxford, UK.                         */
/*                                                                        */
/*                                                                        */
/*        CLASSIFY is a simple demonstration Expert System                */
/*        'Shell' which demonstrates some of the principles upon          */
/*        which real-world expert systems are based and which             */
/*        may be used as a teaching aid.                                  */
/*                                                                        */
/*------------------------------------------------------------------------*/


?- op( 250, xfy, & ).
?- op( 1, fx, @ ).
?- op( 251, fx, { ).
?- op( 250, xf, } ).
?- op( 100, fx, once ).
?- op( 60, xfx, such_that ).
 

/*

--- Background Notes --- 

CLASSIFY uses a tree of categories for its classification.    Each node of the 
tree is either a leaf (denoting    an actual object,  such as "penguin") or  a 
category    (denoting a class of objects, such as "mammal" or    "carnivore").

If  a node is a category,  then it has other nodes hanging    from it  - these 
are  the  subcategories of the parent    category.  Subcategories of the  same 
category  must     represent  disjoint  sets  of  objects  - if  "mammal"  has    
subcategories "carnivore" and "rodent",  no animal may    be both a rodent and 
a carnivore.

The  classification  tree is represented as Prolog  assertions :-
      rule(  N, Type,  Cat,  Subcat,  Conds )
where
      N is a rule number, unique amongst rules.
      Type is 'category' or 'leaf'
      Cat is the name of a parent category.
      Subcat is the name of one of its subcategories.
      Conds is a list of numbers, each denoting a condition.

Conditions are represented as
      cond( N, Statement )
where
      N is a condition number, unique amongst conditions.
      Statement is an atom  defining the condition.

.pa
Each  condition  represents  an  atomic test,  which  can  not     be  further 
analysed.  The condition list used by a rule    denotes a list of conditions - 
all of which must be true    for the rule to be satisfied.  
Thus rule N can be read as:

    For all x, if x is a Cat, and all conditions in Conds hold for x,
               then x is a Subcat
    or
    For all x such that x is a Cat, if all conditions in Conds hold for x, 
               then x is a Subcat
    or
    There is no x such that x is a Cat and all conditionsin Conds hold for x, 
               and x is not a Subcat

There  may  be more than one rule mapping a category to a subcategory  - these 
rules are treated as alternatives, only one of which need be satisfied.

To recognise an object of category Cat, CLASSIFY tries all rules mapping a Cat 
to  some Subcat.  For each rule,  CLASSIFY acquires answers to its conditions, 
and  stores  them  for  later reference.  The rules  are  tried  in  order  of 
assertion, which should also be order of rule number. The first rule which has 
all its conditions satisfied is deemed to categorise the object. 

Once a rule is satisfied,  it can never be un-satisfied. This means that if an 
object has been classified as a Subcat,  it can never be un-classified as such 
- CLASSIFY does not backtrack up the rule tree.

This implies that the order of rules may be important. Given rules
      1)  An animal is a bird if it lays eggs and it has feathers
      2)  An animal is a reptile if it lays eggs
then rule 2 is equivalent to
      2') An animal is a reptile if it lays eggs and it doesn't have feathers
because all the feathered egg-layers have been accepted by rule 1.
Logically, given
      1)  for all x in Cat: x in Cond1 implies x in Subcat1
      2)  for all x in Cat: x in Cond2 implies x in Subcat2
then rule 2 is equivalent to 
      2') for all x in Cat: (x in Cond2 and x not in Cond1)implies x in Subcat2.
where Cond denotes the set of all objects satisfying the conditions for Cond, 
etc.

.pa
Responses To CLASSIFY Queries - The Explanation Facilities
----------------------------------------------------------

A  consultation  session with CLASSIFY begins with the system asking the  user 
for the most definitively known category of object described by the  knowledge 
base.  The  system  uses this answer to identify a node in the knowledge  base 
from which to start the consultation session.  If the knowledge base is viewed 
as  a hierarchical tree of categories,  then this node is the tree  node  from 
which the following consultation descends.

The  consultation  session  proceeds with CLASSIFY asking the  user  questions 
about various observable attributes of the unknown object. In response to such 
questions, the user may respond with one of the following:

Response              Meaning
--------              -------

y or yes            Answer YES : the hypothesis is true.

n or no             Answer NO: the hypothesis is false.

u or unknown        Answer DONT-KNOW: the hypothesis cannot be decided

w or why            Answer WHY: Explain why the question is being asked

x                   Answer X-ON: Turns 'Explanation mode' ON for use in WHY

nx                  Answer X-OFF: Turns 'Explanation mode' OFF

i                   Answer INFORM: Turns 'Inform mode' ON

q                   Answer QUIET: Turns 'Inform mode' OFF

? or h or help      Answer HELP:  Explains the response options


The  'Explanation mode' is examined when the user responds WHY to a  question. 
If the mode is ON, then the actual rules used in the chain of reasoning so far 
are  expanded and displayed on the screen.  If the mode is OFF,  then  a  more 
concise form of WHY is available when only the rule numbers are given.
The default is 'Explanation mode' OFF.

The  'Inform  mode'  is a mode which controls the  reporting  of  intermediate 
inference  conclusions  during the consultation.  With the mode ON,  the  each 
idividual  category-subcategory inference step (conclusion) is reported as  it 
happens. With 'Inform mode' OFF, this information is not provided. 
The default is 'Inform mode' OFF.

.pa
CLASSIFY Database Structures
----------------------------

rule( N, Type, Cat, Subcat, Conds )
     means
     "Rule number N maps category Cat to Subcat provided all
      Conds are true"

cond( N, Statement )
     means
     "Condition N is the list of words Statement"

fact( Cond, Ans, How )
    means
    "Condition Cond has answer Ans obtained by How".
    Ans will be y or n.
    How will be 'from_data' or 'to_satisfy_rule'
        depending on whether the answer was obtained by
        asking the user for it, or assuming it when
        acquiring a rule.

rule( N )
    means
    "Rule number N has been satisfied".
    Is used for explanation.

current_rule( N )
    means
    "The rule being tried now is number N".
    Used in explanation.

start_category( C )
    means
    "The category with which the current classification
    started was C". Used in explanation.
 
.pa
/*
/*--------------------------------------------------------------------*/
/*     [1] CLASSIFY Expert System SHELL Main Control Procedure        */
/*--------------------------------------------------------------------*/

classify :-
     read_knowledge_base,
     repeat,
        prologue,
        most_definitive_category( Cat ),
        recognise( Cat ),
        epilogue,
     fail.


read_knowledge_base:-
     writef( / & 'CLASSY Expert System Shell.  Version 1.0' &
             / & '----------------------------------------' &
             / & / & 'Knowledge base ( Type filename or "new" ): ' ),
     read_line( K_Base_File ),
     consult_KB( K_Base_File ).

consult_KB( new ):-
     assert( next_rule_no(1) ),
     assert( next_cond_no(1) ),
     writef( / & 'Knowledge Base empty.' & / ).
consult_KB( KB_file ):-
     consult( KB_file ).


most_definitive_category( Cat ):-
     writef( / & 'State the most definitive known category: '),
     read_line( Cat ),
     nl,
     retractall( fact(_,_,_) ),
     retractall( rule(_) ),
     retractall( start_category(_) ),
     asserta( start_category( Cat ) ),
     !.

/*
.pa
*/ 
/*----------------------------------------------------------------------*/
/*      [2] Main Classification Inference Engine Predicates             */
/*----------------------------------------------------------------------*/
     
/*
RECOGNISE( Category )

"recognise"  questions  the user,  trying to find out what kind  of  leaf  his 
object  is.  It  recursively   calls "branch_from" to define the object  as  a 
subcategory of Category. It only succeeds if it has identified the object.
It fails if it can't identify the object,  because a call of "branch_from" has 
failed.
*/

recognise( Category ) :-
     branch_from( Category, Subcat, R, Type ), !,
     asserta( rule(R) ),
     (
     Type=leaf, 
     start_category( Scat ),
     writef( / & 'Conclusion:' &
             / & '-----------' & 
             / & 'I deduce from the facts described to me' &
	     / & 'that the final sub-category of "' & Scat &
                  '" is "' & Subcat & '".' & / & / )
     ;
     recognise( Subcat )   
     ),
     !.
 
 
/*
.pa
*/
/*
BRANCH_FROM( Cat, Subcat, R, Type ):

Cat is a category to which the object being recognised is known to belong.
"branch_from"  tries  to establish a subcategory of Cat to which  it  belongs; 
instantiating Subcat to that subcategory and R to the number of the rule used.

If there are no rules which identify Cat, "branch_from" will ask for a new one 
- if that rule is consistent with the data and other rules, it will be assumed 
to define the Subcat which the Cat is. 

"branch_from"  will fail only it can't find a rule to subcategorise  Cat,  and 
the user refuses to give a new one.
*/

branch_from( Cat, Subcat, R, Type ) :-
        ( 
        rule( _, _, Cat, _, _ ), !,   /*  Is there at least one rule subcategorising Cat?  */
          (
            rule( N, Type, Cat, Subcat, Conds ),
            bt_assert( current_rule(N) ),       /* Remeber current rule being
                                                   tried for explanations */
            discover( Conds ),
            R = N,
            retract( current_rule(N) ), 
            conclusion( Cat, Subcat, N ), !
          ;
          /*  All rules subcategorising Cat failed - ask for another one  */
          get_another_rule_for( Cat, Subcat, R ), !
          )
        ;
        get_first_rule_for( Cat, Subcat, R ), !  
        ).



/*  CONCLUSION( Caty,Subcaty,N ):
    Called from "branch_from" to say that the object being
    recognised belongs to Subcaty of Caty by using rule N.
    Always succeeds and can't be resatisfied.
*/

conclusion(Caty,Subcaty,N) :- 
        inform,
        writef( / & @tab(4) & 'Sub-Classification:' &
		/ & @tab(4) ),
        print_C_is_S_using_N(Caty,Subcaty,N),
        nl,nl,
        !.
conclusion(_,_,_).
 
/*
.pa
*/
/*----------------------------------------------------------------------*/
/*      [3] Condition Investigation Procedures                          */
/*----------------------------------------------------------------------*/

/*  discover( L ):
      L is a list of condition numbers.
      Succeed only if all the conditions are satisfied
      by data from the user.
*/

discover([]).
discover([X|Y]) :- 
        find_out_if(X),
        discover(Y).
 
 
/*  find_out_if(C):
      Succeed only if the condition with number C is
      satisfied. If the answer to it is known already, 
      use that, else ask a question.
*/

find_out_if(C) :- 
        fact(C,y,_),
        !.
find_out_if(C) :- 
        fact(C,n,_),
        !,
        fail.
find_out_if(C) :-
	fact(C,dont_know,_),
	!,
	fail.
find_out_if(C) :- 
        cond(C,Premise),
        respond_to(Premise,Ans),
        !,
        ( 
          is_yes( Ans ), assert( fact(C,y,from_data) )
        ;
          is_no( Ans ), assert( fact(C,n,from_data) )
        ;
	  is_dont_know( Ans ),assert( fact(C,dont_know,from_data))
	), !,
        is_yes(Ans).
 
/*
.pa
*/ 
/*  respond_to(P,A):
      P is the English statement defining a condition.
      Ask if it is true, and set A to the result.
*/

respond_to(Premise,Ans) :- 
        repeat,
        writef('Is it true that ' & @putlist(Premise) & '? '),
        read_line(Ans),
        check(Ans).
 
 
/*  check( Ans ):
      If Ans means yes or no, succeed.
      If it requests an explanation or other action,
      fulfill its request and try again, else fail.
*/

check(Ans) :- is_yes(Ans).
check(Ans) :- is_no(Ans).
check(Ans) :- is_dont_know(Ans).
check(Ans) :- is_why(Ans), 
               line_of_reasoning('am trying to establish '),
               !, fail.
check(Ans) :- is_inform(Ans), do_inform, !, fail.
check(Ans) :- is_quiet(Ans), do_quiet, !, fail.
check(Ans) :- is_explain(Ans), do_explain, !, fail.
check(Ans) :- is_noexplain(Ans), do_noexplain, !,fail.
check(Ans) :- is_help(Ans), do_help, !,fail.
check(_) :-
        write('Please answer ''yes'',''no'',''why'' or ''?'' for help.'),
        nl,
        fail.

is_yes(yes).   is_yes(y).

is_no(no).     is_no(n).

is_dont_know( unknown ).  is_dont_know( u ).

is_why(why).   is_why(w).

is_inform(i).  is_inform(inform).

is_quiet(ni).    is_quiet(noinform).

is_explain(explain).     is_explain(x).

is_noexplain(noexplain). is_noexplain(nx).

is_help( ? ).       is_help( h ).       is_help( help ).

/*
.pa
*/
 
do_inform :- not(inform), 
             assert(inform), 
             writef('INFORM mode turned ON' & / ),!.
do_inform.

do_quiet :- retract(inform), 
            writef('INFORM mode turned OFF' & / ),!.
do_quiet.

do_explain :- not(explain), 
              assert(explain),
              writef('EXPLANATION mode in WHY turned ON' & /),!.
do_explain.

do_noexplain :- retract(explain), 
                writef('EXPLANATION mode in WHY turned OFF' & /),!.
do_noexplain.


do_help:-
     writef(   / & 'You may respond to a question with one of:' & / &
               / & 'y or yes  :         Answer YES.' &
               / & 'n or no   :         Answer NO.' &
               / & 'w or why  :         Answer WHY.' &
               / & 'x         :         Explanation ON.' &
               / & 'nx        :         Explanation OFF.' &
               / & 'i         :         Inform mode ON.' &
               / & 'q         :         Inform mode OFF.' &
               / & '? or h    :         HELP provided.' & /
                 & / ).
 
/*
.pa
*/
/*------------------------------------------------------------------*/
/*     [4] Rule Acquistion Primitive Procedures                     */
/*------------------------------------------------------------------*/
 
/*  GET_FIRST_RULE_FOR( Cat,Subcat,R ):
      There are no rules defining a Subcat.
      Ask for one, and check it. Repeat until
      the user refuses, when fail; or until
      he gives a correct rule, when succeed.
*/

get_first_rule_for( Cat, Subcat, R ) :-
        writef( / & 'I have no knowledge about the category "' & Cat &
                '".' & / ),
        writef('Do you want to add a new rule to sub-categorise it? '  ),
        getyn( A ), !,
        ( A = y,
          acquire_rule( Cat, Subcat, R )
        ).
 

 
/*  GET_ANOTHER_RULE_FOR( Cat,Subcat,R ):
      As for "get_first_rule_for", but called if there are
      already rules identifying a Subcat.
*/

get_another_rule_for( Cat, Subcat, R ) :-
        writef( / & 'I cannot identify the sub-category of "' &
                Cat & '". ' & / ),
        check_unknown_facts,
	writef('Do you want to add a new rule to identify it? '  ),
        getyn( A ), !,
        ( A = y,
          acquire_rule( Cat, Subcat, R )
        ).

 
check_unknown_facts :-
	fact( _,dont_know,_ ),
	nl,
        writef('However, this may not be due to a deficiency'
	  & / &
	  'in the rule base because: ' & / ),
	list_dont_know_facts,
	nl.
check_unknown_facts .

list_dont_know_facts :-
	fact( C,dont_know,_),
	print_unknown_fact(C),
	fail.
list_dont_know_facts.

 
/*  ACQUIRE_RULE( Cat, Subcat, R ):

      Ask the user which subcategory of Cat he wants to
      define, and get a rule for it. Check the rule against
      other rules and data. Keep trying until the rule he
      gives is correct, when succeed; or until he refuses,
      when fail.
      Instantiate Subcat and R to the subcategory and rule number.
*/

acquire_rule( Cat, Subcat, R ) :-
        writef( / & 'What sub-category of "' & Cat &
                '" are you considering?' & / & @tab(4) ),
        read_line( Subcat ),
        category_check( Cat, Subcat ),
        get_condition_list( Cat, Subcat, Conds ),
        nl,
        rule_type( _, _, Subcat, _, Type ),
        check_and_add_rule( Cat, Subcat, Conds, Type, R ), !.

acquire_rule( Cat, Subcat, R ) :-
        /*  Here if the rule given was bad - try again.  */
        writef( / & 'Rule not accepted.' &
		/ & 'Do you want to try again? ' ),
        getyn( A ), !,
        ( A = y, acquire_rule( Cat, Subcat, R ) ), !.
 
 
/*  get_condition_list( Cat, Subcat, Conds ):
      Ask for conditions which define a Cat as being
      a Subcat. If they are syntactically bad, fail
      else instantiate Conds to the list of condition
      numbers. The conditions will be asserted into the
      rulebase.
*/

get_condition_list( Cat, Subcat, Conds ) :-
        writef( / &
                'Enter the conditions which must be true for "' & 
                Subcat & '" to be a' & / & 'sub-category of "' &
                Cat  &  '" ( terminate with a ''.'' ) :' & / & @tab(4) 
              ),
        read_in( W ),
        conditions_parse( W, Conds ).
 

/*  Read_in a sentence (typed by the user) as a string of atoms
    (Taken from Clocksin & Mellish)
*/

read_in([W|Ws]) :-
	get0(C),
	readword(C,W,C1),
	restsent(W,C1,Ws).

restsent(W,_,[]) :-
	lastword(W),
	!.

restsent(W,C,[W1|Ws]) :-
	readword(C,W1,C1),
	restsent(W1,C1,Ws).

readword(C,W,C1) :-
	single_character(C),
	!,
	name(W,[C]),
	get0(C1).

readword(C,W,C2) :-
	in_word(C,NewC),
	!,
	get0(C1),
	restword(C1,Cs,C2),
	name(W,[NewC|Cs]).

readword(C,W,C2) :-
	get0(C1),
	readword(C1,W,C2).

restword(C,[NewC|Cs],C2) :-
	in_word(C,NewC),
	!,
	get0(C1),
	restword(C1,Cs,C2).

restword(C,[],C).

single_character(44).  /* , */
single_character(59).  /* ; */
single_character(58).  /* : */
single_character(63).  /* ? */
single_character(33).  /* ! */
single_character(46).  /* . */

in_word(C,C) :-
	C>96,
	C<123.         /* lower case ok */

in_word(C,L) :-
	C>64,
	C<91,
	L is C+32.    /* upper case to lower case */

in_word(C,C) :-
	C>47,
	C<58.         /* numbers */

in_word(39,39).
in_word(45,45).       /* - and ' */

lastword('.').
lastword('!').
lastword('?').


/*
.pa
*/ 
/*  category_check( Cat, Subcat ):
      If Subcat is already defined as a subcategory of a
      category which is not Cat, then complain and fail;
      else succeed.
*/

category_check( Cat, Subcat ) :-
        rule( N, _, C, Subcat, _ ), C \= Cat,
        writef(/ & 'Category "' & Subcat & '" has already been used in rule ' & N & /),
        writef('as a subcategory of "' & C & '". ' & /),
        writef('You may not therefore use it as a subcategory of "'
                 & Cat & '". ' & /),
        !, fail.
category_check( _, _ ).

/*
.pa
*/
/*----------------------------------------------------------------*/
/*     [5] Rule Consistency Checking Predicates                   */
/*----------------------------------------------------------------*/

/*  check_and_add_rule( Cat, Subcat, Conds, Type, R ):
      Check that the conditions Conds which define
      a Cat to be a Subcat (which is either a leaf or
      category, per Type), agree with the data, and with
      the other rules.

      If they do, instantiate R to the new rule number and
      add the rule to the rulebase.

      If they don't, undo any assumptions made when acquiring
      the rule, and fail.
*/

check_and_add_rule( Cat, Subcat, Conds, Type, R ) :-
        check_consistent_with_rules( Cat, Subcat, Conds, Type, Rules_ok ), !,
        check_consistent_with_data( Cat, Subcat, Conds, Type, [],
                                                Facts_assumed, Data_ok ), !,
        and( Data_ok, Rules_ok, All_ok ),
        ( 
          All_ok = n, undo_assumptions( Facts_assumed ), !, fail
        ;
          append_rule( R, Type, Cat, Subcat, Conds )
        ), !.
 
 
/*  undo_assumptions( L ):
      L is a list of "fact(Cond,...)" terms.
      Retract each one.
*/

undo_assumptions( [] ).
undo_assumptions( [ Cond | Tl ] ) :-
        retract( fact(Cond,y,to_satisfy_rule) ),
        undo_assumptions( Tl ).
 
/*
.pa
*/ 
/*  CHECK_CONSISTENT_WITH_DATA(Cat,Subcat,Conds,Type,Old_facts,
                         All_new_facts,Consistent):
      Check that the conditions whose numbers are in list
      Conds, are consistent with the data. 

      Old_facts is a list of facts which have already been
      assumed as true in order that the rule being acquired
      be correct. All_new_facts is instantiated to Old_facts
      plus any new ones assumed to satisfy Conds.

      Always succeeds; sets Consistent to n if there was an
      inconsistency, else to y.
*/

check_consistent_with_data( Cat, Subcat, [ Cond1 | Rest ], Type, Old_facts, All_new_facts, Consistent ) :-
        check_consistent_with_data( Cat, Subcat, Cond1, Type, Old_facts, New_facts, Ok ),
         check_consistent_with_data( Cat, Subcat, Rest, Type, New_facts, All_new_facts, Rest_ok ),
         and( Ok, Rest_ok, Consistent ), !.
check_consistent_with_data( _, _, [], _, F, F, y ).
 
 
/*
    These clauses for check_consistent_with_data are
    used to deal with one condition, rather than a list
    of them.
*/

check_consistent_with_data( Cat, Subcat, Cond, Type, Old_facts, Old_facts, y ) :-
        fact( Cond, y, _ ), !.
check_consistent_with_data( Cat, Subcat, Cond, Type, Old_facts, Old_facts, n ) :-
        fact( Cond, Truth, _ ),
        writef('The condition' & @print_fact(Cond,y) &
                'is inconsistent with the fact already established that' & /
                & @print_fact(Cond,Truth) & /
              ), !.
check_consistent_with_data( Cat, Subcat, Cond, Type, Old_facts, [ New | Old_facts ], y ) :-
        writef('Fact recorded: ' & @print_fact(Cond,y) & / ),
        assert( fact(Cond,y,to_satisfy_rule) ).

/*
.pa
*/
/*  CHECK_CONSISTENT_WITH_RULES( Cat,Subcat,NewConds,Type,Consistent ):

      Checks that the new conditions New_conds defining a
      Cat to be a Subcat are consistent with all the other
      rules which subcategorise a Cat.

      To do this, it first checks New_conds against all
      other rules defining a Subcat, and then against all
      rules defining a non-Subcat.

      Each check is done in the same manner:
      New_conds are compared against the conditions 
      Old_conds of some rule N, to see how the sets described
      by Old_conds and New_conds are related.

      Some relations are deemed to indicate an error, and
      if there is such an error, it will be reported.

      This procedure always succeeds: it sets Consistent
      to n if an inconsistency was detected, else to y.
*/

check_consistent_with_rules( Cat, Subcat, New_conds, Type, Consistent ) :-

        /*  Check against other rules for Subcat  */
        { X1 = L1 such_that
                 ( rule( N1, _, Cat, Subcat, Old_conds1 ),
                   inconsistent_with_conditions_for_same_subcategory( Old_conds1, New_conds, Why1 ),
                   report_rule_inconsistency( N1, Why1, same, Subcat ),
                   X1 = found
                 )
        } , !,

        /*  Check against rules for a non-Subcat  */
        { X2 = L2 such_that
                 ( rule( N2, _, Cat, Subcatx, Old_conds2 ), Subcatx \= Subcat,
                   inconsistent_with_conditions_for_different_subcategory( Old_conds2, New_conds, Why2 ),
                   report_rule_inconsistency( N2, Why2, different, Subcat ),
                   X2 = found
                 )
        } , !,

        /*  If errors found, L1 or L2 will be non-empty  */
        (
          L1 = [], L2 = [], Consistent = y
        ;
          Consistent = n
        ), !.
 
/*
.pa
*/ 
/*
   INCONSISTENT_WITH_CONDITIONS_FOR_(same/different)_SUBCATEGORY:

      If Old_conds and New_conds appear to be in conflict
      as definitions of the same subcategory, set Why
      to the relation of Old_conds with New_conds and succeed;
      else fail.
*/

inconsistent_with_conditions_for_same_subcategory(Old_conds,New_conds,Why):-
        compare_conditions( Old_conds, New_conds, Relation ),
        (
          Relation = equal, Why = equal
        ;
          Relation = subset, Why = subset
        ;
          Relation = superset, Why = superset
        ), !.
 
inconsistent_with_conditions_for_different_subcategory( Old_conds, 
                                                         New_conds, Why ):-
	compare_conditions( Old_conds, New_conds, Relation ),
	(
	Relation=equal, Why=equal
	;
	Relation=superset,  Why=superset
	), !.

compare_conditions( A,B,Relation ):-
        compare_sets( B,A,Relation ).

/*
.pa
*/
/*  REPORT_RULE_INCONSISTENCY( Old_rule,Why,Like,New_subcat ):

      Old_rule:         the number of an old rule.
      Why     :         a word for a set relation.
      Like    :         'same' if the old rule defines the same subcategory
                        as the new one, else 'different'.
      New_subcat:       Subcategory defined by the new rule.
 
      Reports that the old rule conflicts with the new rule because
      the set defined by its conditions is related to the set defined
      by the conditions of the rule currently being checked by
      the relation in Why.
*/

report_rule_inconsistency( Old_rule, Why, Like, New_subcat ) :-
        rule( Old_rule, _, _, Old_subcat, _ ),
        ( Why = equal, Rel = 'equal to'
        ; Why = subset, Rel = 'a subset of'
        ; Why = superset, Rel = 'a superset of'
        ),
        inconsistency_details( Like, Why, Problem ),
        nl,
        writef('Your new rule may conflict with rule ' & Old_rule &
                ' which defines sub-category ' & / &
                @tab(4) & '"' & Old_subcat & '". ' & / ),
        writef('The conditions for rule ' & Old_rule & ' are ' & Rel & ' your new ones. ' & / ),
        writef('This means that ' & / & Problem & '. ' & /  & / ).
 
 
/*  inconsistency_details( Like, Rel, Reason ):
      Like: 'same' or 'different'
      Rel : name of a relation.

      Sets Reason to text saying why the relation between
      two sets described by old conditions and new conditions
      for subcategories which are (same or different) is bad.
*/
inconsistency_details( same, equal, 
                       'the new rule is redundant because it is the same as the old one' ).
inconsistency_details( same, subset, 
                       'the new rule may be redundant because if anything satisfies it' &
                       / & 'it will satisfy the old one' ).
inconsistency_details( same, superset, 
                       'the old rule may be redundant because if anything satisfies it' &
                       / & 'it will satisfy the new one' ).
inconsistency_details( different, equal, 
                       'the rules define different categories so must have different conditions' ).
inconsistency_details( different, superset, 
                       'if anything would match the new rule, it will be matched' &
                       / & 'and classified by the old one' ).
 
/*
.pa
*/
/*-------------------------------------------------------------------*/
/*     [6] PRE-CONSULTATION PROLOGUE PROCEDURES                      */
/*-------------------------------------------------------------------*/


prologue :-
        get_prologue_command(C), 
        do_prologue_command(C), 
        fail.
prologue.


get_prologue_command(C) :-
        repeat,
        print_prologue_options,
        write('Option? '),
        read_in_single_char(C),
        (C=c, !, fail  ;  true).


print_prologue_options :-
        nl,
	write('PRE-CONSULTATION OPTIONS'),nl,
	write('------------------------'),nl,
        write('Start a consultation (c)'), nl,
        write('See the rules (r)'), nl,
        write('Manipulate rulebase (m)'),nl,
        write('Copy the rulebase to file (f)'), nl,
	write('Exit from the program (e)'),nl,
        nl.


do_prologue_command(C) :- dpc(C), !.


dpc(r) :- print_rulebase.
dpc(m) :- manipulate_rulebase.
dpc(e) :- restart.
dpc(f) :- file_rules.
dpc(_) :- write('Not a valid option.'), nl.


/*
.pa
*/
/*------------------------------------------------------------------*/
/*     [7] POST_CONSULTATION EPILOGUE OPTION PROCEDURES             */
/*------------------------------------------------------------------*/


epilogue :-
        get_epilogue_command(C), 
        do_epilogue_command(C), 
        fail.
epilogue.


get_epilogue_command(C) :-
        print_epilogue_options,
        repeat,
        nl,
        write('Option? '),
        read_in_single_char(C),
        (C=e, !, fail ; true).


print_epilogue_options :-
        nl,
        write('END OF CONSULTATION OPTIONS'), nl,
	write('---------------------------'), nl,
        write('See categories established (c)'), nl,
        write('See facts established (f)'), nl,
        write('See line of reasoning (r)'), nl,
        write('Display this list of options (h)'), nl,
	write('End this consultation (e)'), nl,
        nl.


do_epilogue_command(C) :- dec(C), !.


dec(c) :- print_categories.
dec(f) :- print_out_facts.
dec(r) :- post_line_of_reasoning.
dec(h) :- print_epilogue_options.
dec(_) :- write('Not a valid option (use h for help)'), nl.

/*
.pa
*/
/*------------------------------------------------------------------*/
/*     [8] PROLOGUE MENU COMMAND SERVICE PROCEDURES                 */
/*------------------------------------------------------------------*/

/*  FILE_RULES:
      Ask for a filename, and write the Prolog clauses
      defining the rulebase to that file.
      Always succeeds if the rulebase is not corrupt.
*/

file_rules :-
        nl,
        write('File? (''user'' for terminal) '),
        read_line( File ),
        telling( Out ), tell( File ),
	writeclause( next_rule_no(_) ),
        writeclause( next_cond_no(_) ),
        { writeclause( rule(_,_,_,_,_) ) } ,
        { writeclause( cond(_,_) ) },
        told, tell( Out ), !.


/*  writeclause( C ):
      C must be a valid argument to "clause".

      "writeclause" will find the first clause matching
      C and write it, followed by a dot and newline, then
      succeed.

      On being resatisfied, it will write the next clause matching C.
      It will fail if there are no such clauses.
*/

writeclause( C ) :-
        clause( C, Body ),
        ( 
          Body = true, writeq( C )
        ;
          Body \= true, writeq( (C:-Body) )
        ),
        write(' . '), nl.

/*
.pa
*/
/*  PRINT RULEBASE  */

print_rulebase :-
        nl,
        write('File? (''user'' for terminal) '),
        read_line(File),
        tell(File),
        { (
          rule(N, Type, Cat, Subcat, Conds),
          print_rule(N, Type, Cat, Subcat, Conds)
        ) } ,
        told, !.

print_rule(N, Type, Cat, Subcat, Conds) :-
        writef( / &
                'Rule ' & N & ':' & / &
                @tab(8) & 'The category     "' & Cat & '"' & / &
                @tab(8) & 'has sub-category "' & Subcat & '"' & / &
                @tab(8) & 'provided that:' & /
              ),
        print_cond_list(Conds,21),
        nl.

print_cond_list([H|T], Spaces) :-
        tab(Spaces), tab(4), print_cond(H),
        print_cond_list_1(T, Spaces), nl.

print_cond_list_1([],_) :- write('.').
print_cond_list_1([H|T], Spaces) :-
        nl, tab(Spaces), write('and '), print_cond(H),
        print_cond_list_1(T, Spaces).

print_cond(C) :-
        cond(C, Statement),
        putlist(Statement).
/*
.pa
*/
/*--------------------------------------------------------------*/
/*     [9] EPILOGUE MENU COMMAND-SERVICE PROCEDURES             */
/*--------------------------------------------------------------*/

post_line_of_reasoning :-
        retract( rule(N) ),
        assert( current_rule(N)),
        line_of_reasoning('have established '),
        retract( current_rule(_)),
        asserta( rule( N )).

line_of_reasoning( Sense ) :-
        current_rule(N),
        rule_details(N,Caty,Subcaty),
        print_current_rule(N,Sense,Caty,Subcaty),
        print_other_rules_if_any,
        print_definitive_catagory.

print_other_rules_if_any :-
        rule(_),
        print_other_rules.
print_other_rules_if_any .

print_definitive_catagory :-
	start_category( Scat ),
	writef( / & 'AND:' & / & / & 'I know that "' &
                Scat & '" was the starting catagory of this' &
	       / & 'consultation.' ),
	nl,nl,
	!.

print_other_rules :-
        { (
          rule(N),
          rule_details(N,Caty,Subcaty),
          print_rule_details(N,Caty,Subcaty)
        ) },
	!.

print_current_rule(N,Sense,Caty,Subcaty) :-
        writef( / & 'I ' & Sense & ' ( Rule ' & N &
		' ) that the category ' & /
                &  '"' & Caty & '" has the sub-category "' &
                Subcaty & '" .' & / ), 
        giverule(N).

/*
.pa
*/

print_rule_details(N,Caty,Subcaty) :-
	writef( / & 'AND:' & / & /  &
	       'I  have  established ( Rule ' & N & ' ) that' & /  
	        &  'category "' & Caty 
                & '" has the sub-category "'
                & Subcaty & '"' & / & 'because:-' & / ),
	rule( N,_,Caty,Subcaty, Conds ),
	print_cond_list( Conds,0 ),
        giverule(N),
	!.

print_C_is_S_using_N(Caty,Subcaty,N) :-
        writef( '"' & Subcaty & '" is the sub_category of "' & Caty &
                '" using rule ' & N ),
        giverule(N).

rule_details(N,Caty,Subcaty) :-
        rule(N,_,Caty,Subcaty,_),
        !.

giverule(N) :-
        explain,
        !,
        nl,
        rule(N,Type,Cat,Subcat, Conds),
        print_rule(N, Type, Cat, Subcat, Conds).
giverule(N).

print_categories :-
        nl,
        write('The categories are: '), nl, tab(4),
        start_category(C), write(C),
        { (
          rule(N),
          rule_details(N,_,Subcaty),
          tab(4),
          write(Subcaty)
        ) },
        nl, !.


print_out_facts :- nl,write('The facts established are: '),nl,
        print_facts.


print_facts :- { ( fact(C,V,_),print_fact(C,V) ) }, nl, nl, !.

/*
.pa
*/

print_fact(C,y) :-
        !,print_true_fact(C).
print_fact(C,n) :- 
	!,print_false_fact(C).
print_fact(C,dont_know) :-
	!,print_unknown_fact(C).

print_true_fact(C) :- cond(C,Statement),tab(4),
        putlist(Statement),nl.


print_false_fact(C) :-
        cond( C, Statement ),
        tab(4),
        writef('it is not true that ' & @putlist(Statement) ),
        nl.

print_unknown_fact(C) :-
	cond( C, Statement ),
	tab(4),
	writef('it is not known whether ' & @putlist(Statement) ),
	nl.

/*
.pa
*/
/*-------------------------------------------------------------*/
/*     [10] RULEBASE MANIPULATION PROCEDURES                   */
/*-------------------------------------------------------------*/


/*  MANIPULATE_RULEBASE:
      Displays the rulebase options, then reads and executes
      user commands until he wants to consult.
      Always succeeds.
*/

manipulate_rulebase :-
        nl,
        write('RULEBASE MANIPULATION OPTIONS'), nl,
        write('-----------------------------'), nl,
        write('Show rule (s)'), nl,
        write('Delete rule (d)'), nl,
        write('Replace rule (r)'),nl,
        write('Add new rule (a)'),nl,
        write('End rulebase manipulation (e)'), 
        nl,
        choose_rulebase_action( X ), 
        ( X = consultation ;
          take_rulebase_action(X), 
          manipulate_rulebase    ),
        !.


/*  CHOOSE_RULEBASE_ACTION( X ):
    Give prompt asking for a character denoting some
    rulebase action, and read it. Repeat until character
    is valid, then succeed.
*/

choose_rulebase_action(X) :-
        repeat,
        nl,
        write('Choose rulebase option (h for help) :'),
        read_in_single_char(Y),
        check_rbact_ans(Y,X,_),
        !.

/*
.pa
*/
/*  TAKE_RULEBASE_ACTION( Action ):
      Action is an atom denoting some action. Performs
      the action, then succeeds - must never fail, or
      will upset alter_rule1.
*/

take_rulebase_action(show) :-
        find_rule_no(X),
        show_rule(X),
        !.
take_rulebase_action(delete) :-
        once find_rule_no(X),
        delete_rule(X),
        !.
take_rulebase_action(replace) :-
        once find_rule_no(X),
        replace_rule(X),
        !.

take_rulebase_action(add) :-
        next_rule_no(X),
        read_in_rule(X),
        write('Rule '),
        write(X),
        write(' added'),
        nl,nl,
        incr_rule_no(X),
        end_take_rbact(add),
        !.
take_rulebase_action( add ).




/*
      CHECK_RBACT_ANS( C, Act, Word ):
      Defines correspondence between rulebase
      command characters, atoms denoting them in this
      program, and English words for them.
*/

check_rbact_ans(s,show,'Show').
check_rbact_ans(d,delete,'Delete').
check_rbact_ans(r,replace,'Replace').
check_rbact_ans(a,add,'Add').
check_rbact_ans(e,consultation,'Return to consulting').
check_rbact_ans(h,help,'Help').
check_rbact_ans(_,_,_) :-
        write('Not a valid option (use h for help)'),
        nl,
        fail.

/*
.pa
*/
/*------------------------------------------------------------------*/
/*     [11] RULEBASE MANIPULATION PRIMITIVE COMMANDS                */
/*------------------------------------------------------------------*/

/* -- SHOW_RULE( N ) -- */

show_rule(0).
show_rule(X) :-
        X \= 0,
        ( display_rule(X) ; say_rule_not_found(X) ),
        !,
        end_take_rbact(show).


/* -- DELETE_RULE( N ) -- */

delete_rule(0).
delete_rule(X) :-
        X \= 0,
        rule(X,_,_,_,_),
        !,
        retract(rule(X,_,_,_,_)),
        write('rule '),
        write(X),
        write(' deleted'),
        nl,
        check_for_last_rule(X),
        end_take_rbact(delete).
delete_rule(X) :-
        X \= 0,
        say_rule_not_found( X ).

/* -- REPLACE_RULE( N ) -- */

replace_rule(0).
replace_rule(X) :-
        X \= 0,
        rule(X,_,_,_,_),
        retract(rule(X,_,_,_,_)),
        !,
        write('Rule deleted'),
        nl,
        read_in_rule(X),
        end_take_rbact(replace).
replace_rule(X) :-
        X \= 0,
        not rule(X,_,_,_,_),
        say_rule_not_found( X ),
        next_rule_no(Y),
        (X < Y ; 
         retract(next_rule_no(Y)), Z is X+1, assert(next_rule_no(Z))
        ),
        !,
        !,      read_in_rule(X),
        write('Rule '),
        write(X),
        write(' added'),
        nl,nl,
        end_take_rbact(replace).


/* -- DISPLAY_RULE( N ) -- */

display_rule(X) :-
        rule(X,Type,Cat,Subcat,Conds),
        print_rule(X,Type,Cat,Subcat,Conds).


/*  end_take_rbact( Act ):
      Act is a valid parameter to take_rulebase_action.
      Asks if the user wants to do another action of
      type Act; if so, does it and succeeds, else
      succeeds directly.
*/

end_take_rbact(Z) :-
        check_rbact_ans( _, Z, Do ),
        writef(Do & ' more rules? '),
        getyn(X),
        ( X = y, !, take_rulebase_action( Z ) ; true ), !.

find_rule_no(X) :-
        repeat,
        write('Type rule number (0 for no action) :'),
        input_integer(X).
say_rule_not_found( X ) :- 
        write('Rule '), 
        write(X), 
        write(' not found'), nl.

/*
.pa
*/
/*-------------------------------------------------------------------*/
/*     [12] RULE ENTRY PROCEDURES                                    */
/*-------------------------------------------------------------------*/

/*  READ_IN_RULE( X ):
     
      Reads a new rule numbered X, checks it, and repeats until
      the rule is good, then adds it to the rulebase.
      Succeeds if the user eventually gives a good rule;
      fails if he refuses.
*/

read_in_rule(X) :-
        nl,
	writef('For which catagory do you wish to enter a rule ? '),
	read_line( Cat ),
        writef( / & 'For which sub-category of "' & Cat & '"' &
                / & 'do you wish to enter a rule ? '),
        read_line( Subcat ),
        category_check( Cat,Subcat ),
        get_condition_list( Cat,Subcat,Conds ),
        nl,
        rule_type( _,_,Subcat,_, Type ),
        check_consistent_with_rules(Cat,Subcat,Conds,Type, OK),
        OK=y,
        append_rule( X,Type,Cat,Subcat,Conds ),
        !.

read_in_rule( X ) :-
        /*  Here if rule just read was bad  */
        nl,
        write('Rule not accepted.'),
        nl,
        write('Do you want to try again? '),
        getyn( A ),
        A = y, !, read_in_rule( X ), !.

/*
.pa
*/
/*-------------------------------------------------------------------*/
/*     [13] CONDITIONs PARSING PROCEDURES                            */
/*-------------------------------------------------------------------*/

conditions_parse(A,[E|F]) :-
        append(C,D,A),
        non_last_cond(C,E),
        !,
        conditions_parse(D,F).
conditions_parse(A,[B]) :-
        last_cond(A,B).


non_last_cond(A,B) :-
        !,
        last_member(C,and,A),
        rule_base_cond(C,B).


last_cond(A,B) :-
        !,
        last_member(C,'.',A),
        rule_base_cond(C,B).
last_cond(_,_) :-
        write('Error - conditions should be separated by "and" '),
        write('and terminated by a "." '), nl,
        fail.


rule_base_cond(A,B) :-
        cond(B,A),
        !.
rule_base_cond(A,B) :-
        next_cond_no(B),
        assert(cond(B,A)),
        incr_cond_no(B),
        !.


rule_type(W,Cat1,Cat2,Clist,C) :- rule(_,C,_,Cat2,_), !.
rule_type(W,Cat1,Cat2,Clist,C) :-
        write( 'Can the sub-category "' ), write( Cat2 ),
        write( '" be sub-categorised? '),
        getyn(A),
        nl,
        (A=y , C=category  ;  C=leaf).

/*
.pa
*/
/*-------------------------------------------------------------------*/
/*     [14] LOOPING CONTROL AND ALL SOLUTIONS PREDICATES             */
/*-------------------------------------------------------------------*/

/*    LIST_OF_ALL(X, Goal, List)
 
      List is a list of all Xs such that Goal.
      This routine will go through all possible solutions
      of Goal (by backtracking) collecting up all the resulting
      instantiations of X to produce the list List. The order
      of these Xs in List will be the order in which the solutions
      occurred.
     
      list_of_all was originally called bagof.
      bagof is now a standard evaluable predicate in Dec10
      Prolog. This code is not however a complete implementation
      since it fails to handle free variables in Goal (logically)
      correctly. See the DEC10 version 3 manual for details.
      This makes its behaviour slighly different in the case
      where there are no solutions to Goal. This code produces
      List = [], whereas the DEC10 bagof will fail.
     
      This implementation builds a "stack" in the database and
      collects it up at the end. This method should be more
      efficient than the retract/assert every time method,
      although I have never empirically verified this. Note
      that calling list_of_all recursively will work.
      Build stack of "all__found(X)"s in database until all P's
      have been satisfied.
      Then go to final clause for "list_of_all", and instantiate
      List to a list of X's.
*/

list_of_all(X,P,_):-
           asserta(all__found(mark)),
           call( P ),
           asserta(all__found(X)),
           fail.
list_of_all(_,_,List) :- all__collect_found([],L), !, List = L.
 
 
/*  ALL_COLLECT_FOUND( List, L )
 
    List: list.
    L: uninstantiated.

    Called by list_of_all, to instantiate L to List
    preceded by a list of all X's such that "all__found(X)".
*/
/*
.pa
*/ 
 all__collect_found(Sofar,L)
        :- all__getnext(X),
           !,
           all__collect_found([X|Sofar],L).
 
  all__collect_found(L,L).
 
/*
    ALL_GETNEXT(X): 

    Succeeds if there is a "all__found(X)" clause, when
    and X is not 'mark' - if success, X is instantiated
    to the argument of "all__found".
*/

  all__getnext(X)
        :- retract(all__found(X)),
           !,
           X \== mark.
 
 
/*  DO_FOR_ALL( Goal ) :
 
    Call Goal as many times as possible.
    Always succeeds.
*/

do_for_all( Goal ) :- call( Goal ), fail.

do_for_all( _ ) :- !.



/*  { ... }
    Defines the operators {, } and such_that, enabling
    backtracking loops to be written compactly.
    { Goal } is equivalent to do_for_all( Goal ).
    Goal will be called as many times as possible until
    there are no more solutions. If Goal is a conjunction
    of subgoals, it must be enclosed in round brackets.

    { Vars = List such_that Goal } is equivalent to
    list_of_all( Vars, Goal, List ). As above, Goal
    will be called as many times as possible until it
    can't be resatisfied. If Goal is a conjunction, it
    must be enclosed in round brackets.
*/

( { Vars = List such_that Goal } ) :-
        list_of_all( Vars, Goal, List ), !.
( { Goal } ) :-
        do_for_all( Goal ),!.
/*
.pa
*/
/*------------------------------------------------------------------*/
/*     [15] CHARACTER HANDLING & LEXICAL ANALYSIS                   */
/*------------------------------------------------------------------*/

/*   GETYN( A ): 
        Reads a character which should be a 'y' or 'n'.
        If it is, instantiates A to the character.
        If it isn'nt, prompts the user to type 'y' or 'n' and
        then calls itself.
        Cannot be resatisfied.
*/

getyn(A) :-
        read_in_single_char(A),
        (A = y ; A = n),
        !.
getyn(A) :- write('Please type y or n: '), getyn(A).



/* READ_LINE( A ) :
        Reads a line (terminated by LF), converts it to an atom
        and unifies it with A.
        Cannot be resatisfied.
*/

read_line( A ) :-
        get0(C), read_line_list(List,C), name( A , List ).

read_line_list( [],  10 ) :- !.   /* 10 = LF */
read_line_list( [] , 13 ) :- !.   /* 13 = CR */
read_line_list( [C|T] , C ) :-
        get0( NextC ), read_line_list( T , NextC ).

read_in_single_char(X) :-
        get_non_space(Y),
        repeat,
        get0( C ), ( C = 10 ; C = 13 ),
        name(X,[Y]),
        !.

get_non_space(C) :-
        repeat,
        get0(C),
        (C\=32 ; C = 13 ; C = 10 ),
        !.

/*
.pa
*/

/* -- ATOM/INTEGER TRANSLATION -- */

input_integer(X) :-
        read_line(A),
        name( A,Y ),
        integer_as_in_name(X,Y).

integer_as_in_name(A,B) :- integer_as_in_name(A,B,_).

integer_as_in_name(A,[B],1) :- !, digit_char(A,B).

integer_as_in_name(A,[B|C],D) :-
        digit_char(E,B),
        integer_as_in_name(F,C,G),
        D is G * 10,
        A is F + E * D.

digit_char(A,B) :-
        B >= 48,
        B =< 57,
        A is B - 48.

/*
.pa
*/
/*-------------------------------------------------------------------*/
/*     [16] Utility Predicates                                       */
/*-------------------------------------------------------------------*/

once( Goal ):-
     call( Goal ), !.

print_C_is_S_by_Cond( Cat, Subcat, Cond ) :-
        put_indef( Cat, lc ), write(' is '), put_indef( Subcat, lc ),
        write(' because '), print_true_fact( Cond ).

put_indef(Noun, ULcase) :-
        name(Noun, [H|T]),
        v_or_c(H,VC),
        article(VC, ULcase, Article),
        putlist([Article,Noun]),
        !.

put_article( Noun, ULcase ):-
     name( Noun, [H|T] ),
     v_or_c( H,VC ),
     article( VC, ULcase, Article ),
     write( Article ),
     !.

v_or_c(97, vowel).
v_or_c(101, vowel).
v_or_c(105, vowel).
v_or_c(111, vowel).
v_or_c(117, vowel).
v_or_c(_, consonant).


article(vowel, uc, 'An').
article(vowel, lc, an).
article(consonant, uc, 'A').
article(consonant, lc, a).

append_rule( R, Type, Cat, Subcat, Conds ) :-
        next_rule_no( R ),
        assertz( rule(R,Type,Cat,Subcat,Conds) ),
        write( 'Rule added:' ),
        print_rule( R, Type, Cat, Subcat, Conds ),
        incr_rule_no( R ).


bt_assert(X) :- assert(X).
bt_assert(X) :- retract(X), fail.
     
/*
.pa
*/

check_for_last_rule(X) :-
        next_rule_no(N),
        X is N -1,
        !,
        decr_rule_no(N).
check_for_last_rule(_).


decr_rule_no(N) :-
        retract(next_rule_no(N)),
        X is N - 1,
        assert(next_rule_no(X)).


 incr_rule_no(N) :-
        retract(next_rule_no(N)),
        X is N + 1,
        assert(next_rule_no(X)).


incr_cond_no(X) :-
        retract(next_cond_no(X)),
        Y is X + 1,
        assert(next_cond_no(Y)).
 
 
/*  WRITEF( G ):
      G is a sequence of terms joined by "&". 
      Each term T in G will be written by "write",
      except that if T = @Call, the term Call will
      be called .
*/

writef( X & Y ) :- !, writef( X ), writef( Y ).
writef( @X ) :- !, call( X ).
writef( / )  :- !, nl.
writef( X ) :- write( X ).
 
 
/*  putlist( L ):
      Write L as a sequence of elements, with one space
      between each.
*/
putlist([]) :- !.
putlist([H|T]) :- 
        write(H),
        tab(1),
        putlist(T).



/*  BOOLEAN OPERATIONS  */
 

/*
    Boolean values are denoted by y (true), and n (false).
    The effect of these procedures is undefined on other
    values.
*/


/*
    and( X, Y, Z ): Z is X and Y.
*/
and( n, n, n ).
and( n, y, n ).
and( y, n, n ).
and( y, y, y ).
 
 
/*  LIST OPERATIONS  */
 
 
/*  append( L1, L2, L3 ): L3 is L2 appended to L1.
*/
append([],L,L).
append([X|L1],L2,[X|L3]) :- append(L1,L2,L3).
 
 
/*  last_member( L1, E, L2 ):
      E is the last member of list L2, giving
      L1 when E is removed.
*/
last_member([],B,[B]).
last_member([X|A],B,[X|C]) :- last_member(A,B,C).
 
 
/*  member( X, L ):
      X is an element of list L.
*/
member( X, [ X | _ ] ).
member( X, [ _ | T ] ) :- member( X, T ).
 
 
/*  SET OPERATIONS  */
 
 
/*
    Sets are represented by lists of their elements.
    These procedures are undefined on lists which have
    duplicate elements.
*/


/*  subset( X, Y ):
      Succeeds if X is a subset of Y (including if X = Y).
      Fails otherwise. Can't be resatisfied.
      X and Y must be instantiated.
*/
subset( [ A | X ], Y ) :- member( A, Y ), subset( X, Y ).
subset( [], Y ).
 
 
/*  compare_sets( A, B, R ):
      Compares sets A and B, setting R to one of
      'subset', 'superset', 'equal', or 'incomparable'.
      Always succeeds, and can't be resatisfied.
      A and B must be instantiated.
*/

compare_sets( A, B, Relation ) :-
        (
          subset( A, B ), (
                            subset( B, A ), Relation = equal
                          ;
                            Relation = subset
                          )
        ;
          subset( B, A ), Relation = superset
        ;
          Relation = incomparable
        ), !.
 
 
?-seeing(F),see(user),classify,see(F).
