#!/bin/bash
cd /builds/marcinwozniak0/RemoteControlVehicle/CentralUnit/CMake
mkdir build
cd build
git clone -b v1.32.0 https://github.com/grpc/grpc
cd grpc
git submodule update --init
cd ..
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make -j8
