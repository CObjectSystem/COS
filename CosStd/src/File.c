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
 | $Id: File.c,v 1.9 2009/09/30 12:09:58 ldeniau Exp $
 |
*/

#include <cos/File.h>
#include <cos/Functor.h>
#include <cos/Number.h>
#include <cos/String.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/functor.h>
#include <cos/gen/message.h>
#include <cos/gen/new.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

// -----

makclass(File, Stream);

makclass(ClosedFile,     File);
makclass(  OpenFile,     File);

// text file

makclass(    InFile, OpenFile);
makclass(   OutFile, OpenFile);
makclass( InOutFile,   InFile);
makclass( OutInFile,  OutFile);

// binary file

makclass(    InBinFile,     InFile);
makclass(   OutBinFile,    OutFile);
makclass( InOutBinFile,  InBinFile);
makclass( OutInBinFile, OutBinFile);

// -----

useclass(File, ClosedFile, InOutFile, OutInFile, InOutBinFile, OutInBinFile);
useclass(ExBadStream, AutoRelease, Array, String);

// -----

STATIC_ASSERT(OpenFile_vs_ClosedFile__invalid_layout_compatibility,
     COS_FIELD_COMPATIBILITY(OpenFile    , ClosedFile, fd)
  && COS_FIELD_COMPATIBILITY(OpenFile    , ClosedFile, own)
  && COS_FIELD_COMPATIBILITY(OpenFile    , ClosedFile, name)
  && COS_FIELD_COMPATIBILITY(OpenFile    , ClosedFile, buf_size)
  && COS_FIELD_ALIGNMENT    (InOutFile   , ClosedFile, file_buf)
  && COS_FIELD_ALIGNMENT    (OutInFile   , ClosedFile, file_buf)
  && COS_FIELD_ALIGNMENT    (InOutBinFile, ClosedFile, file_buf)
  && COS_FIELD_ALIGNMENT    (OutInBinFile, ClosedFile, file_buf)
);

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

defmethod(OBJ, gdeinit, ClosedFile)
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, OpenFile)
  if (self->fd && self->own)
    fclose(self->fd);

  if (self->name)
    grelease(self->name);

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

static struct Class*
mode2class(STR str)
{
  enum { INVALID=0, READ=1, WRITE=2, BOTH=4, BINARY=8 };
  unsigned m = INVALID;

  while (*str)
    switch (*str++) {
    case 'r': m |= READ;   break;
    case 'a':
    case 'w': m |= WRITE;  break;
    case 'b': m |= BINARY; break;
    case '+': m |= BOTH;   break;
    }

  switch(m) {
  case READ:                 return classref(InFile);
  case READ | BINARY:        return classref(InBinFile);
  case READ | BOTH:          return classref(InOutFile);
  case READ | BOTH | BINARY: return classref(InOutBinFile);

  case WRITE:                 return classref(OutFile);
  case WRITE | BINARY:        return classref(OutBinFile);
  case WRITE | BOTH:          return classref(OutInFile);
  case WRITE | BOTH | BINARY: return classref(OutInBinFile);

  default : test_assert(0, "invalid file mode"); return 0;
  }
}

defmethod(OBJ, gopen, ClosedFile, String, String)
  BOOL ch_cls;
  BOOL ch_buf;

  PRE
  POST
    test_assert(ch_buf, "unable to set file buffer");
    test_assert(ch_cls, "unable to change from ClosedFile to OpenFile");

  BODY
    STR mode = gstr(_3);
    self->fd = fopen(gstr(_2), mode);
    if (!self->fd)
      THROW( gnewWith(ExBadStream, gcat(aStr("unable to open file "), _2)) );

    self->own = YES;
    self->name = gretain(_2);
    ch_buf = !setvbuf(self->fd, self->file_buf, _IOFBF, self->buf_size);
    
    struct Class *cls = mode2class(mode);
    ch_cls = cos_object_unsafeChangeClass(_1, cls, classref(File));

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

    self->fd = 0;
    self->own = NO;
    self->name = 0;
