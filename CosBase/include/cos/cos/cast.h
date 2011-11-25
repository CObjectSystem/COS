#ifndef COS_COS_CAST_H
#define COS_COS_CAST_H

/**
 * C Object System
 * COS cast operators
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

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/cast.h>"
#endif

#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_CAST
#define COS_DISABLE_cast
#define COS_DISABLE_dyncast
#define COS_DISABLE_ecast
#define COS_DISABLE_edyncast
#define COS_DISABLE_ecastLoc
#define COS_DISABLE_edyncastLoc
#define COS_DISABLE_dbgcast
#endif

#ifndef COS_DISABLE_CAST
#define CAST(typename,value) COS_CAST(typename,value)
#endif

#ifndef COS_DISABLE_cast
#define cast(class,object) COS_OBJECT_CAST(class,object)
#endif

#ifndef COS_DISABLE_dyncast
#define dyncast(class,object) COS_OBJECT_DYNCAST(class,object)
#endif

#ifndef COS_DISABLE_ecast
#define ecast(class,object) COS_OBJECT_ECAST(class,object)
#endif

#ifndef COS_DISABLE_edyncast
#define edyncast(class,object) COS_OBJECT_EDYNCAST(class,object)
#endif

#ifndef COS_DISABLE_ecastLoc
#define ecastLoc(cls,obj,file,line) COS_OBJECT_ECASTLOC(cls,obj,file,line)
#endif

#ifndef COS_DISABLE_edyncastLoc
#define edyncastLoc(cls,obj,file,line) COS_OBJECT_EDYNCASTLOC(cls,obj,file,line)
#endif

#ifndef COS_DISABLE_dbgcast
#define dbgcast(class,object) COS_OBJECT_DBGCAST(class,object)
#endif

/***********************************************************
 * Implementation
 */

// convert value (C cast)
#define COS_CAST(type,value) ((type) (value))
        
// convert object (COS cast)
#define COS_OBJECT_CAST(cls,obj) \
((struct cls*) cos_object_cast(obj,classref(cls)))

// convert object (COS downcast)
#define COS_OBJECT_DYNCAST(cls,obj) \
((struct cls*) cos_object_dyncast(obj,classref(cls)))

// convert object (COS cast or throw)
#define COS_OBJECT_ECAST(cls,obj) \
        COS_OBJECT_ECASTLOC(cls,obj,__FILE__,__LINE__)

// convert object (COS downcast or throw)
#define COS_OBJECT_EDYNCAST(cls,obj) \
        COS_OBJECT_EDYNCASTLOC(cls,obj,__FILE__,__LINE__)

// convert object (COS cast or throw)
#define COS_OBJECT_ECASTLOC(cls,obj,file,line) \
((struct cls*) cos_object_ecast(obj,classref(cls),file,line))

// convert object (COS downcast or throw)
#define COS_OBJECT_EDYNCASTLOC(cls,obj,file,line) \
((struct cls*) cos_object_edyncast(obj,classref(cls),file,line))

// convert value (static cast in release mode, dynamic cast in debug mode)
#define COS_OBJECT_DBGCAST(cls,obj) \
COS_PP_IFNDEF(COS_DEBUG)( COS_CAST(struct cls*, obj), \
                          COS_OBJECT_EDYNCASTLOC(cls,obj,__FILE__,__LINE__) )

#endif // COS_COS_CAST_H
