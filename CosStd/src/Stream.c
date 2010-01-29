/*
 o---------------------------------------------------------------------o
 |
 | COS Stream
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
 | $Id: Stream.c,v 1.5 2010/01/29 12:36:34 ldeniau Exp $
 |
*/

#include <cos/Stream.h>

#include <cos/gen/delegate.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>

#include <stdio.h>
#include <string.h>

// -----

makclass(Stream);
makclass(InputStream , Stream);
makclass(OutputStream, Stream);

makclass(ExBadStream, Exception);

// ----- constructors, destructor

defmethod(OBJ, ginit, Stream)
  self->delegate = 0;
  retmethod(_1);
endmethod

defmethod(OBJ, ginitWith, Stream, Stream)
  self->delegate = gretain(_2);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Stream)
  if (self->delegate)
    grelease(self->delegate);

  retmethod(_1);
endmethod

// ----- delegate

defmethod(OBJ, gdelegate, Stream)
  retmethod(self->delegate);
endmethod

defmethod(OBJ, gsetDelegate, Stream, Stream)
  OBJ old = self->delegate;
  self->delegate = gretain(_2);
  if (old) grelease(old);

  retmethod(_1);
endmethod

// ----- stream generic methods

defmethod(size_t, gputnChr, OutputStream, (I32)chr, (size_t)len)
  size_t n = 0;

  if (len) {
    SEL  sel = genericref(gputChr);
    IMP1 put = cos_method_fastLookup1(sel, cos_object_id(_1));
    I32  ret;
    gputChr_arg_t arg = { chr };

    for (; n < len; n++) {
      put(sel, _1, &arg, &ret);
      if (ret == EndOfStream) break;
    }
  }
  
  retmethod( n );
endmethod

defmethod(size_t, gputStr, OutputStream, (STR)str)
  size_t n = 0;

  if (str) {
    SEL  sel = genericref(gputChr);
    IMP1 put = cos_method_fastLookup1(sel, cos_object_id(_1));
    I32  ret;

    while (str[n]) {
      gputChr_arg_t arg = { str[n++] };
      put(sel, _1, &arg, &ret);
      if (ret == EndOfStream) break;
    }
  }
    
  retmethod( n );
endmethod

defmethod(size_t, gputStrLn, OutputStream, (STR)str)
  size_t n = 0;
  SEL  sel = genericref(gputChr);
  IMP1 put = cos_method_fastLookup1(sel, cos_object_id(_1));
  I32  ret;

  if (str) {
    while (str[n]) {
      gputChr_arg_t arg = { str[n++] };
      put(sel, _1, &arg, &ret);
      if (ret == EndOfStream) break;
    }
  }
    
  put(sel, _1, &(gputChr_arg_t){ '\n' }, &ret);

  retmethod( n+1 );
endmethod

defmethod(size_t, gputData, OutputStream, (U8*)buf, (size_t)len)
PRE
  test_assert( buf || !len, "invalid buffer" );

BODY
  size_t n = 0;

  if (len) {
    SEL  sel = genericref(gputChr);
    IMP1 put = cos_method_fastLookup1(sel, cos_object_id(_1));
    I32  ret;

    for (; n < len; n++) {
      gputChr_arg_t arg = { buf[n] };
      put(sel, _1, &arg, &ret);
      if (ret == EndOfStream) break;
    }
  }
  
  retmethod( n );
endmethod

defmethod(size_t, gungetData, InputStream, (U8*)buf, (size_t)len)
PRE
  test_assert( buf || !len, "invalid buffer" );

BODY
  size_t n = len;

  if (len) {
    SEL  sel = genericref(gungetChr);
    IMP1 unget = cos_method_fastLookup1(sel, cos_object_id(_1));
    I32  ret;

    for (; n > 0; n--) {
      gungetChr_arg_t arg = { buf[n-1] };
      unget(sel, _1, &arg, &ret);
      if (ret == EndOfStream) break;
    }
  }

  retmethod( len - n );
endmethod

defmethod(size_t, ggetData, InputStream, (U8*)buf, (size_t)len)
PRE
  test_assert( buf || !len, "invalid buffer" );

BODY
  size_t n = 0;
  
  if (len) {
    SEL  sel = genericref(ggetChr);
    IMP1 get = cos_method_fastLookup1(sel, cos_object_id(_1));
    I32  c;

    for (; n < len; n++) {
      get(sel, _1, 0, &c);
      if (c == EndOfStream) break;
      buf[n] = (U32)c;
    }  
  }

  retmethod( n );
endmethod

defmethod(size_t, ggetLine, InputStream, (U8*)buf, (size_t)len)
PRE
  test_assert( buf || !len, "invalid buffer" );

BODY
  size_t n = 0;
  
  if (len) {
    SEL  sel = genericref(ggetChr);
    IMP1 get = cos_method_fastLookup1(sel, cos_object_id(_1));
    I32  c, c2;

    for (; n < len; n++) {
      get(sel, _1, 0, &c);
      if (c == EndOfStream) break;

      if (c == '\n') {
        get(sel, _1, 0, &c2);
        if (c2 != EndOfStream && c2 != '\r') gungetChr(_1, c2);
        break;
      }

      if (c == '\r') {
        get(sel, _1, 0, &c2);
        if (c2 != EndOfStream && c2 != '\n') gungetChr(_1, c2);
        break;
      }

      buf[n] = (U32)c;
    }
  }
  
  retmethod( n );
endmethod

defmethod(size_t, ggetDelim, InputStream, (U8*)buf, (size_t)len, (I32)delim)
PRE
  test_assert( buf || !len, "invalid buffer" );

BODY
  size_t n = 0;
  
  if (len) {
    SEL  sel = genericref(ggetChr);
    IMP1 get = cos_method_fastLookup1(sel, cos_object_id(_1));
    I32  c;

    while (n < len) {
      get(sel, _1, 0, &c);
      if (c == EndOfStream) break;
      buf[n++] = (U32)c;
      if (c == delim) break;
    }
  }

  retmethod( n );
endmethod

defmethod(size_t, ggetDelims, InputStream, (U8*)buf, (size_t)len, (STR)delims)
PRE
  test_assert( buf || !len, "invalid buffer" );
  test_assert( delims || !len, "invalid delimiters" );

BODY
  size_t n = 0;
  
  if (len) {
    SEL  sel = genericref(ggetChr);
    IMP1 get = cos_method_fastLookup1(sel, cos_object_id(_1));
    I32  c;

    while (n < len) {
      get(sel, _1, 0, &c);
      if (c == EndOfStream) break;
      buf[n++] = (U32)c;
      if (strchr(delims, c)) break;
    }
  }

  retmethod( n );
endmethod

