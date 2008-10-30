#!/bin/sh

# linux option
OPTIONS="-DCOS_C89 -DCOS_POSIX=1 -DCOS_TLS=1 -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE"

# compile .c to .o
for f in src/*.c; do
  f=src/`basename $f .c`
  cpp -std=c99 -Wall -w -pedantic -Iinclude $OPTIONS -E $f.c -o $f.i;
  gcc -std=c89 -Wall -W -pedantic -O3                -c $f.i -o $f.o;
  rm  $f.i
done

# archive (does not run cossym)
ar -cr src/libCosBase89.a src/*.o

# build program:
# cd path/to/program
# cossym libCosBase89.a src/*.o
# cc _cossym.c libCosBase89.a src/*.o -o program

