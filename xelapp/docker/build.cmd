setlocal
docker build --no-cache --progress=plain -t xelaste/xelasteallallapps:v03 -f .\Dockerfile ..
docker push xelaste/xelasteallallapps:v03
endlocal
