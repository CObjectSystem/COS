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
 | $Id: File.c,v 1.1 2009/09/14 13:35:15 ldeniau Exp $
 |
*/

#include <cos/File.h>
#include <cos/Number.h>
#include <cos/String.h>

#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

// -----

makclass(File,Stream);

makclass(OpenFile  ,File);
makclass(ClosedFile,File);

// -----

useclass(ClosedFile);

// -----

STATIC_ASSERT(OpenFile_vs_ClosedFile__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(OpenFile,ClosedFile,fd) );

// ----- allocator

defmethod(OBJ, galloc, pmFile)
  retmethod(_1); // lazy alloc
endmethod

// ----- constructors

defalias (OBJ, (ginit)gnew, pmFile);
defmethod(OBJ,  ginit     , pmFile)
  retmethod(gnew(ClosedFile));
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmFile, Int);
defmethod(OBJ,  ginitWith         , pmFile, Int)
  PRE
    test_assert(self2->value >= 0, "negative file buffer size");
  POST BODY
    retmethod(ginitWith(gallocWithSize(ClosedFile, self2->value), _2));
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, pmFile, String, String);
defmethod(OBJ,  ginitWith2          , pmFile, String, String)
  retmethod(gnewWith2(ClosedFile,_2,_3));
endmethod

// ----- initializers

defmethod(OBJ, ginit, ClosedFile)
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, ClosedFile, Int)
  self->fs = self2->value;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith2, ClosedFile, String, String)
  self->fd = fopen(gstr(_2), gstr(_3));
  test_assert( self->fd, "unable to open file");

  int done = cos_object_unsafeChangeClass(_1, classref(OpenFile), classref(File));
  test_assert( done, "unable to change from ClosedFile to OpenFile");

  if (self->fs) {
    int err = setvbuf(self->fd, self->fb, _IOFBF, self->fs);
    test_assert( !err, "unable to set file buffer");
  }

  retmethod(_1);
endmethod

// ----- destructors

defmethod(OBJ, gdeinit, OpenFile)
  if (self->fd) fclose(self->fd);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ClosedFile)
  retmethod(_1);
endmethod

// ----- open, close

defalias(OBJ, (ginitWith2)gopen, ClosedFile, String, String);

defmethod(OBJ, gclose, OpenFile)
  test_assert( fclose(self->fd), "unable to close file");
  self->fd = 0;

  int done = cos_object_unsafeChangeClass(_1, classref(ClosedFile), classref(File));
  test_assert( done, "unable to change from OpenFile to CloseFile");

  retmethod(_1);
endmethod

// ----- get, gets

defmethod(OBJ, gget, OpenFile, Char)
  self2->Int.value = fgetc(self->fd);
  
  retmethod(self2->Int.value == EOF ? False : True);
endmethod

defmethod(OBJ, gget, OpenFile, StringDyn)
  enum { N = 1024*sizeof(void*) };
  FILE *fd = self->fd;
  U8 str[N];

  while (1) {
    int c = 0, i = 0;
    
    while (i < N && (c = fgetc(fd)) != EOF) {
      if (c == '\n') {
        if ((c = fgetc(fd)) != EOF && c != '\r') ungetc(c, fd);
        break;
      }
      
      if (c == '\r') {
        if ((c = fgetc(fd)) != EOF && c != '\n') ungetc(c, fd);
        break;
      }

      str[i++] = (unsigned)c;
    }
    
    if (i) gappend(_2, aStringRef(str,i));
    
    if (c == EOF || c == '\n' || c == '\r')
      retmethod(c == EOF ? False : True);
  }
endmethod

defmethod(OBJ, ggetData, OpenFile, (void*)ref, (U32*)n)
  size_t size = *n;
  
  *n = fread(ref, 1, size, self->fd);

  retmethod(*n < size ? False : True);
endmethod

// ----- put, puts

defmethod(OBJ, gput, OpenFile, Char)
  retmethod(fputc(self2->Int.value, self->fd) == EOF ? False : True);
endmethod

defmethod(OBJ, gput, OpenFile, String)
  retmethod(fwrite(self2->value, 1, self2->size, self->fd) < self2->size ? False : True);
endmethod

defmethod(OBJ, gputData, OpenFile, (void*)ref, (U32*)n)
  size_t size = *n;

  *n = fwrite(ref, 1, size, self->fd);

  retmethod(*n < size ? False : True);
endmethod

