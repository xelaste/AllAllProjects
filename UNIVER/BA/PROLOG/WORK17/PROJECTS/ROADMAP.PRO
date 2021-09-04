

/*-------------------------------------------------------*/
/*                                                       */
/* ROADMAP - A Simple Route Finder Demonstration Program */
/*                                                       */
/*   This program illustrates the applicability of       */
/* Prolog to problems which involve searching a graph.   */
/*   The 'graph' in this case is a small section of a    */
/* city street plan, illustrated below and defined by    */
/* the 'on' predicates which occur later. These 'on'     */
/* clauses constitute an unambiguous topological         */
/* description of the streets and junctions.             */
/*   The logic of the program is as follows. The 'route' */
/* clause is given a starting and finishing point (A and */
/* B respectively) and instantiates P to a list whose    */
/* elements (of the form 'Junction-Road')                */
/* comprise a step-wise list of directions leading from  */
/* the start to the finish. This list is built up using  */
/* recursion, which effectively breaks the goal down     */
/* into subgoals repeatedly until all the subgoals are   */
/* directly soluble. (A subgoal is 'directly soluble'    */
/* when the two points passed to it as arguments are     */
/* adjacent.)                                            */
/*   The 'directions' predicate is simply a means of     */
/* obtaining the solution in a more readable form.       */
/*   As it stands this program will print out all        */
/* possible distinct routes between any two points with  */
/* the proviso that no point may be visited more than    */
/* once. This is necessary to prevent infinite looping.  */
/* Further constraints may be added as exercises - eg    */
/* perhaps only the shortest route might be required.    */
/*                                                       */
/*-------------------------------------------------------*/

/*
.pa
*/


/*  Diagrammatic representation of the 'city plan' */
/*  defined in the 'on' clauses on the next page.  */

/*

        |                         |                         |
        |                         |                         |  
  ----- a ---high_street--------- e -----lovers_lane------- j --
        |                         |                         |
        |                         |                         |  
 albion_street(1)         oxford_road(1)             acacia_avenue(1)
        |                         |                         |
      \ |                         |                         |                     
        b -pigeon_lane(1)--\      |                         |
        |                   \     |                         |  
  albion_street(2)           \    |                         /
        |                     \-- f --pigeon_lane(2) --\   /
        |                         |                     \ /
  ----- c----blue_street(1)------ g --blue_street(2)---- i ---
        |                       / |                     /
  mill_road                    /  |   /--acacia_av(2)--/     
        |                     /   |  /
        |  /---boars_hill----/    | /
        | /                       h
  ----- d -----north_lane--------/
        |
     
*/
/*
.pa
*/

/*  Unambiguous Prolog definition of the map above  */


on( a, high_street ).       on( a, albion_street(1) ).

on( b, albion_street(1) ).  on( b, albion_street(2) ).
on( b, pigeon_lane(1) ).    

on( c, albion_street(2) ).  on( c, blue_street(1) ).
on( c, mill_road ).

on( d, mill_road ).         on( d, north_lane ).     
on( d, boars_hill ).

on( e, high_street ).       on( e, oxford_road(1) ). 
on( e, lovers_lane ).

on( f, oxford_road(1) ).    on( f, oxford_road(2) ). 
on( f, pigeon_lane(1) ).    on( f, pigeon_lane(2) ).

on( g, blue_street(1) ).    on( g, blue_street(2) ). 
on( g, oxford_road(2) ).    on( g, oxford_road(3) ).    
on( g, boars_hill ).

on( h, oxford_road(3) ).    on( h, north_lane ).     
on( h, acacia_avenue(2) ).

on( i, pigeon_lane(2) ).    on( i, blue_street(2) ). 
on( i, acacia_avenue(1) ).  on( i, acacia_avenue(2) ).

on( j, acacia_avenue(1) ).  on( j, lovers_lane ).

/*
.pa
*/

/*  This program is designed with two entry points:- */
/*  The 'route' clause which instantiates P to a     */
/*  list of intermediate junctions.                  */
/*  The 'directions' clause which uses route but     */
/*  prints the resulting solution in a more readable */
/*  form.                                            */

route( A,B,P ):- route1( A,B, [A], P ).      

/*
     route1 has an extra argument to those in route.
     This is used to build up the list of all points encountered
     so far in reaching the (current) starting point.

     Notice the use of '-' to separate the road and junction
     names. It is used merely as a convenient infix operator
     which has been pre-defined. It is very useful when we want two
     terms to be linked together and treated as a single entity.
     We could just as easily have used '+','*' or '/'.
*/

route1( A,A, _, [A-end] ) :- !.        /* boundary condition */
       
route1( A,B, SoFar, [A-R | P] ):-              
       on( A,R ),                  /* find a junction C which is */       
       on( C,R ),                  /* linked to A by some road R */         

       not  member(  C,SoFar ),    /* ensure C is not in list of */
                                   /* previously-met junctions   */

       route1( C,B, [C|SoFar], P ). /* C now becomes new starting */
                                    /* point and is added to the  */
                                    /* list of points met so far */

  /* member is a utility predicate used by route */

member( X, [X|_] ).
member( X, [_|Y] ):- member(X,Y).

/*
.pa
*/

  /* Directions is the other entry point */


directions( A,B ):-
     route( A,B,P ),
     nl,
     write('Start at '),
     list_directions(P).

list_directions( [J-end] ):-     /* boundary condition */
     write('junction '''),
     write(J),
     write(''' which is the destination.'),
     nl, !.
list_directions([H|T]):-         /* process each element */
     list_direction(H),
     list_directions(T).

list_direction( J-R ):-          /* print each element */
     write('junction '''),
     write(J),
     write(''' and travel along '''),
     write(R),
     write(''' to get to '),
     nl.






