setlocal
call set_env.bat
%JAVA_HOME%\bin\java -classpath %LIB%\VigenereAndPermutationCipher.jar cipher.SimplePermutationCipher -k %KEY% -f %DAT%\ex14.data -o %DAT%\ex14.prm.secret
endlocal