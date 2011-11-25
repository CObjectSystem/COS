#ifndef COS_TESTS_COUNTER_HPP
#define COS_TESTS_COUNTER_HPP

/**
 * C Object System
 * COS testsuites - C++ Counter class
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
