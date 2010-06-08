/*
 o---------------------------------------------------------------------o
 |
 | COS functor
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
 | $Id: cos_functor.c,v 1.1 2010/06/08 09:05:57 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Exception.h>

#include <cos/gen/object.h>

#include <stdlib.h>

#ifndef COS_FUNCTOR_STACKSIZE
#define COS_FUNCTOR_STACKSIZE 8192  // 64k per thread on 64 bits arch
#endif

#if COS_HAVE_TLS || !COS_HAVE_POSIX // -----------------------------

__thread struct cos_functor_context cos_functor_context_ = { 0, 0, 0 };

#else // COS_HAVE_POSIX && !COS_HAVE_TLS ---------------------------

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

  if (!(cxt = malloc(sizeof *context)))
	  cos_abort("out of memory while creating functor context");

  cxt->stk = 0;
  cxt->top = 0;
  cxt->end = 0;

  if ( pthread_setspecific(cos_functor_context_key, cxt) )
	  cos_abort("unable to initialize functor context");

  return cxt;
}
  
#endif // ------------------------------------------------

useclass(ExBadAlloc, ExOverflow);

void
cos_functor_enlargeContext(void)
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
cos_functor_clearContext(void)
{
  struct cos_functor_context *cxt = cos_functor_context();

  free(cxt->stk), cxt->stk = 0;
}

