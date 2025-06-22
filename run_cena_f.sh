#!/bin/bash
if [ -e "./out/cenaFilosofos" ]; then
    rm "./out/cenaFilosofos"
fi

gcc ./programs/la_cena_de_los_filosofos.c ./libraries/sharedMemory.c -o ./out/cenaFilosofos

if [ -e "./out/cenaFilosofos" ]; then
    ./out/cenaFilosofos
fi