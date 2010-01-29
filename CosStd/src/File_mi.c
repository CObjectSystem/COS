/*
 o---------------------------------------------------------------------o
 |
 | COS File multiple inheritance
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
 | $Id: File_mi.c,v 1.3 2010/01/29 12:36:34 ldeniau Exp $
 |
*/

#include <cos/File.h>

#include <cos/gen/message.h>
#include <cos/gen/object.h>
#include <cos/gen/stream.h>

// -----

useclass(InputOutputFile, OutputInputFile);

// ----- read-write -> write-read (multiple inheritance)

defmethod(void, gunrecognizedMessage1, InputOutputFile)
  if (ginstancesUnderstandMessage1(OutputInputFile, _sel) != True)
    next_method(self);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutputInputFile), classref(Stream));
  test_assert(chg, "unable to change from InputOutputFile to OutputInputFile");

  forward_message(_1);
endmethod

defmethod(void, gunrecognizedMessage2, InputOutputFile, Object)
  if (ginstancesUnderstandMessage2(OutputInputFile, _2, _sel) != True)
    next_method(self,self2);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutputInputFile), classref(Stream));
  test_assert(chg, "unable to change from InputOutputFile to OutputInputFile");

  forward_message(_1,_2);
endmethod

defmethod(void, gunrecognizedMessage3, InputOutputFile, Object, Object)
  if (ginstancesUnderstandMessage3(OutputInputFile, _2, _3, _sel) != True)
    next_method(self,self2,self3);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutputInputFile), classref(Stream));
  test_assert(chg, "unable to change from InputOutputFile to OutputInputFile");

  forward_message(_1,_2,_3);
endmethod

// ----- write-read -> read-write (multiple inheritance)

defmethod(void, gunrecognizedMessage1, OutputInputFile)
  if (ginstancesUnderstandMessage1(InputOutputFile, _sel) != True)
    next_method(self);
  
  gflush(_1);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InputOutputFile), classref(Stream));
  test_assert(chg, "unable to change from OutputInputFile to InputOutputFile");

  forward_message(_1);
endmethod

defmethod(void, gunrecognizedMessage2, OutputInputFile, Object)
  if (ginstancesUnderstandMessage2(InputOutputFile, _2, _sel) != True)
    next_method(self,self2);
  
  gflush(_1);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InputOutputFile), classref(Stream));
  test_assert(chg, "unable to change from OutputInputFile to InputOutputFile");

  forward_message(_1,_2);
endmethod

defmethod(void, gunrecognizedMessage3, OutputInputFile, Object, Object)
  if (ginstancesUnderstandMessage3(InputOutputFile, _2, _3, _sel) != True)
    next_method(self,self2,self3);
  
  gflush(_1);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InputOutputFile), classref(Stream));
  test_assert(chg, "unable to change from OutputInputFile to InputOutputFile");

  forward_message(_1,_2,_3);
endmethod

