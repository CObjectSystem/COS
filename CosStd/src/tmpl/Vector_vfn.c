/*
 o---------------------------------------------------------------------o
 |
 | COS Vector template - algorithms using value functions
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
 | $Id: Vector_vfn.c,v 1.1 2009/08/29 21:38:46 ldeniau Exp $
 |
*/

#ifndef VECTOR_TMPL
#error "this template file requires tmpl/Vector.c"
#endif

// ----- foreach (in place, discard fun returned value)

defmethod(void, gforeach, T, TF1)
  VAL *val   = self->valref;
  I32  val_s = self->stride;
  VAL *end   = self->valref + self->size*self->stride;
  PF1  fct   = self2->fct;

  while (val != end) {
    fct(*val);
    val += val_s;
  }
endmethod

// ---

static inline void
foreach(VAL *val, PF1 fct, int n) {
  for (int i = 0; i < n; i++)
    fct(val[i]);
}

defmethod(void, gforeach, COS_PP_CAT(T,0), TF1)
  foreach(self->T.valref, self2->fct, 0);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,1), TF1)
  foreach(self->T.valref, self2->fct, 1);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,2), TF1)
  foreach(self->T.valref, self2->fct, 2);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,3), TF1)
  foreach(self->T.valref, self2->fct, 3);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,4), TF1)
  foreach(self->T.valref, self2->fct, 4);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,5), TF1)
  foreach(self->T.valref, self2->fct, 5);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,6), TF1)
  foreach(self->T.valref, self2->fct, 6);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,7), TF1)
  foreach(self->T.valref, self2->fct, 7);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,8), TF1)
  foreach(self->T.valref, self2->fct, 8);
endmethod

defmethod(void, gforeach, COS_PP_CAT(T,9), TF1)
  foreach(self->T.valref, self2->fct, 9);
endmethod

// ----- apply (in place map)

defmethod(void, gapply, TF1, T)
  VAL *val   = self2->valref;
  I32  val_s = self2->stride;
  VAL *end   = self2->valref + self2->size*self2->stride;
  PF1  fct   = self->fct;

  while (val != end) {
    *val = fct(*val);
    val += val_s;
  }
endmethod

// ---

static inline void
apply(VAL *val, PF1 fct, int n) {
  for (int i = 0; i < n; i++)
    val[i] = fct(val[i]);
}

defmethod(void, gapply, COS_PP_CAT(T,0), TF1)
  apply(self->T.valref, self2->fct, 0);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,1), TF1)
  apply(self->T.valref, self2->fct, 1);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,2), TF1)
  apply(self->T.valref, self2->fct, 2);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,3), TF1)
  apply(self->T.valref, self2->fct, 3);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,4), TF1)
  apply(self->T.valref, self2->fct, 4);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,5), TF1)
  apply(self->T.valref, self2->fct, 5);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,6), TF1)
  apply(self->T.valref, self2->fct, 6);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,7), TF1)
  apply(self->T.valref, self2->fct, 7);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,8), TF1)
  apply(self->T.valref, self2->fct, 8);
endmethod

defmethod(void, gapply, COS_PP_CAT(T,9), TF1)
  apply(self->T.valref, self2->fct, 9);
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, TF1, T)
  struct T* vec = T_alloc(self2->size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst   = vec->valref;
  VAL *end   = vec->valref + vec->size;
  VAL *src   = self2->valref;
  I32  src_s = self2->stride;
  PF1  fct   = self->fct;

  while (dst != end) {
    *dst++ = fct(*src);
    src += src_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ---

static inline OBJ
map(VAL *src, PF1 fct, int n) {
  struct T* vec = T_alloc(n);
  OBJ _vec = (OBJ)vec; PRT(_vec);
  
  VAL *dst = vec->valref;
  
  for (int i = 0; i < n; i++)
    dst[i] = fct(src[i]);

  UNPRT(_vec);
  return(gautoDelete(_vec));
}

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,0))
  retmethod( map(self2->T.valref, self->fct, 0) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,1))
  retmethod( map(self2->T.valref, self->fct, 1) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,2))
  retmethod( map(self2->T.valref, self->fct, 2) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,3))
  retmethod( map(self2->T.valref, self->fct, 3) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,4))
  retmethod( map(self2->T.valref, self->fct, 4) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,5))
  retmethod( map(self2->T.valref, self->fct, 5) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,6))
  retmethod( map(self2->T.valref, self->fct, 6) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,7))
  retmethod( map(self2->T.valref, self->fct, 7) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,8))
  retmethod( map(self2->T.valref, self->fct, 8) );
