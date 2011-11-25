/**
 * C Object System
 * COS Ordered
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

#include <cos/Ordered.h>
#include <cos/gen/sequence.h>
#include <cos/gen/numop.h>

// -----

makclass(Ordered, Predicate);

makclass(Equal  , Ordered);
makclass(Lesser , Ordered);
makclass(Greater, Ordered);

// -----

useclass(Lesser, Greater);

// -----

defalias (OBJ, (gneg)greverse, pmLesser);
defalias (OBJ, (gneg)gnegate , pmLesser);
defmethod(OBJ,  gneg         , pmLesser)
  retmethod(Greater);
endmethod

defalias (OBJ, (gneg)greverse, pmOrdered);
defalias (OBJ, (gneg)gnegate , pmOrdered);
defmethod(OBJ,  gneg         , pmOrdered)
  retmethod(_1);
endmethod

defalias (OBJ, (gneg)greverse, pmGreater);
defalias (OBJ, (gneg)gnegate , pmGreater);
defmethod(OBJ,  gneg         , pmGreater)
  retmethod(Lesser);
endmethod

#if 0

IMPORTANT NOTE: these methods are too generic and prevent
                ANY specialization through the delegation

// -----

defmethod(OBJ, gisEqual, Object, Object)
  retmethod( gcompare(_1,_2) == Equal   ? True : False );
endmethod

defmethod(OBJ, gisLesser, Object, Object)
  retmethod( gcompare(_1,_2) == Lesser  ? True : False );
endmethod

defmethod(OBJ, gisGreater, Object, Object)
  retmethod( gcompare(_1,_2) == Greater ? True : False );
endmethod

defmethod(OBJ, gisLesserOrEqual, Object, Object)
  retmethod( gcompare(_1,_2) == Greater ? False : True );
endmethod

defmethod(OBJ, gisGreaterOrEqual, Object, Object)
  retmethod( gcompare(_1,_2) == Lesser  ? False : True );
endmethod

// -----

defmethod(OBJ, gisNotEqual, Object, Object)
  retmethod( gisEqual(_1,_2) == False ? True : False );
endmethod

// -----

defmethod(OBJ, gmin, Object, Object)
  retmethod( gcompare(_1,_2) == Lesser  ? _1 : _2 );
endmethod

defmethod(OBJ, gmax, Object, Object)
  retmethod( gcompare(_1,_2) == Greater ? _1 : _2 );
endmethod

#endif
