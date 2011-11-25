#ifndef COS_FILE_H
#define COS_FILE_H

/**
 * C Object System
 * COS File
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

#include <cos/Stream.h>

/* NOTE-USER: File classes (wrapper to C FILE*)

<- InputStream
  <- InputFile
    <- InputOutputFile
    
<- OutputStream
  <- OutputFile
    <- OutputInputFile
*/

#include <stdio.h>

// ----- private shared data structure

struct file_descriptor_ {
  FILE *fp;
  OBJ   name;
  BOOL  own;
};

// ----- File types

defclass(InputFile, InputStream)      // r mode
  struct file_descriptor_ fd;
endclass

defclass(OutputFile, OutputStream)    // w mode
  struct file_descriptor_ fd;
endclass

defclass(InputOutputFile, InputFile)  // r+ mode
endclass

defclass(OutputInputFile, OutputFile) // w+ mode
endclass

#endif // COS_FILE_H
