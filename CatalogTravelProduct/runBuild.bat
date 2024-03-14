cls
setlocal
set MAVEN_HOME=C:\apache-maven-3.9.6
set MAVEN_OPTS=-Xms512m -Xmx1024m -XX:MaxPermSize=128m 
:-Dhttp.proxyHost=genproxy -Dhttp.proxyPort=8080
set JAVA_HOME=C:\Java\jdk1.8.0_202
call %MAVEN_HOME%\bin\mvn clean -Dmaven.repo.local=C:\ATT\.m2-mex\repository
call %MAVEN_HOME%\bin\mvn -U install -Dmaven.repo.local=C:\ATT\.m2-mex\repository -Dhttps.proxyHost=genproxy -Dhttps.proxyPort=8080 -Dhttp.proxyHost=genproxy -Dhttp.proxyPort=8080
endlocal
