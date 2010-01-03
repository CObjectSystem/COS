/*
 o---------------------------------------------------------------------o
 |
 | COS Ordered
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
 | $Id: Ordered.c,v 1.10 2010/01/03 14:54:33 ldeniau Exp $
 |
*/

#include <cos/Ordered.h>
#include <cos/gen/algorithm.h>
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
