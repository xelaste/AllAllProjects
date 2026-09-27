setlocal
docker build --no-cache --progress=plain -t xelaste/xelasteallallapps:v02 -f .\Dockerfile ..
docker push xelaste/xelasteallallapps:v02
endlocal
