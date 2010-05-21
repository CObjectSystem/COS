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
 | $Id: File.c,v 1.21 2010/05/21 14:59:09 ldeniau Exp $
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
#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

#include <cos/prp/object.h>

// ----- front-end / state machine

// 'closed' files

makclass(File, Stream);

// directional files

makclass(InputFile , InputStream);
makclass(OutputFile, OutputStream);

// bi-directional files

makclass(InputOutputFile, InputFile);
makclass(OutputInputFile, OutputFile);

// -----

useclass(File, InputFile, OutputFile, InputOutputFile, OutputInputFile);
useclass(ExBadStream, ExBadAlloc, AutoRelease, Array, String);

// -----

STATIC_ASSERT(EndOfStream_value_differs_from_EOF, EndOfStream == EOF);

STATIC_ASSERT(IntputFile_vs_File__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(InputFile, File, fd));

STATIC_ASSERT(OutputFile_vs_File__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(OutputFile, File, fd));

// ----- constructors

defmethod(OBJ, ginit, File)
  retmethod( ginitWith(_1, aInt(BUFSIZ)) );
endmethod

defmethod(OBJ, ginitWith, File, Int)
PRE
  test_assert(self2->value >= 0, "negative file buffer size");
POST
BODY
  defnext(OBJ, ginit, File);

  self->fd.fp   = 0;
  self->fd.name = 0;
  self->fd.own  = NO;
  self->fd.size = self2->value;
  self->fd.pos  = 0;
  self->fd.max  = 0;
  self->fd.buf  = 0;

  next_method(self);
endmethod

// ----- destructors

defmethod(OBJ, gdeinit, File)
  if (self->fd.buf)
    free(self->fd.buf), self->fd.buf = 0;
  
  next_method(self);
endmethod

defmethod(OBJ, gdeinit, InputFile)
  gclose(_1);
  next_method(self); // gdeinit(File)
endmethod

defmethod(OBJ, gdeinit, OutputFile)
  gclose(_1);
  next_method(self); // gdeinit(File)
endmethod

// ----- invariants

defmethod(void, ginvariant, InputFile, (STR)func, (STR)file, (int)line)
  test_assert(self->fd.fp  , "InputFile hasn't a FILE descriptor", func, file, line);
  test_assert(self->fd.name, "InputFile hasn't a file name"      , func, file, line);
  test_assert(self->InputStream.Stream.delegate == 0,
                             "InputFile has a delegate (ignored)", func, file, line);
endmethod

defmethod(void, ginvariant, OutputFile, (STR)func, (STR)file, (int)line)
  test_assert(self->fd.fp  , "OutputFile hasn't a FILE descriptor", func, file, line);
  test_assert(self->fd.name, "OutputFile hasn't a file name"      , func, file, line);
  test_assert(self->OutputStream.Stream.delegate == 0,
                             "OutputFile has a delegate (ignored)", func, file, line);
endmethod

// ----- open, close, flush, gisEmpty, remove

static struct Class*
mode2class(STR str, U32 *mode, STR file, int line)
{
  enum { INVALID=0, READ=1, WRITE=2, BOTH=4, BINARY=8, TEXT=16, APPEND=32 };
  struct Class *cls = 0;
  U32 m = 0;

  while (*str)
    switch (*str++) {
    case 'a': m |= APPEND; break;
    case 'b': m |= BINARY; break;
    case 't': m |= TEXT;   break;
    case 'r': m |= READ;   break;
    case 'w': m |= WRITE;  break;
    case '+': m |= BOTH;   break;
    default : test_assert(0, "invalid file mode", file, line);
    }

  if (mode) *mode = m;

  switch(m & (READ|WRITE|BOTH)) {
  case READ:         cls = classref(InputFile);       break;
  case WRITE:        cls = classref(OutputFile);      break;
  case READ  | BOTH: cls = classref(InputOutputFile); break;
  case WRITE | BOTH: cls = classref(OutputInputFile); break;
  }
  
  return cls;
}

defmethod(OBJ, gopen, File, String, String)
  struct File_Descriptor_ *fd = &self->fd;
  STR mode_str = gstr(_3);
  U32 mode;

  struct Class *cls = mode2class(mode_str, &mode, __FILE__, __LINE__);

  fd->fp = fopen(gstr(_2), mode_str);
  if (!fd->fp)
    THROW( gnewWith(ExBadStream, gconcat(aStr("unable to open file "), _2)) );

  fd->own  = YES;
  fd->name = gretain(_2);

  if (fd->size != BUFSIZ) {
    BOOL chg = !setvbuf(fd->fp, 0, _IOFBF, fd->size);
    test_assert(chg, "unable to set file buffer");
  }
  
  BOOL chg = cos_object_unsafeChangeClass(_1, cls, classref(Stream));
  test_assert(chg, "unable to change from 'closed' File to InputFile/OutputFile");

  retmethod(_1);
