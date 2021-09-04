{**********************************************************************}
{ 5.5 …˜…ˆ -  š‹ ˆ—‰…˜”„ }
program proyekt(life);
{ 120 - š …‰‘ ‰˜’‰ š‰˜…… …˜…ƒ ‰˜…€ ‰"’ š‹ - LIFE Œ—‘” …‰‘ ˆ—‰…˜”}
uses crt;

const
     godel_tavla = 13;
type
    tavla = array [0..godel_tavla,0..godel_tavla] of integer;
var
   tavla_life,tavla_mishni : tavla;
   zman,i,j                : integer;
   prisa,boded,chenek      : integer;
   kovetz                  : file of tavla;
   resh                    : tavla;
   funckey                 : boolean;
   f                       : file of tavla;
{======================================================================}

procedure pticha; { š‰‹…š„ š‚–„ }

var
   makash : char;
{*************************************}

begin                                  {*1.1*}
     clrscr;
     textcolor(1);
     gotoxy (10,3);
     write
         ('             .š…‰…˜š Œ™ „—‰‰ƒŒ ™‡ š‰–Œ…‰‘ €…„ "LIFE"');
     gotoxy (10,4);
     write
         ('‰˜…†€Œ ˆ™”š„Œ ‹"‡€… ‰…‘ ˜…†€ ‡š”š„Œ „Œ…‹‰ š‰…‘ š…˜š');
     gotoxy (10,5);
     write
         ('     .Œ‰Œ‹ Œ’‰„Œ …€ —ˆ–‰„Œ „Œ…‹‰ š…‰…‘ š…‰‘… ‰”‘…');
     gotoxy (10,6);
     write
         (' š€ „€˜š… ‰™…‰„ ‰˜…†€„ Œ™ " š…™‰š„ š” " ‚‰–š š‰‹…š„');
     gotoxy (10,7);
     write
         ('  .™‰—‰ ™š™„™ ‰—…‡„ ‰”Œ „” …Œ…‡‰™ ‰…‰™„… š…‰…‡š”š„„');
     gotoxy (10,13);
     write
         ('.‰˜’‰ š‰˜…… …˜…ƒ ‰˜…€ ‰"’ „š‹‰ …† š‰‹…š              ');
     gotoxy (12,14);
     write ('Š™„Œ <ÄÙ ™—„');
     gotoxy (10,14);
     read (makash);
end;                                   {*1.1*}
{======================================================================}

procedure asama(var i,p,b,c : integer);

begin                                  {*1.2*}
     i := 1;
     p := 3;
     b := 2;
     c := 4;
end;                                   {*1.2*}
{======================================================================}

procedure tafrit(var natun_chazara : integer); {   ˆ‰˜”š Š‘   }

var
   peula          : integer;
   x              : char;
   i,j,natun,sium : integer;
{*************************************}

begin                                  {*1.3*}
     clrscr;
     textcolor(2);
     gotoxy (10,5);
     write
       ('ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»');
     gotoxy (10,6);
     write
       ('º Û     Û  Ûßßß  Ûßßßß               š…™… š‘‹„ .1       º');
     gotoxy (10,7);
     write
       ('º Û     Û  Ûßßß  ÛÛÛÛÛ  "LIFE"Œ „Œ…’” ‰…š š‘‹„ .2       º');
     gotoxy (10,8);
     write
       ('º ÛÛÛÛ  Û  Û     ÛÜÜÜÜ       …˜‡€ …š ‰”Œ —‡™‰ .3       º');
     gotoxy (10,9);
     write
       ('º                         •…— ‰‰—„ …š ™…‰™ .4       º');
     gotoxy (10,10);
     write
       ('º                          •…— …˜‡€ …š š˜‰™ .5       º');
     gotoxy (10,11);
     write
       ('º                                            …‰‘ .6       º');
     gotoxy (10,12);
     write
       ('º                                                          º');
     gotoxy (10,13);
     write
       ('º                                             : Šš…‰‡…Œ   º');
     gotoxy (10,14);
     write
       ('º** „‰…–˜„ „Œ…’” <ÄÄÙ ™—„… „Œ…’” ‚…‘ š˜‰‡Œ ‰–‡ ™š™„ **º');
     gotoxy (10,15);
     write
       ('ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ½');

     i := 6;
     sium := 0;
     natun := 2;
     gotoxy (63,i);
     write ('<====');

     repeat
           begin
                x := readkey;
                if x <> #0 then
 {<ÄÄÙ Œ’ „™—„}    if x = #13 then
                      begin
                           sium := 1;
                           funckey := true;
                      end
                   else
                       funckey := false
                else
                    begin
                         x := readkey;
                         case x of
 { „Œ’Œ •‡ }                 #72 : if natun -1 > 1 then
                                       begin
                                            i := i-1;
                                            natun := natun - 1;
                                            gotoxy (63,i+1);
                                            write ('     ');
                                            gotoxy (63,i);
                                            write ('<====');
                                       end
                                    else
                                        begin
                                             if natun - 1 = 1 then
                                                begin
 { ‰–‰‡„ Œ…‚Œ‚ }                                    i := 11;
                                                     natun := 7;
                                                     gotoxy (63,6);
                                                     write ('     ');
                                                     gotoxy (63,11);
                                                     write ('<====');
                                                end
                                    end;

 { „ˆŒ •‡ }                  #80 : if natun +1 < 8 then
                                       begin
                                            i := i +1;
                                            natun := natun + 1;
                                            gotoxy (63,i-1);
                                            write ('     ');
                                            gotoxy (63,i);
                                            write ('<====');
                                       end
                                    else
                                        begin
                                             if natun +1 = 8 then
                                                begin
 { ‰–‰‡„ Œ…‚Œ‚ }                                    i := 6;
                                                     natun := 2;
                                                     gotoxy (63,11);
                                                     write ('     ');
                                                     gotoxy (63,6);
                                                     write ('<====');
                                                end
                                        end;

                         end;
                    end;
           end;
     until sium = 1;
     natun_chazara := natun;
end;                                   {*1.3*}
{======================================================================}

procedure ipus_tavla (var tavla_ipus:tavla);{š…€Œˆ ‘…”‰€}

var
   i,j : integer;
{*************************************}

begin                                  {*1.4.1*}
     for i := 0 to godel_tavla do
         for j := 0 to godel_tavla do
             tavla_ipus [i,j] := 0;
end;                                   {*1.4.1*}
{======================================================================}

procedure mapa;    {š…™‰š„ š” ˜…‰– }
{*************************************}

begin                                  {*1.4.2*}  {*1.6.1.1*}
     gotoxy (1,1);
     write ('ÉÍÍËÍÍËÍÍËÍÍËÍÍËÍÍËÍÍËÍÍËÍÍËÍÍËÍÍËÍÍ»');
     i := 0;
     j := 1;

     repeat
           i := i + 2;
           j := j + 2;
           gotoxy (1,i);
           write ('º  º  º  º  º  º  º  º  º  º  º  º  º');
           gotoxy (1,j);
           write ('ÌÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍ¹');
     until i = 24;

     gotoxy (1,25);
     write ('ÈÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍ¼');
end;                                   {*1.4.2*}  {*1.6.1.1*}
{======================================================================}

procedure atzavat_yeshuvim(var  natun_chazara : integer);
                                                { „ŒˆŒ ‰…™‰ š‘‹„ }

var
   amuda,i,j                 : integer;
   x                         : char;
   tur,shura,i_tavla,j_tavla : integer;
{*************************************}

begin                                  {*1.4*}
     clrscr;
     textcolor(3);
     for amuda := 1 to 25 do
         begin
              gotoxy (53,amuda);
              write ('º');
         end;
     gotoxy (57,2);
     write ('     ‘‰‹ „š€ „† Š‘');
     gotoxy (57,3);
     write ('   ™š™„ Š‹ ™Œ ‰…™‰');
     gotoxy (57,4);
     write ('         : Œ"„ ‰™—');
     gotoxy (57,5);
     write (' .…‰‹ Œ‹Œ „†…†šŒ ‰–‡');
     gotoxy (57,6);
     write ('      .…™‰ š–„Œ <ÄÄÙ');
     gotoxy (57,7);
     write ('      .„–„ …‰‘Œ  Esc');
     gotoxy (55,9);
     write ('   :„  —‡™‰Œ ‰…š„');
     gotoxy (54,11);
     write ('‰‹™    -  .„™…„ š…™˜”š„');
     gotoxy (54,12);
     write ('‰‹™    -.š…ƒ‰ƒ —’ „™‰ˆ');
     gotoxy (54,13);
     write ('‰‹™    -   .—‡ —’ „™‰ˆ');
     gotoxy (60,11);
     write (prisa);
     gotoxy (60,12);
     write (boded);
     gotoxy (60,13);
     write (chenek);
     ipus_tavla (tavla_life);          {*1.4.1*}
     ipus_tavla (tavla_mishni);        {*1.4.2*}
     mapa;
     gotoxy (2,2);
     i_tavla := 1;
     j_tavla := 1;
     tur := 1;
     shura := 1;
     i := 2;
     j := 2;
     textcolor(1);
     gotoxy (j,i);
     write ('ÛÛ');

     repeat
           begin
                x := readkey;
                if x <> #0 then
 {<ÄÄÙ Œ’ „™—„}    if x = #13 then
                      begin
                           if tavla_life [i_tavla,j_tavla] = 1 then
                              begin
                                   gotoxy (j,i);
                                   write ('  ');
                                   tavla_life[i_tavla,j_tavla] := 0;
                                   tavla_mishni[i_tavla,j_tavla] := 0;
                              end
                           else
                               begin
                                    gotoxy (j,i);
                                    write ('XX');
                                    tavla_life[i_tavla,j_tavla] := 1;
                                    tavla_mishni [i_tavla,j_tavla] := 1;
                               end;
                           if j_tavla + 1 < godel_tavla + 1 then
                              begin
                                   tur := tur + 1;
                                   j_tavla := j_tavla + 1;
                                   if (tavla_mishni [shura,tur] = 0) and
                                         (tur < godel_tavla) then
                                      begin
                                           gotoxy (j+3,i);
                                           write ('ÛÛ');
                                      end;
                              end;
                           j := j + 3;
                           if j > godel_tavla * 3 - 3 then
                              begin
                                   tur := tur - 1;
                                   j := j - 3;
                                   j_tavla := j_tavla - 1;
                              end;
                           funckey := true;
                      end
                   else
                       funckey := false
                else
                    begin
                         x := readkey;
                         case x of
 { „Œ’Œ •‡ }                 #72 : if i-2 > 0 then
                                       begin
                                            if tavla_mishni [shura,tur] = 0
                                                    then
                                               begin
                                                    gotoxy (j,i);
                                                    write ('  ');
                                                    end;
                                            if tavla_mishni [shura-1,tur] = 0
                                                    then
                                               begin
                                                    gotoxy (j,i-2);
                                                    write ('ÛÛ');
                                               end;
                                            shura := shura - 1;
                                            i := i-2;
                                            i_tavla := i_tavla - 1;
                                            gotoxy (j,i);
                                       end;
 { „ˆŒ •‡ }                  #80 : if i+2 < godel_tavla * 2  then
                                       begin
                                            if tavla_mishni [shura,tur] = 0
                                                    then
                                               begin
                                                    gotoxy (j,i);
                                                    write ('  ');
                                               end;
                                            if tavla_mishni [shura+1,tur] = 0
                                                    then
                                               begin
                                                    gotoxy (j,i+2);
                                                    write ('ÛÛ');
                                               end;
                                            shura := shura + 1;
                                            i := i + 2;
                                            i_tavla := i_tavla + 1;
                                            gotoxy (j,i);
                                       end;
 { „‰‰ •‡ }                 #77 : if j+3 < godel_tavla * 3 - 3 then
                                       begin
                                            if tavla_mishni [shura,tur] = 0
                                                    then
                                               begin
                                                    gotoxy (j,i);
                                                    write ('  ');
                                               end;
                                            if tavla_mishni [shura,tur+1] = 0
                                                    then
                                               begin
                                                    gotoxy (j+3,i);
                                                    write ('ÛÛ');
                                               end;
                                            tur := tur + 1;
                                            j := j + 3;
                                            j_tavla := j_tavla + 1;
                                            gotoxy (j,i);
                                       end;
 { „Œ€™ •‡ }                 #75 : if j-3 > 0 then
                                       begin
                                            if tavla_mishni [shura,tur] = 0
                                                    then
                                               begin
                                                    gotoxy (j,i);
                                                    write ('  ');
                                               end;
                                            if tavla_mishni [shura,tur-1] = 0
                                                    then
                                               begin
                                                    gotoxy (j-3,i);
                                                    write ('ÛÛ');
                                               end;
                                            tur := tur - 1;
                                            j := j-3;
                                            j_tavla := j_tavla - 1;
                                            gotoxy (j,i);
                                       end;
                         end;
                    end;
           end
     until x = #27;

     natun_chazara := 1;
end;                                   {*1.4*}
{======================================================================}

procedure netunim (var natun_chazara:integer); {     —‡™‰  ‰…š }

{*************************************}

begin                                  {*1.5*}
     clrscr;
     textcolor(5);
     gotoxy (10,8);
     write
    ('         š…‘…”š š…–™‰      š…‡”Œ ™‰ ˜™€‹ …‘”š‰ š…‰…” š…–™‰');
     gotoxy (35,8);
     read (prisa);
     gotoxy (10,10);
     write
    ('š…‘…”š š…‹™ š…–™‰ š…‡” …€      „Œ ™‰ ˜™€‹ ™ˆ‰š „‘…”š š–™‰');
     gotoxy (40,10);
     read (boded);
     gotoxy (10,12);
     write
    ('     š…‘…”š š…‹™ š…–™ ˜š…‰ …€     „Œ ™‰ € ™ˆ‰š „‘…”š š–™');
     gotoxy (43,12);
     read (chenek);
     natun_chazara := 1;
end;                                   {*1.5*}
{======================================================================}

procedure miluy_tavla; { ‰…š LIFE „Œˆ ‰…Œ‰ }

var
   i,j : integer;

{*************************************}

begin                                  {*1.6.2.1*}
     for i := 1 to godel_tavla - 1 do
         for j := 1 to godel_tavla - 1 do
             tavla_life [i,j] := tavla_mishni [i,j];
end;                                   {*1.6.2.1*}
{======================================================================}

procedure misgeret;  {  š…™‰š„ š˜‚‘‰  }

var
   i,j,amuda,shura : integer;
   xx              : char;

{*************************************}

begin                                  {*1.6.1*}
     for amuda := 1 to 25 do
         begin
              gotoxy (53,amuda);
              write ('º');
         end;
     shura := 0;
     gotoxy (53,26);
     write ('Esc ™—„ …‰‘Œ');
     mapa;                             {*1.6.1.1*}
     gotoxy (60,2);
     write ('Š‘ š‰’™„ † Š™ ™—„');
     gotoxy (60,4);
     write ('     <ÄÙ -… 10 ƒ’ 1 ');
     gotoxy (55,9);
     write ('   :„  —‡™‰Œ ‰…š„');
     gotoxy (54,11);
     write ('‰‹™    -  .„™…„ š…™˜”š„');
     gotoxy (54,12);
     write ('‰‹™    -.š…ƒ‰ƒ —’ „™‰ˆ');
     gotoxy (54,13);
     write ('‰‹™    -   .—‡ —’ „™‰ˆ');
     gotoxy (60,11);
     write (prisa);
     gotoxy (60,12);
     write (boded);
     gotoxy (60,13);
     write (chenek);
     zman := 1;
     gotoxy (60,4);
     read (zman);
end;                                   {*1.6.1*}
{======================================================================}

procedure atzagat_tavla;  { (LIFE-„ š–‰˜) Š‘„ Œ’ ‰…š š‚–„ }

var
   a,i,j,amuda,shura : integer;

{*************************************}

begin                                  {*1.6.2*}
     miluy_tavla;                      {*1.6.2.1*}
     shura := 0;
     i := 0;
     repeat
           i := i + 1;
           amuda := 2;
           shura := shura + 2;
           for j := 1 to godel_tavla - 1  do
               begin
                    gotoxy (amuda,shura);
                    if tavla_life [i,j] = 1 then
                       write ('XX');
                    if tavla_life [i,j] = 0 then
                       write ('  ');
                    amuda := amuda + 3;
               end;
     until i = godel_tavla - 1;
end;                                   {*1.6.2*}
{======================================================================}

procedure bdika;   { „–„… š…™‰š„ š—‰ƒ }

var
   mone,i,j,sium :integer;

{*************************************}

begin                                  {*1.6.3*}
     for i := 1 to godel_tavla - 1 do
         for j := 1 to godel_tavla - 1 do
             begin
                   mone := 0;
                   if tavla_life [i-1,j-1] = 1 then
                      mone := mone + 1;
                   if tavla_life [i-1,j] = 1 then
                      mone := mone + 1;
                   if tavla_life [i-1,j+1] = 1 then
                      mone := mone + 1;
                   if tavla_life [i,j-1] = 1 then
                      mone := mone + 1;
                   if tavla_life [i,j] = 1 then
                      mone := mone + 1;
                   if tavla_life [i,j+1] = 1 then
                      mone := mone + 1;
                   if tavla_life [i+1,j-1] = 1 then
                      mone := mone + 1;
                   if tavla_life [i+1,j] = 1 then
                      mone := mone + 1;
                   if tavla_life [i+1,j+1] = 1 then
                      mone := mone + 1;

                   case tavla_life [i,j] of
                        0 : begin
                                 tavla_mishni [i,j] := 0;
                                 if prisa-1 < mone then
                                    tavla_mishni [i,j] := 1;
                            end;

                        1 : begin
                                 tavla_mishni [i,j] := 1;
                                 if (boded > mone) or (chenek < mone )
                                                                    then
                                    tavla_mishni [i,j] := 0;
                                 if mone = 0 then
                                    tavla_mishni [i,j] := 0;
                            end;
                   end;
             end;
end;                                   {*1.6.3*}
{======================================================================}

procedure mischak (var natun_chazara:integer); {     —‡™‰    }

var
   mone,i,j,sium : integer;
   xx            : char;

{*************************************}

begin                                  {*1.6*}
     sium := 0;
     clrscr;
     textcolor(9);
     misgeret;                         {*1.6.1*}
     xx := #13;
     textcolor(3);
     repeat
           begin
                atzagat_tavla;         {*1.6.2*}
                bdika;                 {*1.6.3*}
                delay (zman * 1000);
                if KeyPressed then
                   begin
                        xx := readkey;
                        if xx <> #0 then
                           if xx = #27 then
                              funckey := true
                           else
                               funckey := false
                        else
                            xx := readkey;
                   end;
           end
     until xx = #27;
     natun_chazara := 1;
end;                                   {*1.6*}
{======================================================================}

procedure kria(var natun_chazara: integer);{•…—„ ‰…š„ Œ™ „€‰˜—}

{*************************************}

begin                                  {*1.7*}
   {$I-}
     assign (kovetz,'life.dat');
     reset (kovetz);  { „€‰˜—Œ •…—„ š‡‰š” }
     if ioresult = 0 then
        begin
             read  (kovetz,resh);
             if ioresult = 0 then
                begin
                     prisa := resh [1,1];
                     boded := resh [2,1];
                     chenek := resh [3,1];

                     for i := 1 to godel_tavla - 1 do
                         for j := 1 to godel_tavla - 1 do
                             begin
                                  if resh [i+3,j] = 1 then
                                     tavla_mishni [i,j] := 1
                                  else
                                      tavla_mishni [i,j] := 0
                             end;

                     close (kovetz);
                end
             else
                 begin
                      clrscr;
                      gotoxy(40,12);
                      write('•…—„ „€‰˜— „‰’ š‰‰—');
                 end;
        end
     else
         begin
              clrscr;
              gotoxy(40,12);
              write('•…—„ š‡‰š” „‰’ š‰‰—');
         end;
   {$I+}
     natun_chazara := 4;
end;                                   {*1.7*}
{======================================================================}

procedure ktiva(var natun_chazara: integer);{•…— ‰…š„ Œ™ „‰š‹}

{*************************************}

begin                                  {*1.8*}
    {$I-}
     assign (kovetz,'life.dat');
     rewrite (kovetz); { „‰š‹Œ •…—„ š‡‰š” }
     if ioresult = 0 then
        begin
             resh [1,1] := prisa;
             resh [2,1] := boded;
             resh [3,1] := chenek;

             for i := 1 to godel_tavla - 1 do
                 for j := 1 to godel_tavla - 1 do
                     resh [i+3,j] := tavla_mishni [i,j];
             write (kovetz,resh);
             if ioresult <> 0 then
                begin
                     clrscr;
                     gotoxy(40,12);
                     write('•…—Œ „‰š‹ „‰’ š‰‰—');
                end;
             close (kovetz);
        end
     else
         begin
              clrscr;
              gotoxy(40,12);
              write('•…—„ š‡‰š” „‰’ š‰‰—');
         end;
    {$I+}
     natun_chazara := 1;
end;                                   {*1.8*}
{======================================================================}

                      {=====š‰™€˜ š‰‹…š=====}
begin                                         {*1*}
     pticha;                                  {*1.1*}
     asama(i,prisa,boded,chenek);             {*1.2*}
     repeat
           case i of
                1 : tafrit(i);                {*1.3*}
                2 : atzavat_yeshuvim(i);      {*1.4*}
                3 : netunim(i);               {*1.5*}
                4 : mischak(i);               {*1.6*}
                5 : kria(i);                  {*1.7*}
                6 : ktiva(i);                 {*1.8*}
           end;
     until i = 7;
end.                                          {*1*}
{**********************************************************************}
