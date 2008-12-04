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
# | $Id: Makefile,v 1.9 2008/12/04 18:43:56 ldeniau Exp $
# |
#

# detect location (bootstrap, normally $(cos) = cos)
pwd := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
cos := $(pwd)/include/cos

# standard COS makefile

include $(cos)/prologue

library := CosBase
version := 0.7
release := 200801
package := $(library)-$(version)_$(release)

# variables hereafter could be omitted

targets := # default (debug profile release static shared)
headers := # default
sources := # default
defgens := # default ($(wildcard $(BASEDIR)/include/cos/gen/*.h))

# only names (as with -lname)
moddeps := # none
libdeps := # none

# only directories
moddirs := # default (. ..)
libdirs := # none
incdirs := # none

include $(cos)/epilogue

# end of COS makefile

