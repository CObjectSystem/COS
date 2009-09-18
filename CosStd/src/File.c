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
 | $Id: File.c,v 1.5 2009/09/18 16:42:30 ldeniau Exp $
 |
*/

#include <cos/File.h>
#include <cos/Number.h>
#include <cos/String.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

// -----

makclass(File,Stream);

makclass(OpenFile  ,File);
makclass(ClosedFile,File);

// -----

useclass(File, ClosedFile);
useclass(ExBadStream);

// -----

STATIC_ASSERT(OpenFile_vs_ClosedFile__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(OpenFile,ClosedFile,fd)
           && COS_FIELD_COMPATIBILITY(OpenFile,ClosedFile,own)
           && COS_FIELD_COMPATIBILITY(OpenFile,ClosedFile,name)
           && COS_FIELD_COMPATIBILITY(OpenFile,ClosedFile,buf_size)
           && COS_FIELD_ALIGNMENT    (OpenFile,ClosedFile,file_buf) );

// ----- some constant

#ifndef FILE_BUFSIZ
#define FILE_BUFSIZ (64*1024)
#endif

STATIC_ASSERT(FILE_BUFSIZ_is_too_small, FILE_BUFSIZ >= BUFSIZ);

// ----- properties

defproperty(OpenFile, name, );

// ----- allocator

defmethod(OBJ, galloc, pmFile)
  retmethod(_1); // lazy alloc
endmethod

// ----- cluster constructors

defalias (OBJ, (ginit)gnew, pmFile);
defmethod(OBJ,  ginit     , pmFile)
  PRE POST BODY
    retmethod( ginitWith(gallocWithSize(ClosedFile, FILE_BUFSIZ), aInt(FILE_BUFSIZ)) );
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmFile, Int);
defmethod(OBJ,  ginitWith         , pmFile, Int)
  PRE
    test_assert(self2->value >= 0, "negative file buffer size");
  POST
  BODY
    retmethod( ginitWith(gallocWithSize(ClosedFile, self2->value), _2) );
endmethod

// ----- initializers

defmethod(OBJ, ginitWith, ClosedFile, Int)
  self->fd = 0;
  self->own = NO;
  self->name = 0;
  self->buf_size = self2->value;
  retmethod(_1);
endmethod

// ----- destructors

defmethod(OBJ, gdeinit, OpenFile)
  if (self->fd && self->own)
    fclose(self->fd);

  if (self->name)
    grelease(self->name);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, ClosedFile)
  retmethod(_1);
endmethod

// ----- invariants

defmethod(void, ginvariant, ClosedFile, (STR)func, (STR)file, (int)line)
  test_assert(!self->fd  , "ClosedFile has a file descriptor", func, file, line);
  test_assert(!self->own , "ClosedFile own a file descriptor", func, file, line);
  test_assert(!self->name, "ClosedFile has a file name"      , func, file, line);
endmethod

defmethod(void, ginvariant, OpenFile, (STR)func, (STR)file, (int)line)
  test_assert(self->fd  , "OpenFile hasn't a file descriptor", func, file, line);
  test_assert(self->name, "OpenFile hasn't a file name"      , func, file, line);
endmethod

// ----- open, close, flush, gisEmpty, remove

defmethod(OBJ, gopen, ClosedFile, String, String)
  BOOL ch_cls;
  BOOL ch_buf;

  PRE
  POST
    test_assert(ch_buf, "unable to set file buffer");
    test_assert(ch_cls, "unable to change from ClosedFile to OpenFile");

  BODY
    self->fd = fopen(gstr(_2), gstr(_3));
    if (!self->fd)
      THROW( gnewWith(ExBadStream, gcat(aStr("unable to open file "), _2)) );

    self->own = YES;
    self->name = gretain(_2);
    ch_buf = !setvbuf(self->fd, self->file_buf, _IOFBF, self->buf_size);
    ch_cls = cos_object_unsafeChangeClass(_1, classref(OpenFile), classref(File));

    retmethod(_1);
endmethod

defmethod(void, gclose, OpenFile)
  BOOL ch_cls;

  PRE
  POST
    test_assert(ch_cls, "unable to change from OpenFile to ClosedFile");

  BODY
    ch_cls = cos_object_unsafeChangeClass(_1, classref(ClosedFile), classref(File));
    
    if (fclose(self->fd))
      THROW( gnewWith(ExBadStream, gcat(aStr("unable to close file "), self->name)) );

    grelease(self->name);

    self->fd  = 0;
    self->own = NO;
    self->name = 0;
endmethod

defmethod(void, gflush, OpenFile)
  if (fflush(self->fd))
    THROW( gnewWith(ExBadStream, gcat(aStr("unable to flush file "), self->name)) );
endmethod

defmethod(OBJ, gisEmpty, OpenFile)
  retmethod(feof(self->fd) ? True : False);
endmethod

defmethod(void, gremove, OpenFile)
  OBJ name = gretain(self->name); PRT(name);
  gclose(_1);

  if (remove(gstr(name)))
    THROW( gnewWith(ExBadStream, gcat(aStr("unable to remove file "), name)) );

  UNPRT(name);
  grelease(name);
endmethod

// ----- generic putLn

defmethod(OBJ, gputLn, OpenFile, Object)
  int err = gput(_1,_2) != True || putc('\n', self->fd) == EOF;
  
  retmethod(err ? False : True);
endmethod

// ----- get/set file (low-level)

defmethod(FILE*, ggetFILE, OpenFile)
  retmethod(self->fd);
endmethod

defmethod(void, gsetFILE, ClosedFile, (FILE*)fd, (STR)tag)
  BOOL ch_cls = ch_cls; // NOTE-INFO: remove (justified) warning

  PRE
    test_assert(fd , "null file descriptor");
    test_assert(tag, "null file tag");

  POST
    test_assert(ch_cls, "unable to change from ClosedFile to OpenFile");

  BODY
    self->fd   = fd;
    self->own  = NO;
    self->name = gretain(aString(tag));
    ch_cls = cos_object_unsafeChangeClass(_1, classref(OpenFile), classref(File));
endmethod

// ----- StdIn, StdOut, StdErr

OBJ StdIn, StdOut, StdErr;

defmethod(void, ginitialize, pmFile)
  if (!StdIn) {
    gsetFILE(StdIn  = gnew(File), stdin , "stdin" );
    gsetFILE(StdOut = gnew(File), stdout, "stdout");
    gsetFILE(StdErr = gnew(File), stderr, "stderr");
  }
endmethod

defmethod(void, gdeinitialize, pmFile)
  if (StdIn) {
    gdelete(StdIn);
    gdelete(StdOut);
    gdelete(StdErr);
  }
endmethod

