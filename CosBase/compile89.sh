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
# | $Id: compile89.sh,v 1.4 2008/12/02 17:32:21 ldeniau Exp $
# |
#

#
# NOTE-USER: c89 example
# this example is for CosBase itself which is C89 compliant
#

# dirs
incdir=include
srcdir=src
exedir=../build/exe

# defines
DEFINE="-DCOS_C89 -DCOS_POSIX=1 -DCOS_TLS=1 -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE"

# compiler (C99 is only used for preprocessing)
C99="cc -std=c99 -pedantic -W -Wall -Iinclude -O3 $DEFINE -w"  # -w can be removed
C89="cc -std=c89 -pedantic -W -Wall -Iinclude -O3 $DEFINE"

# check location
PWD=`basename \`pwd\``

if [ "$PWD" != "CosBase" ] ; then
  echo `basename $0` "must be run from the CosBase directory"
  exit;
fi

# cleaning
rm -f $srcdir/_cosgen.c $srcdir/_cossym.c $srcdir/libCosBase89.a $srcdir/*.o

if [ "$1" = "clean" ] ; then
  exit 1
fi

# 1) collect generics (preprocessing only)
gen=`ls $incdir/cos/gen/*.h`
$C99 -E $gen | $exedir/cosgen --out=$srcdir/_cosgen.c $gen

# 2) compile source files (2 steps)
for f in $srcdir/*.c; do
  f=$srcdir/`basename $f .c`
  echo "compiling $f.c"
  $C99 -E -o $f.i $f.c # 2.1) preprocessing
  $C89 -c -o $f.o $f.i # 2.2) compilation
  rm $f.i
done

# 3) collect symbols (compilation only)
$exedir/cossym --out=$srcdir/_cossym.c $srcdir/*.o
$C89 -c -o $srcdir/_cossym.o $srcdir/_cossym.c

# build archive
ar -cr $srcdir/libCosBase89.a $srcdir/*.o

# build program (require main() to be defined)
# $C89 $srcdir/*.o -o program

# build program from archive (idem)
# $C89 $srcdir/libCosBase89.a -o program

