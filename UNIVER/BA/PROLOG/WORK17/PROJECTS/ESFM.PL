/*  ESFM.PL
    Shelved on the 15th of March 1988.
*/


go :-
    clear_kb,
    give_advice.


give_advice :-
    recommendation(X),
    fail.

give_advice :-
    write_advice.


/* The rules -
These are implemented this way to mimic the MicroExpert rule set.
Looking at them side by side should show the similarities. */


fact(branch8,yes) :-
    fact('stocking good',yes),
    fact('avg < 5',yes),
    fact('2000+ per acre',yes),
    recommend('The stand of jack pine must be weeded and cleaned.').

fact(branch8,yes) :-
    fact('stocking good',yes),
    fact('avg < 5',yes),
    fact('2000+ per acre',no).

fact(branch9,no) :-
    fact('stocking good',yes),
    fact('avg < 5',no),
    fact(age,mature),
    assertz(fact(branch11,yes)).

fact(branch11,yes) :-
    fact('stocking good',yes),
    fact('avg < 5',no),
    fact(age,mature),
    assertz(fact(branch9,no)).

fact(branch9,yes) :-
    fact('stocking good',yes),
    fact('avg < 5',no),
    fact(age,immature),
    fact('site index > 60',yes),
    fact('product size',large),
    fact('120+ basal area',yes),
    recommend('It is important to thin the area').

fact(branch9,yes) :-
    fact('stocking good',yes),
    fact('avg < 5',no),
    fact(age,immature),
    fact('site index > 60',yes),
    fact('product size',large),
    fact('120+ basal area',no).

fact(branch9,yes) :-
    fact('stocking good',yes),
    fact('avg < 5',no),
    fact(age,immature),
    fact('site index > 60',yes),
    fact('product size',large).

fact(branch9,yes) :-
    fact('stocking good',yes),
    fact('avg < 5',no),
    fact(age,immature),
    fact('site index > 60',yes).

fact(branch11,yes) :-
    fact('stocking good',no),
    fact('other resources',no).

fact(branch9,yes) :-
    fact(branch8,yes),
    fact('severe competition',yes),
    recommend('Competing trees should be eliminated.').

fact(branch9,yes) :-
    fact(branch8,yes),
    fact('severe competition',no).

fact(branch17,yes) :-
    fact(branch11,yes),
    fact('pine desired',yes),
    fact('pine suited',yes),
    fact('desirable seed',yes),
    fact('serotinous cones',yes),
    fact('10/acres adequate',yes),
    fact('burning planned',no),
    add_fact(silvaculture,clearcut),
    recommend('The best silvaculture method to use is clearcut.').

fact(branch17,yes) :-
    fact(branch11,yes),
    fact('pine desired',yes),
    fact('pine suited',yes),
    fact('desirable seed',yes),
    fact('serotinous cones',yes),
    fact('10/acres adequate',no),
    add_fact(silvaculture,clearcut),
    recommend('The best silvaculture method to use is clearcut.').

fact(branch17,yes) :-
    fact(branch11,yes),
    fact('pine desired',yes),
    fact('pine suited',yes),
    fact('desirable seed',yes),
    fact('serotinous cones',no),
    fact('two harvests wanted',yes),
    fact('two harvests possible',yes),
    add_fact(silvaculture,shelterwood),
    recommend('The best silvaculture method to use is the shlterwood method.').

fact(branch17,yes) :-
    fact(branch11,yes),
    fact('pine desired',yes),
    fact('pine suited',yes),
    fact('desirable seed',yes),
    fact('serotinous cones',no),
    fact('two harvests wanted',yes),
    fact('two harvests possible',no),
    add_fact(silvaculture,clearcut),
    recommend('The best silvaculture method to use is clearcut.').

fact(branch17,yes) :-
    fact(branch11,yes),
    fact('pine desired',yes),
    fact('pine suited',yes),
    fact('desirable seed',yes),
    fact('serotinous cones',no),
    fact('two harvests wanted',no),
    add_fact(silvaculture,clearcut),
    recommend('The best silvaculture method to use is clearcut.').

fact(branch17,yes) :-
    fact(branch11,yes),
    fact('pine desired',yes),
    fact('pine suited',yes),
    fact('desirable seed',no),
    add_fact(silvaculture,clearcut),
    recommend('The best silvaculture method to use is clearcut.').

fact(branch18,yes) :-
    fact(branch17,yes),
    fact('adequate seedbed',yes).

fact(branch18,yes) :-
    fact(branch17,yes),
    fact('adequate seedbed',no),
    recommend('The site should be prepared before planting.').

fact(X,Y) :-
    kb(X,Y),! .

fact(X,Y) :-
    not(kb(X,Anything)),
    question(X,Answer),
    assertz(kb(X,Answer)),
    Y = Answer.


recommendation(maintain) :-
    fact('stocking good',no),
    fact('other resources',yes),
    recommend('You should maintain the stand in its present condition').

recommendation(control) :-
    fact(branch9,yes),
    fact('high risk',yes),
    recommend('The current area should be controlled, if at all feasible.').

recommendation(wait) :-
    fact(branch9,yes),
    fact('high risk',no),
    recommend('You should wait before doing anything else to this stand.').

