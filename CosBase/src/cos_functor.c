/**
 * C Object System
 * COS functor
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
#include <cos/Exception.h>

#include <cos/gen/object.h>

#include <stdlib.h>

#ifndef COS_FUNCTOR_STACKSIZE
#define COS_FUNCTOR_STACKSIZE 8192  // 64k per thread on 64 bits arch
#endif

#if defined(_OPENMP) || COS_HAS_TLS || !COS_HAS_POSIX // --------------------

__thread struct cos_functor_context cos_functor_context_ = { 0, 0, 0 };

#else // !defined(_OPENMP) && !COS_HAS_TLS && COS_HAS_POSIX -----------------

       int            cos_functor_context_key_init = 0;
       pthread_key_t  cos_functor_context_key;
static pthread_once_t cos_functor_context_key_once = PTHREAD_ONCE_INIT;

static void
make_key(void)
{
  if ( pthread_key_create(&cos_functor_context_key, free) )
    cos_abort("unable to initialize functor context");
}

struct cos_functor_context*
cos_functor_context_init(void)
{
  struct cos_functor_context *cxt;

  pthread_once(&cos_functor_context_key_once, make_key);
  cos_functor_context_key_init = 1;

  if (!(cxt = malloc(sizeof *cxt)))
	  cos_abort("out of memory while creating functor context");

  cxt->stk = 0;
  cxt->top = 0;
  cxt->end = 0;

  if ( pthread_setspecific(cos_functor_context_key, cxt) )
	  cos_abort("unable to initialize functor context");

  return cxt;
}
  
#endif // ------------------------------------------------

useclass(ExBadAlloc, ExOverflow, ExUnderflow);

void
cos_functor_overflow(void)
{
  struct cos_functor_context *cxt = cos_functor_context();
  size_t ssize = COS_FUNCTOR_STACKSIZE * sizeof(OBJ);

  if (cxt->stk)
    THROW(gnewWithStr(ExOverflow, "functor stack overflow"));

  if (!(cxt->stk = malloc(ssize)))
    THROW(ExBadAlloc);
  
	cxt->top = cxt->stk;
	cxt->end = cxt->stk + COS_FUNCTOR_STACKSIZE;
}

void
cos_functor_underflow(void)
{
  THROW(gnewWithStr(ExUnderflow, "functor stack underflow"));
}

void
cos_functor_clearContext(void)
{
  struct cos_functor_context *cxt = cos_functor_context();

  free(cxt->stk), cxt->stk = 0;
}