endmethod

static void
close_fd(struct File_Descriptor_ *fd) {
  if (fd->fp && fd->own)
    fclose(fd->fp), fd->fp = 0, fd->own = NO;

  if (fd->name)
    grelease(fd->name), fd->name = 0;
    
  fd->own = NO;
}

defmethod(OBJ, gclose, InputFile)
  gflush(_1);
  close_fd(&self->fd);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(File), classref(Stream));
  test_assert(chg, "unable to change from InputFile to 'closed' File");

  retmethod(_1);
endmethod

defmethod(OBJ, gclose, OutputFile)
  gflush(_1);
  close_fd(&self->fd);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(File), classref(Stream));
  test_assert(chg, "unable to change from OutputFile to 'closed' File");

  retmethod(_1);
endmethod

// ----- flush

defmethod(OBJ, gflush, InputFile)
  retmethod(_1);
endmethod

defmethod(OBJ, gflush, OutputFile)
  if (fflush(self->fd.fp))
    THROW( gnewWith(ExBadStream,
             gconcat(aStr("unable to flush file "), self->fd.name)) );

  retmethod(_1);
endmethod

// ----- empty

defmethod(OBJ, gisEmpty, InputFile)
  retmethod(feof(self->fd.fp) ? True : False);
endmethod

defmethod(OBJ, gisEmpty, OutputFile)
  retmethod(feof(self->fd.fp) ? True : False);
endmethod

// ----- remove

defmethod(OBJ, gremove, File)
  OBJ name = gretain(self->fd.name); PRT(name);
  gclose(_1);

  if (remove(gstr(name)))
    THROW( gnewWith(ExBadStream, gconcat(aStr("unable to remove file "), name)) );

  UNPRT(name);
  grelease(name);
  retmethod(_1);
endmethod

// ----- name

defmethod(STR, gstr, OutputFile)
  retmethod(gstr(self->fd.name));
endmethod

defmethod(STR, gstr, InputFile)
  retmethod(gstr(self->fd.name));
endmethod

// ----- read primitives

defmethod(I32, ggetChr, InputFile)
  struct File_Descriptor_ *fd = &self->fd;

  retmethod( fd->pos ? fd->buf[--fd->pos] : getc(fd->fp) );
endmethod

defmethod(I32, gungetChr, InputFile, (I32)chr)
  if (chr == EndOfStream)
    retmethod(chr);

  struct File_Descriptor_ *fd = &self->fd;

  if (fd->pos == fd->max) {
    U32 max = fd->max ? fd->max*2 : 64;
    U8 *buf = realloc(fd->buf, max);
    if (!buf) THROW(ExBadAlloc); 
    fd->buf = buf;
    fd->max = max;
  }

  retmethod( fd->buf[fd->pos++] = (U32)chr );
endmethod

defmethod(I32, gputChr, OutputFile, (I32)chr)
  retmethod( putc(chr, self->fd.fp) );
endmethod

// ----- get/set file (low-level)

defmethod(FILE*, ggetFILE, OutputFile)
  retmethod(self->fd.fp);
endmethod

defmethod(FILE*, ggetFILE, InputFile)
  retmethod(self->fd.fp);
endmethod

defmethod(OBJ, gsetFILE, File, (FILE*)fp, (STR)mode, (STR)name)
PRE
  test_assert(fp  , "null file descriptor");
  test_assert(name, "null file name");
  test_assert(mode, "null file mode");

BODY
  struct Class *cls = mode2class(mode, 0, __FILE__, __LINE__);

  self->fd.fp   = fp;
  self->fd.own  = NO;
  self->fd.name = gretain(gautoDelete(gnewWithStr(String, name)));

  BOOL chg = cos_object_unsafeChangeClass(_1, cls, classref(Stream));
  test_assert(chg, "unable to change from 'closed' File to InputFile/OutputFile");

  retmethod(_1);
endmethod

// ----- StdIn, StdOut, StdErr, StdLog

OBJ StdIn=0, StdOut=0, StdErr=0, StdLog=0;

defmethod(void, ginitialize, pmFile)
  if (!StdIn) {
    gsetFILE(StdIn  = gnew(File), stdin , "r", "stdin" );
    gsetFILE(StdOut = gnew(File), stdout, "w", "stdout");
    gsetFILE(StdErr = gnew(File), stderr, "w", "stderr");
    gsetFILE(StdLog = gnew(File), stderr, "w", "stdlog");
  }
endmethod

defmethod(void, gdeinitialize, pmFile)
  if (StdIn) {
    gdelete(StdIn);
    gdelete(StdOut);
    gdelete(StdErr);
    gdelete(StdLog);
  }
endmethod