recommendation('use seed tree') :-
    fact(branch11,yes),
    fact('pine desired',yes),
    fact('pine suited',yes),
    fact('desirable seed',yes),
    fact('serotinous cones',yes),
    fact('10/acres adequate',yes),
    fact('burning planned',yes),
    recommend('You should use seed trees to seed the area.').

recommendation(convert) :-
    fact(branch11,yes),
    fact('pine desired',yes),
    fact('pine suited',no),
    recommend('You should convert the area to some more desirable kind of tree.').

recommendation(convert) :-
    fact(branch11,yes),
    fact('pine desired',no),
    recommend('You should convert the area to some more desirable kind of tree.').

recommendation('natural seeding') :-
    fact(branch18,yes),
    fact(silvaculture,shelterwood),
    recommend('The natural seeding technique should be used.').

recommendation(plant) :-
    fact(branch18,yes),
    fact(silvaculture,clearcut),
    fact('improved stock',yes),
    recommend('Since there is better stock available, you can plant using that stock.').

recommendation('scatter cones') :-
    fact(branch18,yes),
    fact(silvaculture,clearcut),
    fact('improved stock',no),
    fact('good cone supply',yes),
    recommend('You should scatter the serotinous cones over the area.').

recommendation('direct seed') :-
    fact(branch18,yes),
    fact(silvaculture,clearcut),
    fact('improved stock',no),
    fact('good cone supply',no),
    recommend('You should directly seed the area.').


/*  Add fact to KB if not already there.  */                     

add_fact(X,Y) :-
    kb(X,Y),!.

add_fact(X,Y) :-
    assertz(kb(X,Y)).


recommend(X) :-
    add_fact(advice,X).


/* Questions to ask the user */

question('stocking good',Ans) :-
    write('Is the stocking of the jack pine stand currently'),nl,
    write('at least minimum ? '),nl,nl,
    write('If you are unsure of how to determine stocking,'),nl,
    write('see page 4 in the Managers Handbook for Jack Pine'),
    nl,
    ask('',Ans,[ yes , no ]).

question('avg < 5',Ans) :-
    ask('Is the average diameter of the trees less than 5 inches ?',
        Ans,[yes,no]).

question('2000+ per acre',Ans) :-
    ask('Are there 2000 or more trees per acre ?',Ans,[yes,no]).

question(age,Ans) :-
    ask('Is the age of the stand mature or immature ?',
        Ans,[mature,immature]).

question('site index > 60',Ans) :-
    ask('Is the site index greater than 60 ?',Ans,[yes,no]).

question('product size',Ans) :-
    ask('Do you want to manage the timber for large or small products ?',
        Ans,[large,small]).

question('120+ basal area',Ans) :-
    ask('Is the basal area per acre at least 120 square feet ?',
        Ans,[yes,no]).

question('other resources',Ans) :-
    ask('Do you want to maintain this condition to support other resources?',
        Ans,[yes,no]).

question('severe competition',Ans) :-
    ask('Is there severe overstory competition ?',Ans,[yes,no]).

question('high risk',Ans) :-
    ask('Is there a high risk of loss or injury ?',Ans,[yes,no]).

question('pine desired',Ans) :-
    ask('Do you want to keep jack pine in this area ?',Ans,[yes,no]).

question('pine suited',Ans) :-
    ask('Is jack pine well suited to this site ?',Ans,[yes,no]).

question('desirable seed',Ans) :-
    ask('Is there a desirable jack pine seed source on the area ?',
        Ans,[yes,no]).

question('serotinous cones',Ans) :-
    ask('Do the trees on the site have serotinous cones ?',Ans,[yes,no]).

question('10/acres adequate',Ans) :-
    ask('Are 10 trees per acre adequate to seed the area ?',Ans,[yes,no]).

question('burning planned',Ans) :-
    ask('Has a prescribed burning been planned ?',Ans,[yes,no]).

question('two harvests wanted',Ans) :-
    ask('Do you want two commercial harvests on this area ?',Ans,[yes,no]).

question('two harvests possible',Ans) :-
    ask('Is it possible to get two harvests from this area ?',Ans,[yes,no]).

question('adequate seedbed',Ans) :-
    ask('Is there an adequate seedbed for planting ?',Ans,[yes,no]).

question('improved stock',Ans) :-
    ask('Is there an improved planting stock available ?',Ans,[yes,no]).

question('good cone supply',Ans) :-
    ask('Is there a good supply of serotinous cones in the area ?',
        Ans,[yes,no]).


/* Utility Routines - to be useful, we should add some routines to allow
                       the user to ask 'How' and 'Why' */

display_kb :-
    kb(X,Y),
    write(X),write(' is '),write(Y),
    nl,
    fail.

display_kb.


write_advice :-
    nl,nl,
    write('Based upon your responses, the following is recommended :'),nl,nl,
    show_advice.


show_advice :-
    kb(advice,X),
    write(X),
    nl,
    fail.

show_advice :-
    nl,write('To see the complete set of derived facts, '),
    write('type "display_kb."'), nl.


clear_kb:-
    retractall(kb(_,_)).


member(X,[X|_]).
member(X,[_|Y]) :-
    member(X,Y).


ask(Ques,Ans,LegalResponses) :-
    nl, write(Ques),
    read(Ans),
    member(Ans,LegalResponses),!.

ask(Ques,Ans,LegalResponses) :-
    nl, nl,
    write('Please respond with : '),
    write(LegalResponses), nl, nl,
    ask(Ques,Ans,LegalResponses).
