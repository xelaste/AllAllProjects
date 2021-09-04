package HEX_NUM is
        type HEX_DIGITS is private;  
        type HEX is private;
        type HEX_POINT is access HEX;
        DEC_VALUE:integer:=0;
        function GET_HEX (H:access HEX) return BOOLEAN;
        procedure SHOW_HEX (H:HEX_POINT);
        function GET_DEC (H:access HEX) return INTEGER;
        private
        SIZE:constant:=4;
        type HEX_DIGITS is ('0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'); 
        type Harray is array (1..SIZE) of HEX_DIGITS;
        type HEX is record
                    HEX_VALUE: Harray:=(others=>'0');
                    DEC_VALUE:integer:=0;
        end record;
end HEX_NUM;        
