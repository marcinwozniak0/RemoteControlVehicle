#!/bin/bash

### NEEDED LINUX PACKAGES ###
apt-get update  --yes
apt-get install --yes build-essential
apt-get install --yes libboost-all-dev
apt-get install --yes valgrind
apt-get install --yes wget
apt-get install --yes git
apt-get install --yes pkg-config
apt-get install --yes golang
apt-get install --yes curl
apt-get install --yes zip 
apt-get install --yes unzip
apt-get install --yes libssl-dev

###NEEDED 'FROM SOURCE' PACKAGES ###
#CMAKE
wget -qO- "https://cmake.org/files/v3.15/cmake-3.15.0-Linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local

#PROTOC
PROTOC_ZIP=protoc-3.11.2-linux-x86_64.zip
curl -OL https://github.com/protocolbuffers/protobuf/releases/download/v3.11.2/$PROTOC_ZIP
unzip -o $PROTOC_ZIP -d /usr/local bin/protoc
unzip -o $PROTOC_ZIP -d /usr/local 'include/*'
rm -f $PROTOC_ZIP

#PROTOBUF LIBS
wget https://github.com/protocolbuffers/protobuf/releases/download/v3.8.0/protobuf-all-3.8.0.zip
unzip protobuf-all-3.8.0.zip
cd protobuf-3.8.0
./autogen.sh
./configure
make -j8
make install
ldconfig


