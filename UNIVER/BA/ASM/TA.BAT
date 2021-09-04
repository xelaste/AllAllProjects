tasm/z/l %1 >aa
if not exist %1.obj goto ERROR
tlink/v %1
goto END
:ERROR
list aa
:END
