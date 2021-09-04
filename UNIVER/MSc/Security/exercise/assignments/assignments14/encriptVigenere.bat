setlocal
call set_env.bat
%JAVA_HOME%\bin\java -classpath %LIB%\VigenereAndPermutationCipher.jar cipher.VigenereCipher -k %KEY% -f %DAT%\ex14.data -o %DAT%\ex14.vig.secret
endlocal