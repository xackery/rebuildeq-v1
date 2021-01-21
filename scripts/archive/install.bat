@echo off

::THIS SHOULD ONLY BE RAN ONCE, unless there's a critical change or something. It builds up the images and preps the environment.
::This preps a docker environment for building binaries.
::echo Removing old build data
::del CMakeCache.txt

echo Shutting down docker-compose... (in case it was running)
docker-compose down

::echo Building 'build' docker container...
::docker build docker/build/. -t buildeq

::echo Prepping Cmake...
::docker run -v %cd%:/src -v %cd%\deploy\server:/eqemu buildeq /bin/bash -c "/usr/bin/cmake ~/."

::echo Building binaries...
::docker run -v %cd%:/src -v %cd%\deploy\server:/eqemu buildeq

::echo Copying binaries...
::copy bin\* deploy\server\

::echo Building docker-compose...
::docker-compose build

if not exist "deploy\server\eqemu_config.xml" echo Copying eqemu_config.xml... && copy "docker\eqemu\eqemu_config.xml" "deploy\server"
if not exist "deploy\web\application\config\database.php" echo Copying database.php... && copy "docker\web\database.php" "deploy\web\application\config"
if not exist "deploy\web\application\cache" echo Making web cache directory... && mkdir deploy\web\application\cache
if not exist "deploy\web\application\logs" echo Making web log directory... && mkdir deploy\web\application\logs

if not exist "deploy\server\shared" echo Making shared directory... && mkdir deploy\server\shared

::echo Running shared memory...
::docker-compose run eqemu /eqemu/shared_memory

echo Build completed. Run start.bat start the environment, inject DB via localhost.