#!/bin/bash
if [ -e "./out/barbero" ]; then
    rm "./out/barbero"
fi

gcc ./programs/barbero.c ./libraries/sharedMemory.c -o ./out/barbero

if [ -e "./out/barbero" ]; then
    ./out/barbero
fi