endmethod

// ----- flush

defmethod(void, gflush, InFile)
  // no flush on input file
endmethod

defmethod(void, gflush, OutFile)
  struct OpenFile *file = &self->OpenFile;

  if (fflush(file->fd))
    THROW( gnewWith(ExBadStream, gcat(aStr("unable to flush file "), file->name)) );
endmethod

// ----- empty

defmethod(OBJ, gisEmpty, OpenFile)
  retmethod(feof(self->fd) ? True : False);
endmethod

// ----- remove

defmethod(void, gremove, OpenFile)
  OBJ name = gretain(self->name); PRT(name);
  gclose(_1);

  if (remove(gstr(name)))
    THROW( gnewWith(ExBadStream, gcat(aStr("unable to remove file "), name)) );

  UNPRT(name);
  grelease(name);
endmethod

// ----- primitives

defmethod(I32, ggetChr, InFile)
  retmethod( getc(self->OpenFile.fd) );
endmethod

defmethod(I32, gputChr, OutFile, (I32)chr)
  retmethod( putc(chr, self->OpenFile.fd) );
endmethod

defmethod(I32, gungetChr, OutFile, (I32)chr)
  retmethod( ungetc(chr, self->OpenFile.fd) );
endmethod

// ----- generic get, getLine, getData

defalias (OBJ, (gget)ggetLine, InFile, Class);
defalias (OBJ, (gget)ggetData, InFile, Class);
defmethod(OBJ,  gget         , InFile, Class)
  OBJ obj = gautoDelete(gnew(_2));
  
  forward_message(_1, obj);

  if (gunderstandMessage1(obj, genericref(gadjust)) == True)
    gadjust(obj);

  retmethod(RETVAL == True ? obj : Nil);
endmethod

// ----- generic putLn

defmethod(OBJ, gputLn, OutFile, Object)
  int err = gput(_1,_2) != True || putc('\n', self->OpenFile.fd) == EOF;
  
  retmethod(err ? False : True);
endmethod

// ----- generic mapWhile

defmethod(void, gapplyWhile, Functor, OpenFile)
  while (!feof(self2->fd) && geval(_1,_2) != Nil) ;
endmethod

defmethod(OBJ, gmapWhile, Functor, OpenFile)
  OBJ recs = gautoDelete(gnew(Array));
  OBJ res;

  while (!feof(self2->fd) && (res = geval(_1,_2)) != Nil)
    gpush(recs, res);

  retmethod(gadjust(recs));
endmethod

// ----- get/set file (low-level)

defmethod(FILE*, ggetFILE, OpenFile)
  retmethod(self->fd);
endmethod

defmethod(void, gsetFILE, ClosedFile, (FILE*)fd, (STR)mode, (STR)name)
  BOOL ch_cls = ch_cls; // NOTE-INFO: remove (justified) warning

  PRE
    test_assert(fd  , "null file descriptor");
    test_assert(name, "null file name");
    test_assert(mode, "null file mode");

  POST
    test_assert(ch_cls, "unable to change from ClosedFile to OpenFile");

  BODY
    self->fd   = fd;
    self->own  = NO;
    self->name = gretain(gautoDelete(gnewWithStr(String, name)));

    struct Class *cls = mode2class(mode);
    ch_cls = cos_object_unsafeChangeClass(_1, cls, classref(File));
endmethod

// ----- StdIn, StdOut, StdErr

OBJ StdIn, StdOut, StdErr;

defmethod(void, ginitialize, pmFile)
  if (!StdIn) {
    gsetFILE(StdIn  = gnew(File), stdin , "r", "stdin" );
    gsetFILE(StdOut = gnew(File), stdout, "w", "stdout");
    gsetFILE(StdErr = gnew(File), stderr, "w", "stderr");
  }
endmethod

defmethod(void, gdeinitialize, pmFile)
  if (StdIn) {
    gdelete(StdIn);
    gdelete(StdOut);
    gdelete(StdErr);
  }
endmethod

