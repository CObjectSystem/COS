#ifndef COS_TESTS_COUNTER_HPP
#define COS_TESTS_COUNTER_HPP

/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - C++ Counter class
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
 | $Id: Counter.hpp,v 1.2 2009/03/11 12:29:27 ldeniau Exp $
 |
*/

#include "Interfaces.hpp"

class Counter :
  virtual public IIncr,
  virtual public IAddTo1,
  virtual public IAddTo2,
  virtual public IAddTo3,
  virtual public IAddTo4
{
public:
  explicit Counter(U32 val=0) : _val(val) {}
  U32 value() const { return _val; }
  virtual ~Counter() {}

public: // overrides with covariant return type
  virtual Counter& incr();
  virtual Counter& incrBy(U32);
  virtual Counter& incrBy(U32,U32);
  virtual Counter& incrBy(U32,U32,U32);
  virtual Counter& incrBy(U32,U32,U32,U32);
  virtual Counter& incrBy(U32,U32,U32,U32,U32);
  
  virtual Counter& addTo(const IAddTo1&);
  virtual Counter& addTo(const IAddTo2&, const IAddTo2&);
  virtual Counter& addTo(const IAddTo3&, const IAddTo3&, const IAddTo3&);
  virtual Counter& addTo(const IAddTo4&, const IAddTo4&, const IAddTo4&, const IAddTo4&);

protected:
  virtual Counter& addTo(Counter&) const;

  virtual Counter& addTo(Counter&, const IAddTo2&) const;
  virtual Counter& addTo(Counter&, const Counter&) const;

  virtual Counter& addTo(Counter&, const IAddTo3&, const IAddTo3&) const;
  virtual Counter& addTo(Counter&, const Counter&, const IAddTo3&) const;
  virtual Counter& addTo(Counter&, const Counter&, const Counter&) const;

  virtual Counter& addTo(Counter&, const IAddTo4&, const IAddTo4&, const IAddTo4&) const;
  virtual Counter& addTo(Counter&, const Counter&, const IAddTo4&, const IAddTo4&) const;
  virtual Counter& addTo(Counter&, const Counter&, const Counter&, const IAddTo4&) const;
  virtual Counter& addTo(Counter&, const Counter&, const Counter&, const Counter&) const;

private: // states
  U32 _val;
};

#endif // COS_TESTS_COUNTER_HPP
