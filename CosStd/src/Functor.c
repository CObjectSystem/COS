/**
 * C Object System
 * COS Functor
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

/* NOTE-INFO: PlaceHolder specializations

   PlaceHolders should only override Object's methods, no more,
   since High Order Messages are commonly built with delegation.
*/

#include <cos/Functor.h>

#include <cos/gen/object.h>

// ----- allocator

defmethod(OBJ, galloc, pmFunctor) // lazy alloc
  retmethod(_1);
endmethod

// ----- class cluster root classes

makclass(Expression, Any);

// ----- functor operator (iterate, compose)

makclass(IterateFun, Functor);
makclass(ComposeFun, Functor);

// ------------------------------------------------------------
// ----- variable expression

makclass(VarExpr, Expression);
makclass(FunArg , VarExpr);

// ------------------------------------------------------------
// ----- functor expression

makclass(Functor, Expression);
makclass(FunExpr, Functor);
makclass(MsgExpr, Functor);

makclass(FunExpr0, FunExpr);
makclass(FunExpr1, FunExpr);
makclass(FunExpr2, FunExpr);
makclass(FunExpr3, FunExpr);
makclass(FunExpr4, FunExpr);
makclass(FunExpr5, FunExpr);
makclass(FunExpr6, FunExpr);
makclass(FunExpr7, FunExpr);
makclass(FunExpr8, FunExpr);
makclass(FunExpr9, FunExpr);

// ----- specializations

makclass(FunExpr11, FunExpr1);
makclass(FunExpr12, FunExpr1);

makclass(FunExpr21, FunExpr2);
makclass(FunExpr22, FunExpr2);
makclass(FunExpr23, FunExpr2);
makclass(FunExpr24, FunExpr2);

makclass(FunExpr31, FunExpr3);
makclass(FunExpr32, FunExpr3);
makclass(FunExpr33, FunExpr3);
makclass(FunExpr34, FunExpr3);
makclass(FunExpr35, FunExpr3);
makclass(FunExpr36, FunExpr3);
makclass(FunExpr37, FunExpr3);
makclass(FunExpr38, FunExpr3);

