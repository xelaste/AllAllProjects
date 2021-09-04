setlocal
call set_env.bat
%JAVA_HOME%\bin\java -classpath %LIB%\VigenereAndPermutationCipher.jar cipher.VigenereCipher -k %KEY% -f %DAT%\ex14.vig.secret -o %DAT%\ex14.vig.clear -d
endlocal