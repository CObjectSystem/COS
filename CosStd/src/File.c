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
 | $Id: File.c,v 1.16 2010/01/21 14:52:54 ldeniau Exp $
 |
*/

#include <cos/File.h>
#include <cos/Functor.h>
#include <cos/Number.h>
#include <cos/String.h>

#include <cos/gen/algorithm.h>
#include <cos/gen/collection.h>
#include <cos/gen/file.h>
#include <cos/gen/functor.h>
#include <cos/gen/message.h>
#include <cos/gen/new.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

// -----

// closed files

makclass(ClosedFile, ClosedStream);

// directional files

makclass(InputFile , InputStream);
makclass(OutputFile, OutputStream);

// bi-directional files

makclass(InputOutputFile, InputFile);
makclass(OutputInputFile, OutputFile);

// -----

useclass(File, ClosedFile, InputOutputFile, OutputInputFile);
useclass(ExBadStream, AutoRelease, Array, String);

// -----

STATIC_ASSERT(OpenFile_vs_ClosedFile__invalid_layout_compatibility,
     COS_FIELD_COMPATIBILITY(OpenFile    , ClosedFile, fd)
  && COS_FIELD_COMPATIBILITY(OpenFile    , ClosedFile, own)
  && COS_FIELD_COMPATIBILITY(OpenFile    , ClosedFile, name)
  && COS_FIELD_COMPATIBILITY(OpenFile    , ClosedFile, buf_size)
  && COS_FIELD_ALIGNMENT    (InputOutputFile   , ClosedFile, file_buf)
  && COS_FIELD_ALIGNMENT    (OutputInputFile   , ClosedFile, file_buf)
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
  retmethod( ginitWith(gallocWithSize(ClosedFile, FILE_BUFSIZ), aInt(FILE_BUFSIZ)) );
endmethod

defalias (OBJ, (ginitWith)gnewWith, pmFile, Int);
defmethod(OBJ,  ginitWith         , pmFile, Int)
  PRE
    test_assert(self2->value >= 0, "negative file buffer size");
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
  case READ:                 return classref(InputFile);
  case READ | BINARY:        return classref(InBinFile);
  case READ | BOTH:          return classref(InputOutputFile);
  case READ | BOTH | BINARY: return classref(InOutBinFile);

  case WRITE:                 return classref(OutputFile);
  case WRITE | BINARY:        return classref(OutBinFile);
  case WRITE | BOTH:          return classref(OutputInputFile);
  case WRITE | BOTH | BINARY: return classref(OutInBinFile);

  default : test_assert(0, "invalid file mode"); return 0;
  }
}

defmethod(OBJ, gopen, ClosedFile, String, String)
  STR mode = gstr(_3);
  self->fd = fopen(gstr(_2), mode);
  if (!self->fd)
    THROW( gnewWith(ExBadStream, gconcat(aStr("unable to open file "), _2)) );

  self->own = YES;
  self->name = gretain(_2);
  BOOL ch_buf = !setvbuf(self->fd, self->file_buf, _IOFBF, self->buf_size);
  test_assert(ch_buf, "unable to set file buffer");
  
  struct Class *cls = mode2class(mode);
  BOOL ch_cls = cos_object_unsafeChangeClass(_1, cls, classref(File));
  test_assert(ch_cls, "unable to change from ClosedFile to OpenFile");

  retmethod(_1);
endmethod

defmethod(OBJ, gclose, OpenFile)
  BOOL ch_cls = cos_object_unsafeChangeClass(_1, classref(ClosedFile), classref(File));
  test_assert(ch_cls, "unable to change from OpenFile to ClosedFile");

  if (fclose(self->fd))
    THROW( gnewWith(ExBadStream, gconcat(aStr("unable to close file "), self->name)) );

  grelease(self->name);

  self->fd = 0;
  self->own = NO;
  self->name = 0;
  
  retmethod(_1);
endmethod

// ----- flush

defmethod(OBJ, gflush, InputFile)
  // no flush on input file
  retmethod(_1);
