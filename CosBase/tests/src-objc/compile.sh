#!/bin/sh

gcc -std=c99 -O3 -Wall -W -pedantic *.m *.c -o testObjc -lobjc
