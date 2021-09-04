--*************************************************************
generic
-- A:=(Sigma,Q,Q0,F,Delta) definition of automat;
type STATE is (<>);                 -- The station of automata: Q
START_STATE: in STATE:=STATE'FIRST; -- Q0
type GETTING_STATE is (<>);         -- The list of getting states: F 
type ABC is   (<>);                 -- ABC of the automata
package AUTOMAT_PRODUCER is
THE_NEXT_STATE:array (STATE,ABC) of STATE;
procedure SET_START_STATE;
procedure RECIEVE_SYMBOL(C:ABC);
function IS_PRESENT_STATE_GETTING return BOOLEAN;
WORD_DOES_NOT_BELONG_TO_AUTOMAT_LANGUAGE: exception;
private
PRESENT_STATE :STATE;
end AUTOMAT_PRODUCER;