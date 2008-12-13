#
# o---------------------------------------------------------------------o
# |
# | COS Standard Library
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
# | $Id: Makefile,v 1.6 2008/12/13 00:50:03 ldeniau Exp $
# |
#

# detect location (bootstrap, normally $(cos) = cos)
pwd := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
cos := $(pwd)/../CosBase/include/cos

# standard COS makefile

include $(cos)/prologue

library := CosStd
version := 0.1
moddeps := CosBase

include $(cos)/epilogue

# end of makefile
