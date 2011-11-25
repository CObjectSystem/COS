#ifndef COS_GEN_SEQUENCE_H
#define COS_GEN_SEQUENCE_H

/**
 * C Object System
 * COS generics for sequences
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

#include <cos/Object.h>

// in place
defgeneric(OBJ, greverse, _1);
defgeneric(OBJ, gpermute, _1, idx);

// concat
defgeneric(OBJ, gconcat , _1, _2);
defgeneric(OBJ, gconcat3, _1, _2, _3);
defgeneric(OBJ, gconcat4, _1, _2, _3, _4);
defgeneric(OBJ, gconcatn, _1);

// zip
defgeneric(OBJ, gzip , _1, _2);
defgeneric(OBJ, gzip3, _1, _2, _3);
defgeneric(OBJ, gzip4, _1, _2, _3, _4);
defgeneric(OBJ, gzipn, _1);

// array-like accessor
defgeneric(U32, gindexOf, _1, fun); // return index or (U32)-1 if not found

// list-like accessor
defgeneric(OBJ, ginsertAt, _1, at, what);
defgeneric(OBJ, gremoveAt, _1, at);

// stack-like accessors
defgeneric(OBJ, gpush, _1, what);
defgeneric(OBJ, gpop , _1); // return _1
defgeneric(OBJ, gtop , _1); // return top object

// dequeue-like accessors
defgeneric(OBJ, gpushFront, _1, what);
defgeneric(OBJ, gpushBack , _1, what);
defgeneric(OBJ, gpopFront , _1); // return _1
defgeneric(OBJ, gpopBack  , _1); // return _1
defgeneric(OBJ, gtopFront , _1); // return front object
defgeneric(OBJ, gtopBack  , _1); // return back  object

// seq-like accessor
defgeneric(OBJ, gprepend, _1, what);
defgeneric(OBJ, gappend , _1, what);
defgeneric(OBJ, gdrop   , _1, idx);  // remove up to index (back if idx<0)
defgeneric(OBJ, gfirst  , _1);
defgeneric(OBJ, glast   , _1);

// adjust sequence capacity to size
defgeneric(OBJ, gadjust , _1); // compact (+ fix type)

// englarge sequence memory (Note: front if by<0)
defgeneric(OBJ, genlarge , _1, by);
defgeneric(U32, gcapacity, _1);

#endif // COS_GEN_SEQUENCE_H
