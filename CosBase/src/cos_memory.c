/*
 o---------------------------------------------------------------------o
 |
 | COS debug feature
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
 | $Id: cos_memory.c,v 1.1 2009/09/05 17:49:32 ldeniau Exp $
 |
*/

#undef  COS_MEM_TRACE
#define COS_MEM_TRACE

#include <cos/Object.h>

#include <stdio.h>

#if COS_HAVE_POSIX

#include <unistd.h>
#define INFO ((unsigned)getpid()), file, line, func
#define PRFX "COS-Alloc[%u]:(%s,%d,%s):"

#else

#define INFO file, line, func
#define PRFX "COS-Alloc:(%s,%d,%s):"

#endif

static BOOL cos_mem_trace_on = NO; // not thread safe
static U32  cos_mem_alloc_n  = 0;  // not thread safe
static U32  cos_mem_free_n   = 0;  // not thread safe

BOOL
cos_mem_trace(BOOL on)
{
  BOOL old = cos_mem_trace_on;
  
  cos_mem_trace_on = on;
  
  return old;
}

U32
cos_mem_nalloc(void)
{
  return cos_mem_alloc_n;
}

U32
cos_mem_nfree(void)
{
  return cos_mem_free_n;
}

void*
cos_mem_malloc(size_t size, STR func, STR file, int line)
{
  void *ptr = (malloc)(size);

  if (cos_mem_trace_on)
  fprintf(stderr, PRFX "malloc'ed pointer %p\n", INFO, ptr ? ptr : "(nil)");

  ++cos_mem_alloc_n;

  return ptr;
}

void*
cos_mem_calloc(size_t nelem, size_t size, STR func, STR file, int line)
{
  void *ptr = (calloc)(nelem, size);
  
  if (cos_mem_trace_on)
  fprintf(stderr, PRFX "calloc'ed pointer %p\n", INFO, ptr ? ptr : "(nil)");

  ++cos_mem_alloc_n;

  return ptr;
}

void*
cos_mem_realloc(void *p, size_t size, STR func, STR file, int line)
{
  void *ptr = (realloc)(p, size);
  
  if (cos_mem_trace_on)
  fprintf(stderr, PRFX "realloc'ed pointer %p (was %p)\n", INFO,
          ptr ? ptr : "(nil)", p ? p : "(nil)");

  cos_mem_alloc_n += !p;

  return ptr;
}

void
cos_mem_free(void *ptr, STR func, STR file, int line)
{
  if (cos_mem_trace_on)
  fprintf(stderr, PRFX "free'ed pointer %p\n", INFO, ptr ? ptr : "(nil)");

  ++cos_mem_free_n;

  (free)(ptr);
}

