#!/bin/bash

#NEEDED LINUX PACKAGES
apt-get update --yes
apt-get install --yes build-essential
apt-get install --yes cmake
apt-get install --yes protobuf-compiler
apt-get install --yes libboost-all-dev
apt-get install --yes valgrind
apt-get install --yes wget
apt-get install --yes git
apt-get install --yes grpc++

#NEEDED EXTERNAL PACKAGES
wget -qO- "https://github.com/protocolbuffers/protobuf/releases/download/v3.10.1/protobuf-cpp-3.10.1.tar.gz" | tar --strip-components=1 -xz -C /usr/local

