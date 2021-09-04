with TEXT_IO;
with HEX_NUM;
procedure MAIN is
H1,
H2:HEX_NUM.HEX_POINT;
function "<" (LEFT,RIGHT:HEX_NUM.HEX_POINT) return BOOLEAN is
begin
return (HEX_NUM.GET_DEC(LEFT)<HEX_NUM.GET_DEC(RIGHT));
end "<";
begin
H1:=new HEX_NUM.HEX;
H2:=new HEX_NUM.HEX;
TEXT_IO.NEW_LINE;
TEXT_IO.PUT("Enter a first hexadecimal number:");
if HEX_NUM.GET_HEX(H1) 
   then 
   TEXT_IO.NEW_LINE;
   TEXT_IO.PUT("Enter a second hexadecimal number:");
   if HEX_NUM.GET_HEX(H2) 
           then TEXT_IO.NEW_LINE;
                if H1<H2 
                   then HEX_NUM.SHOW_HEX(H1);
                        TEXT_IO.PUT(" < ");
                        HEX_NUM.SHOW_HEX(H2);
                   else HEX_NUM.SHOW_HEX(H2);
                        TEXT_IO.PUT(" < ");  
                        HEX_NUM.SHOW_HEX(H1);
                 end if;                           
           end if;
end if;

end MAIN;
