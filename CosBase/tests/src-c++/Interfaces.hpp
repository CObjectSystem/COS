#ifndef COS_TESTS_INTERFACES_HPP
#define COS_TESTS_INTERFACES_HPP

/**
 * C Object System
 * COS testsuites - C++ interfaces for Counter
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

typedef unsigned U32;

struct IIncr {
  virtual ~IIncr() {}
  virtual IIncr& incr() = 0;
  virtual IIncr& incrBy(U32) = 0;
  virtual IIncr& incrBy(U32,U32) = 0;
  virtual IIncr& incrBy(U32,U32,U32) = 0;
  virtual IIncr& incrBy(U32,U32,U32,U32) = 0;
  virtual IIncr& incrBy(U32,U32,U32,U32,U32) = 0;
};

class Counter;

struct IAddTo1 {
  virtual ~IAddTo1() {}
  virtual IAddTo1& addTo(const IAddTo1&) = 0;

protected:
  friend class Counter;
  virtual Counter& addTo(Counter&) const = 0;
};

struct IAddTo2 {
  virtual ~IAddTo2() {}
  virtual IAddTo2& addTo(const IAddTo2&, const IAddTo2&) = 0;

protected:
  friend class Counter;
  virtual Counter& addTo(Counter&, const IAddTo2&) const = 0;
  virtual Counter& addTo(Counter&, const Counter&) const = 0;
};

struct IAddTo3 {
  virtual ~IAddTo3() {}
  virtual IAddTo3& addTo(const IAddTo3&, const IAddTo3&, const IAddTo3&) = 0;

protected:
  friend class Counter;
  virtual Counter& addTo(Counter&, const IAddTo3&, const IAddTo3&) const = 0;
  virtual Counter& addTo(Counter&, const Counter&, const IAddTo3&) const = 0;
  virtual Counter& addTo(Counter&, const Counter&, const Counter&) const = 0;
};

struct IAddTo4 {
  virtual ~IAddTo4() {}
  virtual IAddTo4& addTo(const IAddTo4&, const IAddTo4&, const IAddTo4&, const IAddTo4&) = 0;

protected:
  friend class Counter;
  virtual Counter& addTo(Counter&, const IAddTo4&, const IAddTo4&, const IAddTo4&) const = 0;
  virtual Counter& addTo(Counter&, const Counter&, const IAddTo4&, const IAddTo4&) const = 0;
  virtual Counter& addTo(Counter&, const Counter&, const Counter&, const IAddTo4&) const = 0;
  virtual Counter& addTo(Counter&, const Counter&, const Counter&, const Counter&) const = 0;
};

#endif // COS_TESTS_INTERFACES_HPP
