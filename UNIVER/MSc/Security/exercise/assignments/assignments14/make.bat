setLocal
call set_env.bat
del /s  /q .\bin
%JAVA_HOME%\bin\javac  -verbose  -g -d .\bin .\src\cipher\*.* .\src\crack\*.*
%JAVA_HOME%\bin\jar -cvf .\lib\VigenereAndPermutationCipher.jar -C .\bin cipher -C .\bin crack
endLocal