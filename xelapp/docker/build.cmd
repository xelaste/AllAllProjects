setlocal
docker build -t xelaste/xelasteallallapps:v01 -f .\Dockerfile ..
docker push xelaste/xelasteallallapps:v01
endlocal
