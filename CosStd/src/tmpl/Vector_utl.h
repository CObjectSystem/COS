#ifndef COS_VECTOR_UTL_H
#define COS_VECTOR_UTL_H

/**
 * C Object System
 * COS Vector - utilities
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

static inline void
swap(VAL *val1, VAL *val2)
{
  VAL tmp = *val1;
  *val1 = *val2;
  *val2 = tmp;
}

static inline VAL*
copy(VAL *dst, U32 *dst_n, VAL *src, I32 src_s, U32 src_n)
{
  VAL *end = dst + src_n;

  while (dst != end)
    *dst++ = *src, ++*dst_n, src += src_s;

  return dst;
}

#endif // COS_VECTOR_UTL_H
