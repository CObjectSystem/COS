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
 | $Id: File_mi.c,v 1.2 2010/01/15 23:50:13 ldeniau Exp $
 |
*/

#include <cos/File.h>

#include <cos/gen/message.h>
#include <cos/gen/object.h>

// -----

useclass(InOutFile, OutInFile, InOutBinFile, OutInBinFile);

// ----- Text File

// ----- read-write -> write-read (multiple inheritance)

defmethod(void, gunrecognizedMessage1, InOutFile)
  if (ginstancesUnderstandMessage1(OutInFile, _sel) != True)
    next_method(self);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutInFile), classref(File));
  test_assert(chg, "unable to change from InOutFile to OutInFile");

  forward_message(_1);
endmethod

defmethod(void, gunrecognizedMessage2, InOutFile, Object)
  if (ginstancesUnderstandMessage2(OutInFile, _2, _sel) != True)
    next_method(self,self2);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutInFile), classref(File));
  test_assert(chg, "unable to change from InOutFile to OutInFile");

  forward_message(_1,_2);
endmethod

defmethod(void, gunrecognizedMessage3, InOutFile, Object, Object)
  if (ginstancesUnderstandMessage3(OutInFile, _2, _3, _sel) != True)
    next_method(self,self2,self3);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutInFile), classref(File));
  test_assert(chg, "unable to change from InOutFile to OutInFile");

  forward_message(_1,_2,_3);
endmethod

// ----- write-read -> read-write

defmethod(void, gunrecognizedMessage1, OutInFile)
  if (ginstancesUnderstandMessage1(InOutFile, _sel) != True)
    next_method(self);
  
  fflush(self->OutFile.OpenFile.fd);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InOutFile), classref(File));
  test_assert(chg, "unable to change from OutInFile to InOutFile");

  forward_message(_1);
endmethod

defmethod(void, gunrecognizedMessage2, OutInFile, Object)
  if (ginstancesUnderstandMessage2(InOutFile, _2, _sel) != True)
    next_method(self,self2);
  
  fflush(self->OutFile.OpenFile.fd);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InOutFile), classref(File));
  test_assert(chg, "unable to change from OutInFile to InOutFile");

  forward_message(_1,_2);
endmethod

defmethod(void, gunrecognizedMessage3, OutInFile, Object, Object)
  if (ginstancesUnderstandMessage3(InOutFile, _2, _3, _sel) != True)
    next_method(self,self2,self3);
  
  fflush(self->OutFile.OpenFile.fd);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InOutFile), classref(File));
  test_assert(chg, "unable to change from OutInFile to InOutFile");

  forward_message(_1,_2,_3);
endmethod

// ----- Binary File

// ----- read-write -> write-read (multiple inheritance)

defmethod(void, gunrecognizedMessage1, InOutBinFile)
  if (ginstancesUnderstandMessage1(OutInBinFile, _sel) != True)
    next_method(self);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutInBinFile), classref(File));
  test_assert(chg, "unable to change from InOutBinFile to OutInBinFile");

  forward_message(_1);
endmethod

defmethod(void, gunrecognizedMessage2, InOutBinFile, Object)
  if (ginstancesUnderstandMessage2(OutInBinFile, _2, _sel) != True)
    next_method(self,self2);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutInBinFile), classref(File));
  test_assert(chg, "unable to change from InOutBinFile to OutInBinFile");

  forward_message(_1,_2);
endmethod

defmethod(void, gunrecognizedMessage3, InOutBinFile, Object, Object)
  if (ginstancesUnderstandMessage3(OutInBinFile, _2, _3, _sel) != True)
    next_method(self,self2,self3);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutInBinFile), classref(File));
  test_assert(chg, "unable to change from InOutBinFile to OutInBinFile");

  forward_message(_1,_2,_3);
endmethod

// ----- write-read -> read-write

defmethod(void, gunrecognizedMessage1, OutInBinFile)
  if (ginstancesUnderstandMessage1(InOutBinFile, _sel) != True)
    next_method(self);
  
  fflush(self->OutBinFile.OutFile.OpenFile.fd);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InOutBinFile), classref(File));
  test_assert(chg, "unable to change from OutInBinFile to InOutBinFile");

  forward_message(_1);
endmethod

defmethod(void, gunrecognizedMessage2, OutInBinFile, Object)
  if (ginstancesUnderstandMessage2(InOutBinFile, _2, _sel) != True)
    next_method(self,self2);
  
  fflush(self->OutBinFile.OutFile.OpenFile.fd);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InOutBinFile), classref(File));
  test_assert(chg, "unable to change from OutInBinFile to InOutBinFile");

  forward_message(_1,_2);
endmethod

defmethod(void, gunrecognizedMessage3, OutInBinFile, Object, Object)
  if (ginstancesUnderstandMessage3(InOutBinFile, _2, _3, _sel) != True)
    next_method(self,self2,self3);
  
  fflush(self->OutBinFile.OutFile.OpenFile.fd);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InOutBinFile), classref(File));
  test_assert(chg, "unable to change from OutInBinFile to InOutBinFile");

  forward_message(_1,_2,_3);
endmethod

