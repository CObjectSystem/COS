#
# o---------------------------------------------------------------------o
# |
# | COS testsuite
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
# | $Id: Makefile,v 1.7 2009/09/05 21:13:38 ldeniau Exp $
# |
#

# bootstrap, normally $(cos) = cos
cos := ../../CosBase/include/cos

# standard COS makefile

include $(cos)/prologue

# project
program := testCosStd

# targets
targets := debug.run

# files and modules
sources := $(wildcard src/*.c)
headers := $(wildcard src/*.h)
defgens := $(headers)
defprps := $(headers)

# project dependencies (as with -lname)
moddeps := CosBase CosStd

# project dependencies (as with -Ipath or -Lpath)
incdirs := $(foreach m,$(moddeps),../../$(m)/include) src
libdirs := $(foreach m,$(moddeps),../../$(m)/$(OSNAME)/lib)

include $(cos)/epilogue

# end of makefile
