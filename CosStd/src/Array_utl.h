#ifndef COS_ARRAY_UTL_H
#define COS_ARRAY_UTL_H

/**
 * C Object System
 * COS Array - low-level utilities
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

static cos_inline void
assign(OBJ *dst, OBJ val)
{
  OBJ tmp = *dst;
  *dst = gretain(val);
  grelease(tmp);
}

static cos_inline OBJ*
arr_swap(OBJ *dst, I32 dst_s, OBJ *src, I32 src_s, U32 src_n)
{
  OBJ tmp1; PRT(tmp1);
  OBJ tmp2; PRT(tmp2);
  OBJ *end = src + src_s*src_n;

  while (src != end) {
    tmp1 = tmp2 = 0;
    tmp1 = gretain(*src);
    tmp2 = gretain(*dst);
    grelease(*src), *src = tmp2;
    grelease(*dst), *dst = tmp1;
    src += src_s;
    dst += dst_s;
  }

  UNPRT(tmp1);
  return dst;
}

static cos_inline OBJ*
arr_assign(OBJ *dst, I32 dst_s, OBJ *src, I32 src_s, U32 src_n)
{
  OBJ *end = src + src_s*src_n;

  while (src != end) {
    assign(dst, *src);
    dst += dst_s;
    src += src_s;
  }

  return dst;
}

static cos_inline OBJ*
arr_copy(OBJ *dst, I32 dst_s, U32 *dst_n, OBJ *src, I32 src_s, U32 src_n)
{
  OBJ *end = src + src_s*src_n;

  while (src != end) {
    *dst = gretain(*src), ++*dst_n;
     dst += dst_s;
     src += src_s;
  }

  return dst;
}

static cos_inline OBJ*
arr_clone(OBJ *dst, I32 dst_s, U32 *dst_n, OBJ *src, I32 src_s, U32 src_n)
{
  OBJ *end = src + src_s*src_n;

  while (src != end) {
    *dst = gclone(*src), ++*dst_n;
     dst += dst_s;
     src += src_s;
  }

  return dst;
}

#endif // COS_ARRAY_UTL_H
