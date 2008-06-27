#ifndef COS_TESTS_INTERFACES_HPP
#define COS_TESTS_INTERFACES_HPP

/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - C++ interfaces for Counter
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
 | $Id: Interfaces.hpp,v 1.1 2008/06/27 16:17:25 ldeniau Exp $
 |
*/

typedef unsigned U32;

class Counter;

struct IIncr {
  virtual ~IIncr() {}
  virtual IIncr& incr() = 0;
  virtual IIncr& incrBy(U32) = 0;
  virtual IIncr& incrBy(U32,U32) = 0;
  virtual IIncr& incrBy(U32,U32,U32) = 0;
  virtual IIncr& incrBy(U32,U32,U32,U32) = 0;
  virtual IIncr& incrBy(U32,U32,U32,U32,U32) = 0;
};

struct IAddTo1 {
  virtual ~IAddTo1() {}
  virtual IAddTo1& addTo(const IAddTo1&) = 0;
  virtual IAddTo1& addTo(Counter&) const = 0;
};

struct IAddTo2 {
  virtual ~IAddTo2() {}
  virtual IAddTo2& addTo(const IAddTo2&, const IAddTo2&) = 0;
  virtual IAddTo2& addTo(Counter&, const IAddTo2&) const = 0;
  virtual IAddTo2& addTo(Counter&, const Counter&) const = 0;
};

struct IAddTo3 {
  virtual ~IAddTo3() {}
  virtual IAddTo3& addTo(const IAddTo3&, const IAddTo3&, const IAddTo3&) = 0;
  virtual IAddTo3& addTo(Counter&, const IAddTo3&, const IAddTo3&) const = 0;
  virtual IAddTo3& addTo(Counter&, const Counter&, const IAddTo3&) const = 0;
  virtual IAddTo3& addTo(Counter&, const Counter&, const Counter&) const = 0;
};

struct IAddTo4 {
  virtual ~IAddTo4() {}
  virtual IAddTo4& addTo(const IAddTo4&, const IAddTo4&, const IAddTo4&, const IAddTo4&) = 0;
  virtual IAddTo4& addTo(Counter&, const IAddTo4&, const IAddTo4&, const IAddTo4&) const = 0;
  virtual IAddTo4& addTo(Counter&, const Counter&, const IAddTo4&, const IAddTo4&) const = 0;
  virtual IAddTo4& addTo(Counter&, const Counter&, const Counter&, const IAddTo4&) const = 0;
  virtual IAddTo4& addTo(Counter&, const Counter&, const Counter&, const Counter&) const = 0;
};

#endif // COS_TESTS_INTERFACES_HPP
