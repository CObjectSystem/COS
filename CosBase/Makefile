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
# | $Id: Makefile,v 1.20 2009/02/23 09:59:48 ldeniau Exp $
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
defprps := # default

# project components (only sub{module} names)
modules := # none

# project dependencies (only {module|library} names as with -lname)
moddeps := # none
libdeps := # none

# project dependencies (only {module|library|include|binary} paths as with -Ipath or -Lpath)
moddirs := # default
libdirs := # none
incdirs := # none
bindirs := # none

# patterns (clean, install-excluded, tar-excluded)
cleanpat := # default
tarexpat := # default
insexpat := # default

include $(cos)/epilogue

#
# makefile customization
#

# COS tools installation:
# 'cosgen' boostrap version of COS uses a portable 'coscmt' sed script to remove
# C comments but the installed version uses a much faster C version of coscmt.

install.pre: $(BINDIR)/$(COSCMT)
	$_ $(RM)    $(INSTDIR)/bin/$(COSCMT)
	$_ $(CP) $< $(INSTDIR)/bin/$(COSCMT)

$(BINDIR)/$(COSCMT): CCFLAGS := $(CCFLAGS)
$(BINDIR)/$(COSCMT): $(BASEDIR)/tools/src/coscmt.c
	$_ $(CC) $(CCFLAGS) $< -o $@
	$_ $(if $(STRIP),$(STRIP) $@)

# COS uninstallation:
# remove $(prefix)/include/cos and $(prefix)/share/doc/cos directories

uninstall.post:
	$_ for d in $(INSTDIR)/include/cos $(INSTDOC) ; do \
	     if [ -d $$d ] ; then \
	       echo "*** Removing $$d" ; \
	       $(RM) $$d ; \
	     fi ; \
	   done

# end of COS makefile

