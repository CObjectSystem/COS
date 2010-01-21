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
 | $Id: File.h,v 1.6 2010/01/21 14:12:36 ldeniau Exp $
 |
*/

#include <cos/Stream.h>

/* NOTE-USER: File subclasses

<- InputStream
  <- InputFile

<- OutputStream
  <- OutputFile
*/

defclass(InputFile, InputStream)
endclass

defclass(OutputFile, OutputStream)
endclass

/***********************************************************
 * Implementation (private)
 */

#include <stdio.h>

// ----- File state machine

defclass(ClosedFile, File)
  FILE *fd;
  OBJ   name;
  BOOL  own;
  U32   buf_size;
  char  file_buf[];
endclass

defclass(OpenFile, File)
  FILE *fd;
  OBJ   name;
  BOOL  own;
  U32   buf_size;
endclass

// ----- text file

defclass(InFile , OpenFile)
endclass

defclass(OutFile, OpenFile)
endclass

defclass(InOutFile, InFile)
  char file_buf[];
endclass

defclass(OutInFile, OutFile)
  char file_buf[];
endclass

#endif // COS_FILE_H
