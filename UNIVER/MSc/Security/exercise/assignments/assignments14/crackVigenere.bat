setlocal
call set_env.bat
%JAVA_HOME%\bin\java -classpath %LIB%\VigenereAndPermutationCipher.jar crack.VigenereCipherCracker %DAT%\ex14.vig.secret
endlocal