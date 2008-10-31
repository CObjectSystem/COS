/*
 o---------------------------------------------------------------------o
 |
 | COS contract
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
 | $Id: cos_contract.c,v 1.2 2008/10/31 15:19:44 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>

// ----- invariant

void
cos_contract_invariant1(OBJ _1, STR func, STR file, int line)
{
  if (gunderstandMessage1(_1, genericref(ginvariant)) == True)
    ginvariant(_1,func,file,line);
}

void
cos_contract_invariant2(OBJ _1, OBJ _2, STR func, STR file, int line)
{
  cos_contract_invariant1(_1,func,file,line);
  cos_contract_invariant1(_2,func,file,line);
}

void
cos_contract_invariant3(OBJ _1, OBJ _2, OBJ _3, STR func, STR file, int line)
{
  cos_contract_invariant2(_1,_2,func,file,line);
  cos_contract_invariant1(_3   ,func,file,line);
}

void
cos_contract_invariant4(OBJ _1, OBJ _2, OBJ _3, OBJ _4, STR func, STR file, int line)
{
  cos_contract_invariant2(_1,_2,func,file,line);
  cos_contract_invariant2(_3,_4,func,file,line);
}

void
cos_contract_invariant5(OBJ _1, OBJ _2, OBJ _3, OBJ _4, OBJ _5, STR func, STR file, int line)
{
  cos_contract_invariant2(_1,_2,func,file,line);
  cos_contract_invariant2(_3,_4,func,file,line);
  cos_contract_invariant1(_5   ,func,file,line);
}

