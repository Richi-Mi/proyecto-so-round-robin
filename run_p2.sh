#!/bin/bash
if [ -e "./out/ejercicioP2" ]; then
    rm "./out/ejercicioP2"
fi

gcc ./programs/test.c ./libraries/sharedMemory.c -o ./out/ejercicioP2

if [ -e "./out/ejercicioP2" ]; then
    ./out/ejercicioP2
fi