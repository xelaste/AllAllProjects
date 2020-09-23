cls
setlocal
set MAVEN_HOME=C:\apache-maven-3.2.5
set MAVEN_OPTS=-Xms512m -Xmx1024m -XX:MaxPermSize=128m -Dhttp.proxyHost=genproxy -Dhttp.proxyPort=8080
: Execute clean
set JAVA_HOME=C:\Java\jdk1.7.0_79
call %MAVEN_HOME%\bin\mvn  eclipse:clean -Dmaven.repo.local=C:\ATT\.m2-mex\repository
call %MAVEN_HOME%\bin\mvn  eclipse:eclipse -Dmaven.repo.local=C:\ATT\.m2-mex\repository
endlocal
