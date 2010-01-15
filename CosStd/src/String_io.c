/*
 o---------------------------------------------------------------------o
 |
 | COS String - strings IO
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
 | useful, but WITHOUT ANY WARRANTY; without even the implied wstranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: String_io.c,v 1.7 2010/01/15 23:50:13 ldeniau Exp $
 |
*/

#include <cos/String.h>
#include <cos/File.h>
#include <cos/Functor.h>
#include <cos/Number.h>

#include <cos/gen/container.h>
#include <cos/gen/message.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>
#include <cos/gen/value.h>

#include <ctype.h>

// ----- Binary File

defmethod(OBJ, gget, InBinFile, String)
  int res = fread(self2->value, self2->size, 1, self->InFile.OpenFile.fd) != 1;
  retmethod(res ? False : True);
endmethod

// ----- Text File

// ----- put

defmethod(OBJ, gput, OutFile, String)
  int res = fwrite(self2->value, self2->size, 1, self->OpenFile.fd) != 1;
  retmethod(res ? False : True);
endmethod

// ----- get string (stops on white spaces)

defmethod(OBJ, gget, InFile, StringDyn)
  PRE POST BODY
  struct StringFix *strf = &self2->StringFix;
  struct String    *str  = &strf->String;

  FILE *fd    = self->OpenFile.fd;
  U32  *val_n = &str->size;
  int   c;

  gclear(_2);

  // skip heading white spaces
  while ((c = getc(fd)) != EOF && isspace(c))
    ;

  while(1) {
    U8* val = str->value + str->size;
    U8* end = strf->_value + strf->capacity;
  
    while (val != end && (c = getc(fd)) != EOF && !isspace(c))
      *val++ = (unsigned)c, ++*val_n;

    if (c == EOF || isspace(c)) break;

    genlarge(_2, aInt(1));
  }

  retmethod(c == EOF ? False : True);
endmethod

// ----- getLine

defmethod(OBJ, ggetLine, InFile, StringDyn)
  PRE POST BODY
  struct StringFix *strf = &self2->StringFix;
  struct String    *str  = &strf->String;

  FILE *fd    = self->OpenFile.fd;
  U32  *val_n = &str->size;
  int   c     = 0;

  // clear
  str->size  = 0;
  str->value = strf->_value;

  while(1) {
    U8* val = str->value + str->size;
    U8* end = strf->_value + strf->capacity;
    int c2;
  
    while (val != end && (c = getc(fd)) != EOF) {
      if (c == '\n') {
        if ((c2 = getc(fd)) != EOF && c2 != '\r') ungetc(c2, fd);
        break;
      }
      if (c == '\r') {
        if ((c2 = getc(fd)) != EOF && c2 != '\n') ungetc(c2, fd);
        break;
      }
      *val++ = (unsigned)c, ++*val_n;
    }
    
    if (c == EOF || c == '\n' || c == '\r') break;

    genlarge(_2, aInt(1));
  }

  retmethod(c == EOF ? False : True);
endmethod

// ----- dynamic size getData

defmethod(OBJ, ggetData, InFile, StringDyn)
  PRE POST BODY
  struct StringFix *strf = &self2->StringFix;
  struct String    *str  = &strf->String;

  // clear
  str->size  = 0;
  str->value = strf->_value;

  // NOTE-TODO: check if stream is seekable and precompute the result size

  while(1) {
    U8* val = str->value + str->size;
    U8* end = strf->_value + strf->capacity;

    size_t n = fread(val, 1, end-val, self->OpenFile.fd);
        
    str->size += n;
    
    if (val + n < end) break;

    genlarge(_2, aInt(1));
  }

  retmethod(False);
endmethod

// ----- fixed size getData

defmethod(OBJ, ggetData, InFile, String)
  if (!self2->size)
    retmethod(True);

  int res = fread(self2->value, self2->size, 1, self->OpenFile.fd) != 1;
  retmethod(res ? False : True);
endmethod

// ----- generic get, getLine, getData from class

defalias (OBJ, (gget)ggetLine, String, Class);
defalias (OBJ, (gget)ggetData, String, Class);
defmethod(OBJ,  gget         , String, Class)
  OBJ obj = gautoDelete(gnew(_2));
  
  forward_message(_1, obj);

  if (gunderstandMessage1(obj, genericref(gadjust)) == True)
    gadjust(obj);

  retmethod(RETVAL == True ? obj : Nil);
endmethod

// ----- gput

defmethod(OBJ, gput, StringDyn, String)
  gappend(_1,_2);
  retmethod(True);
endmethod



