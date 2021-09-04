;*------------------------
PROC b ()
RUN "del m14.dat"
PRINT FILE "m14.dat"  x," ",y,"\n"
FOR i FROM 1 TO x
    FOR j FROM 1 TO y PRINT FILE "m14.dat" FORMAT ("w5",STRVAL(b[y*(i-1)+j]))," "  ENDFOR
    PRINT FILE "m14.dat" "\n"
ENDFOR
ENDPROC
;*-------------------------
ACCEPT "N" TO x
ACCEPT "N" TO y
ARRAY a[x*y]
ARRAY b[x*y]
FOR i FROM 1 TO x
    FOR j FROM 1 TO y
        a[y*(i-1)+j]=FALSE
    ENDFOR
ENDFOR
i=0
WHILE i<x*y
z=INT((x*y)*RAND() + 1)
      ? z
      lne=ROW()
      clm=COL()
      @ 12,30
      ?? i ," ",x*y
      @ lne ,clm
      IF  a[z] = FALSE THEN
          a[z] = TRUE
          i=i+1
          b[i] = z
       ENDIF
ENDWHILE
b()
