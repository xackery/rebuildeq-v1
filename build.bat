@echo off
echo Shutting down docker-compose... (in case it was running)
docker-compose down

echo Building 'build' docker container...
docker build docker/build/. -t buildeq

echo Prepping Cmake...
docker run -v %cd%:/src -v %cd%\deploy\server:/eqemu buildeq /bin/bash -c "/usr/bin/cmake ~/."

echo Building binaries...
docker run -v %cd%:/src -v %cd%\deploy\server:/eqemu buildeq

echo Copying binaries...
copy bin\* deploy\server\

echo Building docker-compose...
docker-compose build

if not exist "deploy\server\eqemu_config.xml" echo Copying eqemu_config.xml... && copy "docker\eqemu\eqemu_config.xml" "deploy\server"
if not exist "deploy\server\shared" echo Making shared directory... && mkdir deploy\server\shared

echo Running shared memory...
docker-compose run eqemu /eqemu/shared_memory

echo Build completed. Run start.bat start the environment, inject DB via localhost. When modifications are done, run rebuild.bat from now on. DO NOT re-run build.bat unless it's a big issue.