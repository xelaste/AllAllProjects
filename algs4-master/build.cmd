setlocal
set java_home=C:\java\jdk1.8.0_301
set maven_home=C:\apache-maven-3.8.4
call %maven_home%\bin\mvn clean
call %maven_home%\bin\mvn eclipse:clean
call %maven_home%\bin\mvn install
endlocal