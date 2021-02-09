In order to build / run application 
1) make sure JAVA_HOME env var - location of a JDK home dir exists 
2) The maven central repository is accessible in case it runs behind the proxy apply maven options e.g 
set MAVEN_OPTS=-Dhttp.proxyHost=${proxyname} -Dhttp.proxyPort=${proxyport} -Dhttps.proxyHost=${proxyname} -Dhttps.proxyPort=${proxyport}

Build application 
	run mvnw clean install
Run application – run script startEnv.bat

These instructions are for windows 

For the Linux shell 
make sure JAVA_HOME env var exists
make mvnw executable
run build  - run mvnw clean install
run applications
${JAVA_HOME}/bin/java -Dfile.encoding=UTF8 -jar .\BE\target\BE-1.0-SNAPSHOT.jar 
${JAVA_HOME}/bin/java -Dfile.encoding=UTF8 -jar .\UI\target\UI-1.0-SNAPSHOT.jar
from the folder where this file is.

Calling the application http://localhost:4050/names?threads=5&time=10&prefix=THA (GET request)
Regenerate the input http://localhost:4050/reset (GET request)

Files location
input.file.name=${user.dir}/DavidCopperField.txt 
input.dir=${user.home}/eci/IN
output.dir=${user.home}/eci/OUT


It is possible to change the location by providing the command line option arguments
e.g
${JAVA_HOME}/bin/java -Dfile.encoding=UTF8 -jar .\BE\target\BE-1.0-SNAPSHOT.jar --input.file.name=..

or use Application property files
SpringApplication will load properties from application.properties files in the following locations and add them to the Spring Environment:
A /config subdir of the current directory.
The current directory
A classpath /config package
The classpath root
