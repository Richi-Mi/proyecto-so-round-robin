#!/bin/bash
if [ -e "./out/extra" ]; then
    rm "./out/extra"
fi

gcc ./programs/extra.c ./libraries/sharedMemory.c -o ./out/extra

if [ -e "./out/extra" ]; then
    ./out/extra
fi