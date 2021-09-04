echo off
gfx pk sysdemo /i /v1 /q255
if not errorlevel 1 goto end
echo ---------------------------------------------------------------------------
echo Please remove any memory resident software (including GraFiX) and try again
echo ---------------------------------------------------------------------------
exit
:end
