FROM ubuntu:16.04

RUN apt-get -y update \
	&& apt-get install -y liblua5.1 libmysql++ libperl5i-perl lua5.1 zlibc wget

ENV HOME /eqemu
WORKDIR /eqemu

# Define default command.
CMD ["/eqemu/eqemu_cmd.sh"]
