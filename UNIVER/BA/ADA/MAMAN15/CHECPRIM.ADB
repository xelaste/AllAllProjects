--*************************************************************
with PRIME;
procedure CHECK_PRIME is
X:PRIME.INPUT_ARRAY_TYPE(1..100):=(others=>0);
begin
for I in X'RANGE loop
X(I):=I;
end loop;
PRIME.FIND_PRIME_NUMBERS(X,10);
end;