endmethod

defmethod(OBJ, gflush, OutputFile)
  struct OpenFile *file = &self->OpenFile;

  if (fflush(file->fd))
    THROW( gnewWith(ExBadStream, gconcat(aStr("unable to flush file "), file->name)) );

  retmethod(_1);
endmethod

// ----- empty

defmethod(OBJ, gisEmpty, OpenFile)
  retmethod(feof(self->fd) ? True : False);
endmethod

// ----- remove

defmethod(OBJ, gremove, OpenFile)
  OBJ name = gretain(self->name); PRT(name);
  gclose(_1);

  if (remove(gstr(name)))
    THROW( gnewWith(ExBadStream, gconcat(aStr("unable to remove file "), name)) );

  UNPRT(name);
  grelease(name);
  retmethod(_1);
endmethod

// ----- name

defmethod(STR, gstr, OpenFile)
  retmethod(gstr(self->name));
endmethod

// ----- read primitives

defmethod(I32, ggetChr, InputFile)
  retmethod( getc(self->OpenFile.fd) );
endmethod

defmethod(I32, gputChr, OutputFile, (I32)chr)
  retmethod( putc(chr, self->OpenFile.fd) );
endmethod

defmethod(I32, gungetChr, OutputFile, (I32)chr)
  retmethod( ungetc(chr, self->OpenFile.fd) );
endmethod

defmethod(size_t, ggetData, InputFile, (U8*)buf, (size_t)len)
  retmethod( fread(buf, 1, len, self->OpenFile.fd) );
endmethod

defmethod(size_t, gputData, OutputFile, (U8*)buf, (size_t)len)
  retmethod( fwrite(buf, 1, len, self->OpenFile.fd) );
endmethod

defmethod(size_t, ggetDelim, InputFile, (U8*)buf, (size_t)len, (I32)delim)
  FILE *fd = self->OpenFile.fd;
  U32 n = 0;
  I32 c;
  
  while (n < len && (c = getc(fd)) != EOF && c != delim)
    buf[n++] = (U32)c;

  retmethod( n );
endmethod

defmethod(size_t, ggetLine, InputFile, (U8*)buf, (size_t)len)
  FILE *fd = self->OpenFile.fd;
  U32 n = 0;
  I32 c, c2;
  
  while (n < len && (c = getc(fd)) != EOF) {
    if (c == '\n') {
      if ((c2 = getc(fd)) != EOF && c2 != '\r') ungetc(c2, fd);
      break;
    }
    
    if (c == '\r') {
      if ((c2 = getc(fd)) != EOF && c2 != '\n') ungetc(c2, fd);
      break;
    }

    buf[n++] = (U32)c;
  }

  retmethod( n );
endmethod

// ----- generic get type

defmethod(OBJ, gget, InputFile, Class)
  forward_message(_1, gautoDelete(gnew(_2)));
endmethod

// ----- generic putLn

defmethod(OBJ, gputLn, OutputFile, Object)
  FILE *fd = self->OpenFile.fd;
  int err;

  err = gput(_1,_2) != True || putc('\n', fd) == EOF;
  
  retmethod(err ? False : True);
endmethod

// ----- generic mapWhile

defmethod(void, gforeachWhile, OpenFile, Functor)
  while (!feof(self->fd) && geval(_2,_1) != Nil) ;
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

defmethod(OBJ, gsetFILE, ClosedFile, (FILE*)fd, (STR)mode, (STR)name)
  PRE
    test_assert(fd  , "null file descriptor");
    test_assert(name, "null file name");
    test_assert(mode, "null file mode");

  BODY
    self->fd   = fd;
    self->own  = NO;
    self->name = gretain(gautoDelete(gnewWithStr(String, name)));

    struct Class *cls = mode2class(mode);
    BOOL ch_cls = cos_object_unsafeChangeClass(_1, cls, classref(File));
    test_assert(ch_cls, "unable to change from ClosedFile to OpenFile");

    retmethod(_1);
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

