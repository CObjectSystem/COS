/*
 o---------------------------------------------------------------------o
 |
 | COS dispatch caches
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
 | $Id: cos_dispatch.c,v 1.3 2008/10/31 15:19:44 ldeniau Exp $
 |
*/

#include <cos/Object.h>

void cos_method_clearCaches(void)
{
  cos_method_clearCache1();
  cos_method_clearCache2();
  cos_method_clearCache3();
  cos_method_clearCache4();
  cos_method_clearCache5();
}

/*
 * ----------------------------------------------------------------------------
 *  Debug Functions
 * ----------------------------------------------------------------------------
 */

#include <cos/debug.h>

void
cos_method_showCache1(FILE *fp)
{
  struct cos_method_cache1 *cache = cos_method_cache1();
  U32 i, n=0, d=0;

  if (!fp) fp = stderr;

  for (i=0; i <= cache->msk; i++) {
    struct cos_method_slot1 *slot = cache->slot[i];

    if (slot->idg) {
      U32 j=0;

      fprintf(fp, "[%3u]", i);

      do {
        ++j;
        fprintf(fp, " %s(%s)",
                cos_generic_get(slot->idg)->name,
                cos_class_get  (slot->id1)->name);
        slot = slot->nxt;
      } while (slot->idg);

      fputc('\n', fp);

      n += j;
      if (j > d) d = j;
    }
  }

  fprintf(fp,"Slots=%u, Cells=%u, MaxDepth=%d, Load=%.2f\n",i,n,d,(double)n/i);
}

void
cos_method_showCache2(FILE *fp)
{
  struct cos_method_cache2 *cache = cos_method_cache2();
  U32 i, n=0, d=0;

  if (!fp) fp = stderr;

  for (i=0; i <= cache->msk; i++) {
    struct cos_method_slot2 *slot = cache->slot[i];

    if (slot->idg) {
      U32 j=0;

      fprintf(fp, "[%3u]", i);

      do {
        ++j;
        fprintf(fp, " %s(%s,%s)",
                cos_generic_get(slot->idg)->name,
                cos_class_get  (slot->id1)->name,
                cos_class_get  (slot->id2)->name);
        slot = slot->nxt;
      } while (slot->idg);

      fputc('\n', fp);

      n += j;
      if (j > d) d = j;
    }
  }

  fprintf(fp,"Slots=%u, Cells=%u, MaxDepth=%d, Load=%.2f\n",i,n,d,(double)n/i);
}

void
cos_method_showCache3(FILE *fp)
{
  struct cos_method_cache3 *cache = cos_method_cache3();
  U32 i, n=0, d=0;

  if (!fp) fp = stderr;

  for (i=0; i <= cache->msk; i++) {
    struct cos_method_slot3 *slot = cache->slot[i];

    if (slot->idg) {
      U32 j=0;

      fprintf(fp, "[%3u]", i);

      do {
        ++j;
        fprintf(fp, " %s(%s,%s,%s)",
                cos_generic_get(slot->idg)->name,
                cos_class_get  (slot->id1)->name,
                cos_class_get  (slot->id2)->name,
                cos_class_get  (slot->id3)->name);
        slot = slot->nxt;
      } while (slot->idg);

      fputc('\n', fp);

      n += j;
      if (j > d) d = j;
    }
  }

  fprintf(fp,"Slots=%u, Cells=%u, MaxDepth=%d, Load=%.2f\n",i,n,d,(double)n/i);
}

void
cos_method_showCache4(FILE *fp)
{
  struct cos_method_cache4 *cache = cos_method_cache4();
  U32 i, n=0, d=0;

  if (!fp) fp = stderr;

  for (i=0; i <= cache->msk; i++) {
    struct cos_method_slot4 *slot = cache->slot[i];

    if (slot->idg) {
      U32 j=0;

      fprintf(fp, "[%3u]", i);

      do {
        ++j;
        fprintf(fp, " %s(%s,%s,%s,%s)",
                cos_generic_get(slot->idg)->name,
                cos_class_get  (slot->id1)->name,
                cos_class_get  (slot->id2)->name,
                cos_class_get  (slot->id3)->name,
                cos_class_get  (slot->id4)->name);
        slot = slot->nxt;
      } while (slot->idg);

      fputc('\n', fp);

      n += j;
      if (j > d) d = j;
    }
  }

  fprintf(fp,"Slots=%u, Cells=%u, MaxDepth=%d, Load=%.2f\n",i,n,d,(double)n/i);
}

void
cos_method_showCache5(FILE *fp)
{
  struct cos_method_cache5 *cache = cos_method_cache5();
  U32 i, n=0, d=0;

  if (!fp) fp = stderr;

  for (i=0; i <= cache->msk; i++) {
    struct cos_method_slot5 *slot = cache->slot[i];

    if (slot->idg) {
      U32 j=0;

      fprintf(fp, "[%3u]", i);

      do {
        ++j;
        fprintf(fp, " %s(%s,%s,%s,%s,%s)",
                cos_generic_get(slot->idg)->name,
                cos_class_get  (slot->id1)->name,
                cos_class_get  (slot->id2)->name,
                cos_class_get  (slot->id3)->name,
                cos_class_get  (slot->id4)->name,
                cos_class_get  (slot->id5)->name);
        slot = slot->nxt;
      } while (slot->idg);

      fputc('\n', fp);

      n += j;
      if (j > d) d = j;
    }
  }

  fprintf(fp,"Slots=%u, Cells=%u, MaxDepth=%d, Load=%.2f\n",i,n,d,(double)n/i);
}
