#!/bin/bash


status=$1

rm -rf build
mkdir build && cd build

if [ "$status" = "debug" ]; then
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cmake ..
fi


