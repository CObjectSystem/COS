#
#  C Object System
#  COS example
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
cos := ../../../CosBase/include/cos

# standard COS makefile

include $(cos)/prologue

# project
program := cos-ex01

# targets
targets := release.run # debug.run

# files & modules
sources := *.c
defgens := 
defprps :=

# project dependencies (as with -lname)
moddeps := CosStd CosBase

# project dependencies (as with -Ipath or -Lpath)
incdirs := ../../../CosBase/include ../../include .
libdirs := ../../../CosBase/$(OSNAME)/lib ../../$(OSNAME)/lib

include $(cos)/epilogue

# end of COS example makefile
