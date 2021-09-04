--***********************************************************
package body AUTOMAT_PRODUCER  is
----------------------------------------------------
procedure SET_START_STATE is
begin
PRESENT_STATE:=START_STATE;
end SET_START_STATE;
----------------------------------------------------
procedure RECIEVE_SYMBOL(C:ABC) is
begin
PRESENT_STATE:=THE_NEXT_STATE(PRESENT_STATE,C);
end RECIEVE_SYMBOL;
--------------------------------------------------------------
function IS_PRESENT_STATE_GETTING return BOOLEAN is
HELP:GETTING_STATE;
begin
HELP:=GETTING_STATE'VALUE(STATE'IMAGE(PRESENT_STATE));--cast from state to 
                                                     --getting state     
return true;                                         --if was succseful 
exception
 when CONSTRAINT_ERROR => return FALSE;  --present_state is not getting
end IS_PRESENT_STATE_GETTING;                         
end AUTOMAT_PRODUCER;