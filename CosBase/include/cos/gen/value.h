#ifndef COS_GEN_VALUE_H
#define COS_GEN_VALUE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS value generics (C types)
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
 | $Id: value.h,v 1.1 2008/06/27 16:17:16 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif

defgeneric(STR            , gstr     , _1);
defgeneric(size_t         , gsize    , _1);

defgeneric(char           , gchar    , _1);
defgeneric(short          , gshort   , _1);
defgeneric(S32            , gint     , _1);
defgeneric(S64            , glong    , _1);
defgeneric(double         , gdouble  , _1);
defgeneric(_Complex double, gcomplex , _1);

defgeneric(void*          , gpointer , _1);
defgeneric(FUNC           , gfunction, _1);

#endif // COS_GEN_VALUE_H
