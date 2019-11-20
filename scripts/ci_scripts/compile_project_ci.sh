#!/bin/bash
cd /builds/marcinwozniak0/IntelligentVehicle
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
