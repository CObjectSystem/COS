/**
 * C Object System
 * COS example01 -- String class
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

#include "String.h"
#include "generics.h"

#include <string.h>
#include <stdlib.h>

makclass(String);

static char* str_dup(STR str)
{
  size_t len = strlen(str);
  char *s = cos_malloc(len+1);
  if (s) memcpy(s, str, len+1);
  return s;
}

defmethod(OBJ, ginitWithStr, String, (STR)str)
  useclass(ExBadAlloc);

  self->str = str_dup(str);
  if (!self->str)
    THROW(ExBadAlloc);

  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, String)
  cos_free(self->str), self->str = 0;
  retmethod(_1);
endmethod

