@echo ################################
set JAVA_HOME=C:\Java\jdk-14.0.1
set MAVEN_OPTS=-Xms512m -Xmx1024m -Dhttp.proxyHost=genproxy -Dhttp.proxyPort=8080 -Dhttps.proxyHost=genproxy -Dhttps.proxyPort=8080
:set MAVEN_CONFIG=%MAVEN_OPTS%
@echo ################################