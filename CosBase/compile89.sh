#!/bin/sh
#
#  C Object System
#  COS HOWTO compile CosBase in C89 mode (example for Linux)
# 
#  Copyright 2007+ Laurent Deniau <laurent.deniau@gmail.com>
# 
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
# 
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

#
# NOTE-USER: c89 example
# this example is for CosBase itself which is C89 compliant
#

# defines
NAME=CosBase
OSNAME=`uname -s`
DEFINE="-DCOS_C89 -DOSNAME=$OSNAME -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE"

# dirs
incdir=include
srcdir=src
bindir=$OSNAME/bin

# compiler (C99 is only used for preprocessing)
C89="c89 -Iinclude -O3 $DEFINE"
C99="c99 -Iinclude -O3 $DEFINE -w"  # -w can be removed

# check location
PWD=`basename \`pwd\``

if [ "$PWD" != "$NAME" ] ; then
  echo `basename $0` "must be run from the $NAME directory"
  exit;
fi

# cleaning
rm -f $srcdir/${NAME}_gens.c \
      $srcdir/${NAME}_prps.c \
      $srcdir/${NAME}_syms.c \
      $srcdir/lib${NAME}89.a \
      $srcdir/*.o

if [ "$1" = "clean" ] ; then
  exit 1
fi

# 1) collect generics and properties (preprocessing only)
$bindir/cosgen --out=$srcdir/${NAME}_gens.c $incdir/cos/gen/*.h
$bindir/cosprp --out=$srcdir/${NAME}_prps.c $incdir/cos/prp/*.h

# 2) compile source files (2 steps)
for f in $srcdir/*.c ; do
  f=$srcdir/`basename $f .c`
  echo "compiling $f.c"
  $C99 -E $f.c -o $f.i # 2.1) preprocessing
  $C89 -c $f.i -o $f.o # 2.2) compilation
  rm $f.i
done

# 3) collect symbols (compilation only)
$bindir/cossym --out=$srcdir/${NAME}_syms.c $srcdir/*.o
$C89 -c -o $srcdir/${NAME}_syms.o $srcdir/${NAME}_syms.c

# build archive
ar -rc $srcdir/lib${NAME}89.a $srcdir/*.o

# build program (require main() to be defined)
# $C89 $srcdir/*.o main.o -o program

# build program from archive (idem)
# $C89 $srcdir/libCosBase89.a main.o -o program

