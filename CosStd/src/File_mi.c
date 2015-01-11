/**
 * C Object System
 * COS File multiple inheritance
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
  ensure(chg, "unable to change from InputOutputFile to OutputInputFile");

  forward_message(_1);
endmethod

defmethod(void, gunrecognizedMessage2, InputOutputFile, Object)
  if (ginstancesUnderstandMessage2(OutputInputFile, _2, _sel) != True)
    next_method(self,self2);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutputInputFile), classref(Stream));
  ensure(chg, "unable to change from InputOutputFile to OutputInputFile");

  forward_message(_1,_2);
endmethod

defmethod(void, gunrecognizedMessage3, InputOutputFile, Object, Object)
  if (ginstancesUnderstandMessage3(OutputInputFile, _2, _3, _sel) != True)
    next_method(self,self2,self3);
  
  BOOL chg = cos_object_unsafeChangeClass(_1, classref(OutputInputFile), classref(Stream));
  ensure(chg, "unable to change from InputOutputFile to OutputInputFile");

  forward_message(_1,_2,_3);
endmethod

// ----- write-read -> read-write (multiple inheritance)

defmethod(void, gunrecognizedMessage1, OutputInputFile)
  if (ginstancesUnderstandMessage1(InputOutputFile, _sel) != True)
    next_method(self);
  
  gflush(_1);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InputOutputFile), classref(Stream));
  ensure(chg, "unable to change from OutputInputFile to InputOutputFile");

  forward_message(_1);
endmethod

defmethod(void, gunrecognizedMessage2, OutputInputFile, Object)
  if (ginstancesUnderstandMessage2(InputOutputFile, _2, _sel) != True)
    next_method(self,self2);
  
  gflush(_1);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InputOutputFile), classref(Stream));
  ensure(chg, "unable to change from OutputInputFile to InputOutputFile");

  forward_message(_1,_2);
endmethod

defmethod(void, gunrecognizedMessage3, OutputInputFile, Object, Object)
  if (ginstancesUnderstandMessage3(InputOutputFile, _2, _3, _sel) != True)
    next_method(self,self2,self3);
  
  gflush(_1);

  BOOL chg = cos_object_unsafeChangeClass(_1, classref(InputOutputFile), classref(Stream));
  ensure(chg, "unable to change from OutputInputFile to InputOutputFile");

  forward_message(_1,_2,_3);
endmethod

