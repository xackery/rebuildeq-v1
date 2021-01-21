# first run, use the command make initial
default: build

.PHONY: help
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
initial: ## ** Makes an initial run, RUN THIS FIRST TIME **
	@if [ ! -f $(shell pwd)/server/eqemu_config.xml ]; then echo "Copying deploy/server/eqemu_config.xml..."; cp $(shell pwd)/../docker/eqemu/eqemu_config.xml $(shell pwd)/server/; fi;
	@if [ ! -f $(shell pwd)/web/application/config/database.php ]; then echo "Copying deploy/web/applicaton/config/database.php..."; cp $(shell pwd)/../docker/web/database.php  $(shell pwd)/web/application/config/; fi;
	@if [ ! -d $(shell pwd)/web/application/cache ]; then echo "Making deploy/web/application/cache..."; mkdir $(shell pwd)/web/application/cache; fi;
	@if [ ! -d $(shell pwd)/web/application/logs ]; then echo "Making deploy/web/application/logs..."; mkdir $(shell pwd)/web/application/logs; fi;
	#@if [ ! -f $(shell pwd)/web/html ]; then echo "Making symlink deploy/web/html..."; ln -s  $(shell pwd)/web/web $(shell pwd)/web/html; fi;
	make images
	make cmake
	make build
	make shared
	@echo "Initialized successfully. Run make services, make world, and make zone in different consoles."
images: ## Builds docker images needed to run dockerized eqemu
	docker build ../docker/build -t buildeq
	docker build ../docker/eqemu -t eqemu
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "wget http://ftp.us.debian.org/debian/pool/main/libs/libsodium/libsodium-dev_1.0.11-1~bpo8+1_amd64.deb -O /eqemu/libsodium-dev.deb"
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "wget http://ftp.us.debian.org/debian/pool/main/libs/libsodium/libsodium18_1.0.11-1~bpo8+1_amd64.deb -O /eqemu/libsodium18.deb"
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "dpkg -i /eqemu/libsodium*.deb"
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "rm -f /eqemu/libsodium-dev.deb"
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "rm -f /eqemu/libsodium18.deb"
purge: ## Purge containers and images made by this system.
	docker rm $(shell docker ps -a -q)
	docker rmi rebuildeq_web buildeq
cmake: ## Runs cmake inside build image to prepare for build
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "/usr/bin/cmake ~/."
build: ## Builds binaries using build image for eqemu image
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "make"
clean: ## Cleans the build files using build image
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "make clean"
shared: ## Runs shared_memory inside eqemu image
	-docker run -v $(shell pwd)/../deploy/server:/eqemu --network="rebuildeq_default" --name shared -it eqemu /eqemu/shared_memory
	docker rm shared
services: ## Runs docker-compose up, starting database, nats, and web server
	cd ..
	-docker-compose down
	-docker-compose up
	docker-compose down
world: ## Starts world binary using eqemu image
	cd ..
	-docker run -v $(shell pwd)/../deploy/server:/eqemu -p 5998:5998/udp -p 5999:5999/udp -p 9000:9000/udp -p 9000:9000 --name world --network="rebuildeq_default" -it eqemu /eqemu/world
	docker rm world
zone: ## Starts zone1 using 7001. use make zone1, make zone2, etc for additional zones
	zone1 
zone1: ## Starts zone binary using eqemu image on port 7001
	docker run -v $(shell pwd)/../deploy/server:/eqemu --network="rebuildeq_default"  -p 7001:7001/udp -it eqemu /eqemu/zone ecommons:7001
zone2: ## Starts zone binary using eqemu image on port 7002
	docker run -v $(shell pwd)/../deploy/server:/eqemu --network="rebuildeq_default"  -p 7002:7002/udp -it eqemu /eqemu/zone chardok:7002	
zone3: ## Starts zone binary using eqemu image on port 7003
	docker run -v $(shell pwd)/../deploy/server:/eqemu --network="rebuildeq_default"  -p 7003:7003/udp -it eqemu /eqemu/zone pojustice:7003
proto: ## Removes proto compiled files and generates new ones based on proto folder
	rm -rf ../common/proto/*
	rm -rf ../go/eqproto/*
	protoc --cpp_out=../common/proto --go_out=../go/eqproto -I ../proto ../proto/message.
discordeq: ## Run discordeq in developer mode
	cd ../go/discordnats
	go run main.go
buildeqbash: ## Run buildeq container and attach bash
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu -it buildeq /bin/bash
eqemubash: ## Run eqemu container and attach bash
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu -it eqemu /bin/bash