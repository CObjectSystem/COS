/**
 * C Object System
 * COS File
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cos/File.h>
#include <cos/String.h>

#include <cos/gen/collection.h>
#include <cos/gen/file.h>
#include <cos/gen/object.h>
#include <cos/gen/sequence.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

// ----- front-end / state machine

// directional files

makclass(InputFile , InputStream);
makclass(OutputFile, OutputStream);

// bi-directional files

makclass(InputOutputFile, InputFile);
makclass(OutputInputFile, OutputFile);

// -----

useclass(InputFile, OutputFile, InputOutputFile, OutputInputFile);
useclass(ExBadStream, ExBadAlloc, AutoRelease, Array, String);

// -----

STATIC_ASSERT(EndOfStream_value_differs_from_EOF, EndOfStream == EOF);

STATIC_ASSERT(IntputFile_vs_OutputFile__invalid_layout_compatibility,
              COS_FIELD_COMPATIBILITY(InputFile, OutputFile, fd));

// ----- constructors

static void
open_file(struct file_descriptor_ *fd, OBJ name, STR mode)
{
  fd->fp = fopen(gstr(name), mode);
  if (!fd->fp)
    THROW( gnewWith(ExBadStream, gconcat(aStr("unable to open file "), name)) );

  fd->own  = YES;
  fd->name = gretain(name);
}

defmethod(OBJ, ginitWith, InputFile, String)
  open_file(&self->fd, _2, "r");
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, OutputFile, String)
  open_file(&self->fd, _2, "w");
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, InputOutputFile, String)
  open_file(&self->InputFile.fd, _2, "r+");
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, OutputInputFile, String)
  open_file(&self->OutputFile.fd, _2, "w+");
  retmethod(_1);
endmethod

// ----- destructors

static void
close_file(struct file_descriptor_ *fd)
{
  if (fd->fp) {
    if (fd->own)
      fclose(fd->fp), fd->own = NO;
    else
      fflush(fd->fp);
    fd->fp = 0;
  }

  if (fd->name)
    grelease(fd->name), fd->name = 0;
}

defmethod(OBJ, gdeinit, InputFile)
  close_file(&self->fd);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, OutputFile)
  close_file(&self->fd);
  retmethod(_1);
endmethod

// ----- flush

defmethod(OBJ, gflush, InputFile)
  retmethod(_1);
endmethod

defmethod(OBJ, gflush, OutputFile)
  if (fflush(self->fd.fp))
    THROW( gnewWith(ExBadStream, gconcat(aStr("unable to flush file "), self->fd.name)) );

  retmethod(_1);
endmethod

// ----- empty

defmethod(OBJ, gisEmpty, InputFile)
  retmethod(feof(self->fd.fp) ? True : False);
endmethod

defmethod(OBJ, gisEmpty, OutputFile)
  retmethod(feof(self->fd.fp) ? True : False);
endmethod

// ----- name

defmethod(STR, gstr, OutputFile)
  retmethod( gstr(self->fd.name) );
endmethod

defmethod(STR, gstr, InputFile)
  retmethod( gstr(self->fd.name) );
endmethod

// ----- read/write primitives

defmethod(I32, ggetChr, InputFile)
  retmethod( getc(self->fd.fp) );
endmethod

defmethod(I32, gungetChr, InputFile, (I32)chr)
  retmethod( ungetc(chr, self->fd.fp) );
endmethod

defmethod(I32, gputChr, OutputFile, (I32)chr)
  retmethod( putc(chr, self->fd.fp) );
endmethod

// ----- file position

defmethod(int, gseek, InputFile, (long)pos, (int)from)
  retmethod( fseek(self->fd.fp, pos, from) );
endmethod

defmethod(int, gseek, OutputFile, (long)pos, (int)from)
  retmethod( fseek(self->fd.fp, pos, from) );
endmethod

defmethod(long, gtell, InputFile);
  retmethod( ftell(self->fd.fp) );
endmethod

defmethod(long, gtell, OutputFile);
  retmethod( ftell(self->fd.fp) );
endmethod

// ----- get file (low-level)

defmethod(FILE*, ggetFILE, OutputFile)
  retmethod(self->fd.fp);
endmethod

defmethod(FILE*, ggetFILE, InputFile)
  retmethod(self->fd.fp);
endmethod

// ----- init with file (low-level)

defmethod(OBJ, ginitWithFILE, InputFile, (FILE*)fp, String)
PRE
  ensure(fp, "null file descriptor");

BODY
  self->fd.fp   = fp;
  self->fd.own  = NO;
  self->fd.name = gretain(_2);

  retmethod(_1);
endmethod

defmethod(OBJ, ginitWithFILE, OutputFile, (FILE*)fp, String)
PRE
  ensure(fp, "null file descriptor");

BODY
  self->fd.fp   = fp;
  self->fd.own  = NO;
  self->fd.name = gretain(_2);

  retmethod(_1);
endmethod

// ----- StdIn, StdOut, StdErr, StdLog

OBJ StdIn=0, StdOut=0, StdErr=0, StdLog=0;

defmethod(void, (ginitialize)StdioInit, Any)
  if (!StdIn ) StdIn  = ginitWithFILE(galloc(InputFile) , stdin , aStr("stdin" ));
  if (!StdOut) StdOut = ginitWithFILE(galloc(OutputFile), stdout, aStr("stdout"));
  if (!StdErr) StdErr = ginitWithFILE(galloc(OutputFile), stderr, aStr("stderr"));
  if (!StdLog) StdLog = ginitWithFILE(galloc(OutputFile), stderr, aStr("stdlog"));
endmethod

defmethod(void, (gdeinitialize)StdioDeinit, Any)
  if (StdIn ) grelease(StdIn ), StdIn  = 0;
  if (StdOut) grelease(StdOut), StdOut = 0;
  if (StdErr) grelease(StdErr), StdErr = 0;
  if (StdLog) grelease(StdLog), StdLog = 0;
endmethod

