#!/bin/sh

gcc -m64 -std=c99 -O3 -Wall -W -pedantic *.m *.c -o testObjc -lobjc
