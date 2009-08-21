/*
 o---------------------------------------------------------------------o
 |
 | COS Vector
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
 | $Id: Vector.c,v 1.6 2009/08/21 13:04:40 ldeniau Exp $
 |
*/

#include <cos/IntVector.h>
#include <cos/LngVector.h>
#include <cos/FltVector.h>
#include <cos/CpxVector.h>

#include <cos/gen/object.h>
#include <cos/gen/init.h>

makclass(Vector, ValueSequence);

// ------ Vector cluster front-end

defmethod(OBJ, galloc, mVector)
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Vector)
  retmethod(_1);
endmethod

// ----- constructors from a vector

defmethod(OBJ, ginitWithIntPtr, mVector, (I32*)ref, (U32)n)
  retmethod( ginitWith(_1, aIntVectorRef(ref,n)) );
endmethod

defmethod(OBJ, ginitWithLngPtr, mVector, (I64*)ref, (U32)n)
  retmethod( ginitWith(_1, aLngVectorRef(ref,n)) );
endmethod

defmethod(OBJ, ginitWithFltPtr, mVector, (F64*)ref, (U32)n)
  retmethod( ginitWith(_1, aFltVectorRef(ref,n)) );
endmethod

defmethod(OBJ, ginitWithCpxPtr, mVector, (C64*)ref, (U32)n)
  retmethod( ginitWith(_1, aCpxVectorRef(ref,n)) );
endmethod

