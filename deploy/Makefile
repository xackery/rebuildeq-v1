default: build
## typical order of this makefile is:
# make images
# make cmake
# make build
# make services
# make world
# make zone

.PHONY: help
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

images: ## Builds docker images needed to run dockerized eqemu
	docker build ../docker/build
	docker build ../eqemu
cmake: ## Runs cmake inside build image to prepare for build
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "/usr/bin/cmake ~/."
build: ## Builds binaries using build image for eqemu image
	docker run -v $(shell pwd)/../:/src -v $(shell pwd)/../deploy/server:/eqemu buildeq /bin/bash -c "make"
shared: ## Runs shared_memory inside eqemu image
	-docker run -v $(shell pwd)/../deploy/server:/eqemu --network="rebuildeq_default" --name shared -it eqemu /eqemu/shared_memory
	docker rm shared
services: ## Runs docker-compose up, starting database, nats, and web server
	cd ..
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
	protoc --cpp_out=../common/proto --go_out=../go/eqproto -I ../proto ../proto/message.proto