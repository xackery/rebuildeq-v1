#!/bin/bash
#Remove placeholder for deploy/web/html/changelog and if it fails, do not show error.
rm -v deploy/web/html/changelog 2> /dev/null
docker-compose run web run-hugo.sh

