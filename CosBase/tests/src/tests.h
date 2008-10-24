#ifndef COS_TESTS_TESTS_H
#define COS_TESTS_TESTS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - tests suite
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
 | $Id: tests.h,v 1.6 2008/10/24 21:08:39 ldeniau Exp $
 |
*/

void ut_methods(void);
void ut_classes(void);
//void ut_predlogic(void);
void ut_nextmethod(void);
void ut_unrecognized(void);
void ut_forwardmessage(void);
void ut_variadics(void);
void ut_proxy(void);
void ut_exception(void);
void ut_contract(void);
void ut_autorelease(void);
//void ut_autoconst(void);
//void ut_autovector(void);

void st_methods(void);
void st_methods_ptr(void);
void st_nextmethods(void);
void st_multimethods(void);
void st_multimethods_ptr(void);

void st_pxymethods(void);
void st_pxynextmethods(void);
void st_pxymultimethods(void);

void st_memory(void);
void st_exception(void);

#endif // COS_TESTS_TESTS_H
