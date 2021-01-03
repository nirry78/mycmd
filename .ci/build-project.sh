#!/bin/bash

if [[ ! -d output ]]; then
    mkdir -p output
    cd output && cmake ..
fi

cd output && make -j10