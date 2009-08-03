#
# o---------------------------------------------------------------------o
# |
# | COS example
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
# | $Id: Makefile,v 1.1 2009/08/03 21:20:39 ldeniau Exp $
# |
#

# bootstrap, normally $(cos) = cos
cos := ../../../CosBase/include/cos

# standard COS makefile

include $(cos)/prologue

# project
program := cos-ex01

# targets
targets := release.run # debug.run

# files & modules
sources := $(wildcard *.c)
defgens := $(wildcard generics.h)
defprps := $(wildcard properties.h)

# project dependencies (as with -lname)
moddeps := CosBase CosStd

# project dependencies (as with -Ipath or -Lpath)
incdirs := ../../../CosBase/include ../../include .
libdirs := ../../../CosBase/$(OSNAME)/lib ../../$(OSNAME)/lib

include $(cos)/epilogue

# end of COS example makefile
