#!/bin/sh
#
# o---------------------------------------------------------------------o
# |
# | COS HowTo compile CosBase in C89 mode (example for Linux)
# |
# o---------------------------------------------------------------------o
# |
# | C Object System
# |
# | Copyright (c) 2007+ Laurent Deniau, laurent.deniau@cern.ch
# |
# | For more information, see:
# | http://cern.ch/laurent.deniau/cos.html
# |
# o---------------------------------------------------------------------o
# |
# | This file is part of the C Object System framework.
# |
# | The C Object System is free software; you can redistribute it and/or
# | modify it under the terms of the GNU Lesser General Public License
# | as published by the Free Software Foundation; either version 3 of
# | the License, or (at your option) any later version.
# |
# | The C Object System is distributed in the hope that it will be
# | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# |
# | See <http://www.gnu.org/licenses> for more details.
# |
# o---------------------------------------------------------------------o
# |
# | $Id: compile89.sh,v 1.3 2008/11/18 19:08:58 ldeniau Exp $
# |
#

# defines
DEFINE="-DCOS_C89 -DCOS_POSIX=1 -DCOS_TLS=1 -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE"

# compiler (C99 is only used for preprocessing)
C99="cc -std=c99 -pedantic -W -Wall -Iinclude -O3 $DEFINE -w"  # -w can be removed
C89="cc -std=c89 -pedantic -W -Wall -Iinclude -O3 $DEFINE"

# location
PWD=`basename \`pwd\``

if [ "$PWD" != "CosBase" ] ; then
  echo `basename $0` "must be run from the CosBase directory"
  exit;
fi

rm -f src/_cosgen.c src/_cossym.c

# collect generics (optional)
../build/exe/cosgen --out=src/_cosgen.c include/cos/gen/*.h

# compile source files (2 steps)
for f in src/*.c; do
  f=src/`basename $f .c`
  echo "compiling $f.c"
  $C99 -E -o $f.i $f.c; # step 1: preprocessing
  $C89 -c -o $f.o $f.i; # step 2: compilation
  rm  $f.i
done

# collect symbols
../build/exe/cossym --out=src/_cossym.c src/*.o

# build program
# $C89 src/_cossym.c src/*.o -o program

# build program from archive (include previous collect & build)
# ar -cr src/libCosBase89.a src/*.o
# cossym --out=src/_cossym.c libCosBase89.a
# $C89 libCosBase89.a src/_cossym.c -o program

