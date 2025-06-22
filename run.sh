#!/bin/bash
if [ "$#" -lt 1 ]; then
  echo "Ingrese un quantum valido"
  exit 1
fi

if [ -e "./out/main" ]; then
    rm "./out/main"
fi

gcc main.c ./libraries/*.c -o ./out/main

if [ -e "./out/main" ]; then
    ./out/main $1
fi