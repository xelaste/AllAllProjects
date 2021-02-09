@setlocal

@REM ==== START VALIDATION ====
if not "%JAVA_HOME%" == "" goto OkJHome

echo.
echo Error: JAVA_HOME not found in your environment. >&2
echo Please set the JAVA_HOME variable in your environment to match the >&2
echo location of your Java installation. >&2
echo.
goto error
:OkJHome
start %JAVA_HOME%/bin/java -Dfile.encoding=UTF8 -jar .\BE\target\BE-1.0-SNAPSHOT.jar
start %JAVA_HOME%/bin/java -Dfile.encoding=UTF8 -jar .\UI\target\UI-1.0-SNAPSHOT.jar
goto end
:error
set ERROR_CODE=1

:end
@endlocal & set ERROR_CODE=%ERROR_CODE%

endLocal