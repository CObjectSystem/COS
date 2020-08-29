/**
 * C Object System
 * COS example01 -- main
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
