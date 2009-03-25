/*
 o---------------------------------------------------------------------o
 |
 | COS example01 -- main
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
 | $Id: main.c,v 1.2 2009/03/25 16:50:08 ldeniau Exp $
 |
*/

#include "generics.h"
#include <stdlib.h>

useclass(Stream, String);

int main(void)
{
  OBJ strm = gnewWithStr(Stream, 0);
  OBJ str1 = gnewWithStr(String, "string one\n");
  OBJ str2 = gnewWithStr(String, "string two\n");

  gprint(strm, str1);
  gprint(strm, str2);
    
  grelease(str1);
  grelease(str2);
  grelease(strm);

  return EXIT_SUCCESS;
}
