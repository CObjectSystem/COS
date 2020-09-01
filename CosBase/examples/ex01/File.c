/**
 * C Object System
 * COS example01 -- File class
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

#include "File.h"
#include "String.h"
#include "generics.h"
#include <cos/errno.h>

makclass(File, Stream);

defmethod(OBJ, ginitWithStr, File, (STR)str)
  self->file = str ? fopen(str,"r+") : stdout;
  if (!self->file)
    test_errno(); // THROW

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, File)
  if (self->file)
    fclose(self->file);

  retmethod(_1);
endmethod

defmethod(void, gprint, File, String)
  fputs(self2->str, self1->file);
endmethod

// extend the class Stream to support File creation

useclass(File);

defmethod(OBJ, ginitWithStr, pmStream, (STR)str)
  retmethod( gnewWithStr(File,str) );
endmethod

