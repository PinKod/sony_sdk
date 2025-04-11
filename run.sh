#!/bin/bash

rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc)
sudo sh reset.sh
sudo ./bin/sample_app
cd ..   