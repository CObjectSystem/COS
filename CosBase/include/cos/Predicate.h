#ifndef COS_PREDICATE_H
#define COS_PREDICATE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Predicate
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
 | $Id: Predicate.h,v 1.2 2010/05/20 15:48:13 ldeniau Exp $
 |
*/

#include <cos/Nil.h>

/* NOTE-USER: Predicate

   Predicate is the "root" class of all predicate classes.
      
   Predicate classes are useful for dispatching on result of predicates
   like gisKindOf, gisEqual or gcompare. This allow automatic branching
   of execution flow based on results as well as storing predicates
   results as objects.
*/

defclass(Predicate, Nil)
endclass

#endif // COS_PREDICATE_H
