#!/bin/bash
if [ -e "./out/extra2" ]; then
    rm "./out/extra2"
fi

gcc ./programs/extra2.c ./libraries/sharedMemory.c -o ./out/extra2

if [ -e "./out/extra2" ]; then
    ./out/extra2
fi