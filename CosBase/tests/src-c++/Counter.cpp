/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - C++ Counter class definition
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
 | $Id: Counter.cpp,v 1.1 2008/06/27 16:17:25 ldeniau Exp $
 |
*/

#include "Counter.hpp"

// IIncrBy interface

Counter& Counter::
incr() {
  _val += 1;
  return *this;
}

Counter& Counter::
incrBy(U32 a) {
  _val += a;
  return *this;
}

Counter& Counter::
incrBy(U32 a, U32 b) {
  _val += a + b;
  return *this;
}

Counter& Counter::
incrBy(U32 a, U32 b, U32 c) {
  _val += a + b + c;
  return *this;
}

Counter& Counter::
incrBy(U32 a, U32 b, U32 c, U32 d) {
  _val += a + b + c + d;
  return *this;
}

Counter& Counter::
incrBy(U32 a, U32 b, U32 c, U32 d, U32 e) {
  _val += a + b + c + d + e;
  return *this;
}

// IAddTo1 interface

Counter& Counter::
addTo(const IAddTo1 &a) {
  a.addTo(*this);
  return *this;
}

Counter& Counter::
addTo(Counter &cnt) const {
  return cnt.incrBy(_val);
}

// IAddTo2 interface

Counter& Counter::
addTo(const IAddTo2 &a, const IAddTo2 &b) {
  a.addTo(*this,b);
  return *this;
}

Counter& Counter::
addTo(Counter &cnt, const IAddTo2 &b) const {
  b.addTo(cnt,*this);
  return cnt;
}

Counter& Counter::
addTo(Counter &cnt, const Counter &a) const {
    return cnt.incrBy(a.value(),_val);
}

// IAddTo3 interface

Counter& Counter::
addTo(const IAddTo3 &a, const IAddTo3 &b, const IAddTo3 &c) {
  a.addTo(*this,b,c);
  return *this;
}

Counter& Counter::
addTo(Counter &cnt, const IAddTo3 &b, const IAddTo3 &c) const {
  b.addTo(cnt,*this,c);
  return cnt;
}

Counter& Counter::
addTo(Counter &cnt, const Counter &a, const IAddTo3 &c) const {
  c.addTo(cnt,a,*this);
  return cnt;
}

Counter& Counter::
addTo(Counter &cnt, const Counter &a, const Counter &b) const {
  return cnt.incrBy(a.value(),b.value(),_val);
}

// IAddTo4 interface

Counter& Counter::
addTo(const IAddTo4 &a, const IAddTo4 &b, const IAddTo4 &c, const IAddTo4 &d) {
  a.addTo(*this,b,c,d);
  return *this;
}

Counter& Counter::
addTo(Counter &cnt, const IAddTo4 &b, const IAddTo4 &c, const IAddTo4 &d) const {
  b.addTo(cnt,*this,c,d);
  return cnt;
}

Counter& Counter::
addTo(Counter &cnt, const Counter &a, const IAddTo4 &c, const IAddTo4 &d) const {
  c.addTo(cnt,a,*this,d);
  return cnt;
}

Counter& Counter::
addTo(Counter &cnt, const Counter &a, const Counter &b, const IAddTo4 &d) const {
  d.addTo(cnt,a,b,*this);
  return cnt;
}

Counter& Counter::
addTo(Counter &cnt, const Counter &a, const Counter &b, const Counter &c) const {
  return cnt.incrBy(a.value(),b.value(),c.value(),_val);
}
