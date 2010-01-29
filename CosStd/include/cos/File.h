#ifndef COS_FILE_H
#define COS_FILE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS File
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: File.h,v 1.7 2010/01/29 12:36:34 ldeniau Exp $
 |
*/

#include <cos/Stream.h>

#include <stdio.h>

// ----- private shared data structure

struct File_Descriptor_ {
  FILE *fp;
  OBJ   name;
  BOOL  own;
  U32   size;
  U32   pos;
  U32   max;
  U8   *buf;
};

// ----- File state machine

defclass(File, Stream)
  struct File_Descriptor_ fd;
endclass

defclass(InputFile, InputStream)
  struct File_Descriptor_ fd;
endclass

defclass(OutputFile, OutputStream)
  struct File_Descriptor_ fd;
endclass

defclass(InputOutputFile, InputFile)
endclass

defclass(OutputInputFile, OutputFile)
endclass

#endif // COS_FILE_H
