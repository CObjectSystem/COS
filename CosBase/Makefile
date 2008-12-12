#
# o---------------------------------------------------------------------o
# |
# | COS Base Library
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
# | $Id: Makefile,v 1.12 2008/12/12 16:56:44 ldeniau Exp $
# |
#

# detect location (bootstrap, normally $(cos) = cos)
pwd := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
cos := $(pwd)/include/cos

#
# standard COS makefile
#

include $(cos)/prologue

library := CosBase
version := 0.7
release := 200801

# the following (empty) variables are mentioned for example

package := # default
targets := # default
headers := # default
sources := # default
defgens := # default

# only names (as with -lname)
moddeps := # none
libdeps := # none

# only directories
moddirs := # default
libdirs := # none
incdirs := # none
bindirs := # none

# patterns
cleanpat := # default
tarpat   := # default

include $(cos)/epilogue

#
# makefile customization
#

# COS tools installation:
# 'cosgen' boostrap version of COS uses a portable 'coscmt' sed script to remove
# C comments but the installed version uses a much faster C version of coscmt.

TOOLS = $(filter-out %/coscmt %/CVS, $(wildcard $(BASEDIR)/bin/*))

install.pre: $(BINDIR)/$(COSCMT)
	$_ $(CP) $(TOOLS) $(INSTDIR)/bin

$(BINDIR)/$(COSCMT): CCFLAGS := $(CCFLAGS)
$(BINDIR)/$(COSCMT): $(BASEDIR)/tools/src/coscmt.c
	$_ $(CC) $(CCFLAGS) $< -s -o $@

# end of COS makefile

