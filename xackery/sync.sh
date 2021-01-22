#!/bin/bash
cd ..
rsync -aP --exclude '*.cmakein' --exclude 'Makefile' --exclude 'CMakeFiles' --exclude '.git' --exclude 'CMakeCache.txt' --exclude '*.cmake' --exclude '*.make' . 10.0.0.10:~/eq/src-latest
ssh 10.0.0.10 "cd /workspaces/src-latest && make"
