FROM ubuntu:16.04

#RUN apt-get -y update && apt-get install -y build-essential cmake cpp curl debconf-utils g++-6 gcc-6 git git-core libio-stringy-perl liblua5.1 liblua5.1-dev libluabind-dev libmysql++ libperl-dev libperl5i-perl libwtdbomysql-dev libmysqlclient-dev lua5.1 make mariadb-client nano open-vm-tools unzip uuid-dev zlib-bin zlibc && apt-get -y upgrade

RUN apt-get -y update && apt-get install -y libstdc++6 build-essential gcc-5 g++-5 libtool cmake curl debconf-utils git git-core libio-stringy-perl liblua5.1 liblua5.1-dev libluabind-dev libmysql++ libperl-dev libperl5i-perl libwtdbomysql-dev libsodium-dev libsodium18 libmysqlclient-dev lua5.1 minizip make mariadb-client nano open-vm-tools unzip uuid-dev zlibc wget && apt-get -y upgrade


ENV HOME /src
WORKDIR /src

# Define default command.
CMD ["make"]