#ifndef COS_GEN_MESSAGE_H
#define COS_GEN_MESSAGE_H

/**
 * C Object System
 * COS generics for messages
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

#include <cos/Object.h>

// errors and forwarding
defgeneric(void, gunrecognizedMessage1, _1);
defgeneric(void, gunrecognizedMessage2, _1, _2);
defgeneric(void, gunrecognizedMessage3, _1, _2, _3);
defgeneric(void, gunrecognizedMessage4, _1, _2, _3, _4);
defgeneric(void, gunrecognizedMessage5, _1, _2, _3, _4, _5);

// behavior, return True or False
defgeneric(OBJ , gunderstandMessage1, _1, (SEL)sel);
defgeneric(OBJ , gunderstandMessage2, _1, _2, (SEL)sel);
defgeneric(OBJ , gunderstandMessage3, _1, _2, _3, (SEL)sel);
defgeneric(OBJ , gunderstandMessage4, _1, _2, _3, _4, (SEL)sel);
defgeneric(OBJ , gunderstandMessage5, _1, _2, _3, _4, _5, (SEL)sel);

// behavior of instances of, return True or False
defgeneric(OBJ , ginstancesUnderstandMessage1, _1, (SEL)sel);
defgeneric(OBJ , ginstancesUnderstandMessage2, _1, _2, (SEL)sel);
defgeneric(OBJ , ginstancesUnderstandMessage3, _1, _2, _3, (SEL)sel);
defgeneric(OBJ , ginstancesUnderstandMessage4, _1, _2, _3, _4, (SEL)sel);
defgeneric(OBJ , ginstancesUnderstandMessage5, _1, _2, _3, _4, _5, (SEL)sel);

#endif // COS_GEN_MESSAGE_H
