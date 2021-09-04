--=======================================================================
with TEXT_IO;
with AUTOMAT_PRODUCER;
procedure CHECK_AUTOMATA is
type SYMBOL is (a,b);
type THE_STATE is (Q0,Q1,Q2,Q3);
type THE_GETTING_STATE is (Q2);
package THE_AUTOMATA is new AUTOMAT_PRODUCER(STATE=>THE_STATE,
                                             START_STATE=>Q0,
                                             GETTING_STATE=>THE_GETTING_STATE,
                                             ABC=>SYMBOL);
----------------------------------------------------------------------------                                               
function CHECK_WORD (THE_WORD:STRING) return BOOLEAN is
THE_SYMBOL:STRING(1..1);
begin
THE_AUTOMATA.SET_START_STATE; -- set automat at start
for I in THE_WORD'RANGE loop  -- reading the word
    THE_SYMBOL(1):=THE_WORD(I);
    THE_AUTOMATA.RECIEVE_SYMBOL(SYMBOL'VALUE(THE_SYMBOL)); 
end loop;
return THE_AUTOMATA.IS_PRESENT_STATE_GETTING;
exception
   when CONSTRAINT_ERROR => TEXT_IO.NEW_LINE;
                            TEXT_IO.PUT(THE_SYMBOL&"  invalid symbol");
                            return false;
end CHECK_WORD;
---------------------------------------------------------------------------
procedure WORD_RECIEVED (THE_WORD:STRING) is
begin
TEXT_IO.NEW_LINE;
TEXT_IO.PUT(THE_WORD&" have been recieved");
end WORD_RECIEVED;
---------------------------------------------------------------------------
procedure WORD_IS_NOT_RECIEVED (THE_WORD:STRING) is
begin
TEXT_IO.NEW_LINE;
TEXT_IO.PUT(THE_WORD&" have been not recieved");
end WORD_IS_NOT_RECIEVED;
--==========================================================================
begin
THE_AUTOMATA.THE_NEXT_STATE:=(Q0=>(Q1,Q2),Q1=>(Q0,Q1),
                              Q2=>(Q2,Q3),Q3=>(Q3,Q2)); 

if CHECK_WORD("ab") then WORD_RECIEVED("ab");
                   else WORD_IS_NOT_RECIEVED("ab");
end if;                    
if CHECK_WORD("b") then WORD_RECIEVED("b");
                   else WORD_IS_NOT_RECIEVED("b");
end if;                    

if CHECK_WORD("aababbab") then WORD_RECIEVED("aababbab");
                          else WORD_IS_NOT_RECIEVED("aababbab");
end if;                    

if CHECK_WORD("aababbaa") then WORD_RECIEVED("aababbaa");
                          else WORD_IS_NOT_RECIEVED("aababbaa");
end if;                    

if CHECK_WORD("aabca") then WORD_RECIEVED("aabca");
                       else WORD_IS_NOT_RECIEVED("aabca");
end if;                    
end CHECK_AUTOMATA;
--***************************************************************