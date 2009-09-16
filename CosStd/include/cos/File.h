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
 | $Id: File.h,v 1.2 2009/09/16 17:02:56 ldeniau Exp $
 |
*/

#include <cos/Stream.h>

defclass(File,Stream)
endclass

/***********************************************************
 * Implementation (private)
 */

#include <stdio.h>

// ----- File state machine

defclass(OpenFile,File) // final class
  FILE *fd;
  BOOL  own;
  OBJ   name;
  U32   buf_size;
  char  file_buf[];
endclass

defclass(ClosedFile,File) // final class
  FILE *fd;
  BOOL  own;
  OBJ   name;
  U32   buf_size;
  char  file_buf[];
endclass

#endif // COS_FILE_H
