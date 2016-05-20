#
#  C Object System
#  COS Base Library
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

# bootstrap, normally $(cos) = cos
cos := include/cos

#
# standard COS makefile
#

include $(cos)/prologue

# project
library := CosBase
version := 0.9
release := 201003
package := $(library)-$(version)_$(release)

# targets
targets := all

# files and modules
sources := src/*.c
headers := include/cos/*.h include/cos/*/*.h
defgens := include/cos/gen/*.h
defprps := include/cos/prp/*.h

# project dependencies (as with -lname)
libdeps := $(SYSLIBS)
moddeps :=

# project dependencies (as with -Ipath or -Lpath)
incdirs := src include
bindirs :=
libdirs :=
moddirs :=

# documentation
auxdocs :=

# patterns (clean, install-excluded, tar-excluded)
cleanpat :=
tarexpat :=
insexpat :=

# reload makefile (bootstrap)
ifeq ($(filter clean% tarball% uninstall%,$(MAKECMDGOALS)),)
DOIT := $(if $(BOOTSTRAP),,$(shell $(MAKE) -R bootstrap BOOTSTRAP=yes))
endif

include $(cos)/epilogue

# end of (standard) makefile

#
# COS boostrap
# install tools cosgen, cosprp, coscmt and cossym before anything else is done.
#
.PHONY: bootstrap

bootstrap: $(OSNAME)/bin/coscmt$(BINEXT)
	$_ cp -fP bin/cosgen $(dir $<)
	$_ cp -fP bin/cosprp $(dir $<)
	$_ cp -fP bin/cossym $(dir $<)

$(OSNAME)/bin/coscmt$(BINEXT): CCFLAGS := $(CCFLAGS)
$(OSNAME)/bin/coscmt$(BINEXT): tools/src/coscmt.c
	$_ $(call mkdir,$(dir $@)) 
	$_ $(CC) $(CCFLAGS) $< -o $@
	$_ $(if $(STRIP),$(STRIP) $@)