endmethod

defmethod(OBJ, gmap, TF1, COS_PP_CAT(T,9))
  retmethod( map(self2->T.valref, self->fct, 9) );
endmethod

// --

defmethod(OBJ, gmap2, TF2, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;

  struct T* vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self2->valref;
  I32  src1_s = self2->stride;
  VAL *src2   = self3->valref;
  I32  src2_s = self3->stride;
  PF2  fct    = self->fct;

  while (dst != end) {
    *dst++ = fct(*src1,*src2);
    src1 += src1_s;
    src2 += src2_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap3, TF3, T, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;

  struct T* vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self2->valref;
  I32  src1_s = self2->stride;
  VAL *src2   = self3->valref;
  I32  src2_s = self3->stride;
  VAL *src3   = self4->valref;
  I32  src3_s = self4->stride;
  PF3  fct    = self->fct;

  while (dst != end) {
    *dst++ = fct(*src1,*src2,*src3);
    src1 += src1_s;
    src2 += src2_s;
    src3 += src3_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, gmap4, TF4, T, T, T, T)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;

  struct T* vec = T_alloc(size);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst    = vec->valref;
  VAL *end    = vec->valref + vec->size;
  VAL *src1   = self2->valref;
  I32  src1_s = self2->stride;
  VAL *src2   = self3->valref;
  I32  src2_s = self3->stride;
  VAL *src3   = self4->valref;
  I32  src3_s = self4->stride;
  VAL *src4   = self5->valref;
  I32  src4_s = self5->stride;
  PF4  fct    = self->fct;

  while (dst != end) {
    *dst++ = fct(*src1,*src2,*src3,*src4);
    src1 += src1_s;
    src2 += src2_s;
    src3 += src3_s;
    src4 += src4_s;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

// ----- filter, fold, scan

defmethod(OBJ, greduce, T, TF2, TE)
  VAL *src   = self->valref;
  I32  src_s = self->stride;
  VAL *end   = self->valref + self->size*self->stride;
  PF2  fct   = self2->fct;
  VAL  res   = VALUE(self3);
  
  while (src != end) {
    res = fct(res, *src);
    src += src_s;
  }

  VALUE(self3) = res;
  retmethod(_3);
endmethod

defmethod(OBJ, grreduce, T, TF2, TE)
  VAL *src   = self->valref + self->size*self->stride;
  I32  src_s = self->stride;
  VAL *end   = self->valref;
  PF2  fct   = self2->fct;
  VAL  res   = VALUE(self3);

  while (src != end) {
    src -= src_s;
    res = fct(res, *src);
  }

  VALUE(self3) = res;
  retmethod(_3);
endmethod

defmethod(OBJ, gaccumulate, T, TF2, TE)
  struct T* vec = T_alloc(self->size+1);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst   = vec->valref;
  VAL *end   = vec->valref + vec->size;
  VAL *src   = self->valref;
  I32  src_s = self->stride;
  PF2  fct   = self2->fct;

  *dst++ = VALUE(self3);
  
  while (dst != end) {
    *dst = fct(dst[-1], *src);
    src += src_s, dst++;
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

defmethod(OBJ, graccumulate, T, TF2, TE)
  struct T* vec = T_alloc(self->size+1);
  OBJ _vec = (OBJ)vec; PRT(_vec);

  VAL *dst   = vec->valref + vec->size;
  VAL *end   = vec->valref;
  VAL *src   = self->valref + self->size*self->stride;
  I32  src_s = self->stride;
  PF2  fct   = self2->fct;

  *--dst = VALUE(self3);

  while (dst != end) {
    src -= src_s, dst--;
    *dst = fct(*src, dst[1]);
  }

  UNPRT(_vec);
  retmethod(gautoDelete(_vec));
endmethod

