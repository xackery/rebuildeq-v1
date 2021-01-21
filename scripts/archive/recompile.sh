echo Building binaries...
docker run -v `pwd`:/src -v `pwd`/deploy/server:/eqemu buildeq

echo Copying binaries...
cp bin/* deploy/server/

echo Recompile completed. Run start.sh to start the environment.
