#ifndef COS_COS_COSCLS_H
#define COS_COS_COSCLS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS core classes
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
 | $Id: coscls.h,v 1.13 2010/01/11 13:41:20 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/coscls.h>"
#endif

/* NOTE-USER: core class hierarchy
   COS classes, meta classes and property meta classes hierarchy follows
   the principle of 'uniform object oriented programming' a-la SmallTalk
   (i.e. everything-is-an-object) and the 'safe metaclass compatibility model'
   (see "Safe MetaClass Programming", OOPSLA'98).

   1) Behaviors are Objects
   2) Classes and Generics are Behaviors
   3) Meta classes are Classes
   4) Property classes are Meta classes

   Legend:
     -> means 'subclass of'                          Class
     => means 'instance of'                            ^
                                                       |
                                                  o---------o
                NIL                   +---------->| mObject |=========>v
                 ^                    |           o---------o          v
                 |                    |                ^               v
             o--------o         o----------o           |               v
             | Object |========>| pmObject |===========|==========>v   v
             o--------o         o----------o           |           v   v
                 ^                               o-----------o     v   v
                 |                    +--------->| mBehavior |=====v==>v
                 |                    |          o-----------o     v   v
                 |                    |                ^           v   v
            o----------o       o------------o          |           v   v
            | Behavior |======>| pmBehavior |==========|==========>v   v
            o----------o       o------------o          |           v   v
                 ^                                o--------o       v   v
                 |                    +---------->| mClass |=======v==>v
                 |                    |           o--------o       v   v
                 |                    |                ^           v   v
             o-------o           o---------o           |           v   v
             | Class |==========>| pmClass |===========|==========>v   v
             o-------o           o---------o           |           v   v
                 ^                              o------------o     v   v
                 |                    +-------->| mMetaClass |=====v==>v
                 |                    |         o------------o     v   v
                 |                    |                ^           v   v
           o-----------o       o-------------o         |           v   v
  ========>| MetaClass |======>| pmMetaClass |=========|==========>v   v
  ^        o-----------o       o-------------o         |           v   v
  ^              ^                             o----------------o  v   v
  ^              |                    +------->| mPropMetaClass |==v==>v
  ^              |                    |        o----------------o  v   v
  ^              |                    |                            v   v
  ^      o---------------o    o-----------------o                  v   v
  ^  ===>| PropMetaClass |===>| pmPropMetaClass |=================>v   v
  ^  ^   o---------------o    o-----------------o                  v   v
  ^  ^                                                             v   v
  ^  ^<============================================================X   v
  ^                                                                ^   v
  ^<===============================================================^===X
                                                                   ^   ^
                                                     Class         ^   ^
                                                       ^           ^   ^
                                                       |           ^   ^
                                                    o------o       ^   ^
                NIL                   +------------>| mNil |=======^==>^
                 ^                    |             o------o       ^   ^
                 |                    |                ^           ^   ^
              o-----o             o-------o            |           ^   ^
              | Nil |============>| pmNil |============|==========>^   ^
              o-----o             o-------o            |           ^   ^
                 ^                               o-----------o     ^   ^
                 |                    +--------->| mProperty |=====^==>^
                 |                    |          o-----------o     ^   ^
                 |                    |                            ^   ^
            o----------o       o------------o                      ^   ^
            | Property |======>| pmProperty |=====================>^   ^
            o----------o       o------------o 

*/

COS_CLS_DEF(Object,_)
COS_CLS_END

COS_CLS_DEF(Behavior,Object)
  U32 id;
/* id is storing cryptic information (LSB->MSB):
     u27 tag {1..134217727} (unique)
     u5  rnk {0..31} (class rank) OR {1..5} (generic rank)
*/
COS_CLS_END

COS_CLS_DEF(Generic,Behavior)
  U32 mth;
  STR str;
  STR sig;
  struct cos_generic_rcvinfo *rcvinfo;
  struct cos_generic_arginfo *arginfo;
  U16 argsize;
  U16 retsize;
  U32 info; // store cryptic information, see cos/cos/generic.h
COS_CLS_END

COS_CLS_DEF(Class,Behavior)
  U32 isz;
  STR str;
  struct Class* spr;
  struct Class* cls;
  U32 prp[2];
COS_CLS_END

COS_CLS_DEF(Method,Object)
  struct Generic* gen;
  U32 info; // store cryptic information, see cos/cos/method.h
  U32 arnd;
COS_CLS_END

COS_CLS_DEF(Method1,Method)
  IMP1 fct;
  struct Class* cls[1];
COS_CLS_END

COS_CLS_DEF(Method2,Method)
  IMP2 fct;
  struct Class* cls[2];
COS_CLS_END

COS_CLS_DEF(Method3,Method)
  IMP3 fct;
  struct Class* cls[3];
COS_CLS_END

COS_CLS_DEF(Method4,Method)
  IMP4 fct;
  struct Class* cls[4];
COS_CLS_END

COS_CLS_DEF(Method5,Method)
  IMP5 fct;
  struct Class* cls[5];
COS_CLS_END

// standard precicates
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_STD_PREDICATES
#endif

#ifndef COS_DISABLE_STD_PREDICATES
COS_CLS_USE(Nil,True,False);
#endif

#endif // COS_COS_COSCLS_H
