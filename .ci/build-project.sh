#!/bin/bash

if [[ ! -d output ]]; then
    mkdir -p output
    pushd output
    cmake ..
    popd
fi

cd output && make -j10