setlocal
set MAVEN_OPTS=-Xms512m -Xmx1024m -Dhttp.proxyHost=genproxy -Dhttp.proxyPort=8080 -Dhttps.proxyHost=genproxy -Dhttps.proxyPort=8080
set JAVA_HOME=C:\Java\jdk-14.0.1
call mvnw.cmd clean install
:call mvnw.cmd clean install eclipse:eclipse
endlocaL
