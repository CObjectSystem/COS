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
# | $Id: compile89.sh,v 1.2 2008/10/30 11:11:21 ldeniau Exp $
# |
#

# linux options
OPTIONS="-DCOS_C89 -DCOS_POSIX=1 -DCOS_TLS=1 -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE"

# location
PWD=`basename \`pwd\``

if [ "$PWD" != "CosBase" ] ; then
  echo `basename $0` "must be run from the CosBase directory"
  exit;
fi

# compile .c to .o
for f in src/*.c; do
  f=src/`basename $f .c`
  echo "compiling $f.c"
  cpp -std=c99 -pedantic -w -Iinclude $OPTIONS -E -o $f.i $f.c;
  cc  -std=c89 -pedantic -W -Wall -O3          -c -o $f.o $f.i;
  rm  $f.i
done

# archive
echo "building  src/libCosBase89.a"
ar -cr src/libCosBase89.a src/*.o

# build program:
# cd path/to/program
# cossym libCosBase89.a src/*.o
# cc _cossym.c libCosBase89.a src/*.o -o program

