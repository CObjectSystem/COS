/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - next method
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
 | useful, but WITHOUTEST ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: ut_nextmethod.c,v 1.5 2009/02/03 14:40:48 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/utest.h>

#include "tests.h"
#include "generics.h"

#include <string.h>

static BOOL
check_nxt(char mode, OBJ cls1, OBJ cls2, STR res)
{
  OBJ _1 = gnew(cls1);
  OBJ _2 = gnew(cls2);
  STR s1 = gstr(_1);
  STR s2 = gstr(_2);
  BOOL ret;

  switch(mode) {
    case 'X': gdoX(_1,_2); break;
    case 'Y': gdoY(_1,_2); break;
    case 'Z': gdoZ(_1,_2); break;
    default: cos_abort("invalid choice");
  }
    
  ret = ! ( (strchr("ABCDE", s1[0]) && s1[1] != '-')
         || (strchr("ABCDE", s2[0]) && s2[1] != '-')
         ||  strcmp(s1+2, res)
         ||  strcmp(s2+2, res) );

  grelease(_1);
  grelease(_2);
  
  return ret;
}

void
ut_nextmethod(void)
{
  useclass(A,B,C,D,E);

  UTEST_START("next method & specialization")

    // Y mode (25 cases)

    // rnk 2
    UTEST( check_nxt('Y', A,A,"AA") );

    // rnk 3
    UTEST( check_nxt('Y', A,B,"AB-AA") );
    UTEST( check_nxt('Y', A,C,"[AC-AC-AA-AC]") );
    UTEST( check_nxt('Y', B,A,"[BA-[1BA-[2BA-BA-AA-BA2]-BA1]-BA]") );
    UTEST( check_nxt('Y', C,A,"CA-AA") );

    // rnk 4
    UTEST( check_nxt('Y', A,D,"AD-[AC-AC-AA-AC]") );
    UTEST( check_nxt('Y', B,B,"BB-[BA-[1BA-[2BA-BA-AA-BA2]-BA1]-BA]") );
    UTEST( check_nxt('Y', B,C,"[BC-BC-[BA-[1BA-[2BA-BA-AA-BA2]-BA1]-BA]-BC]") );
    UTEST( check_nxt('Y', C,B,"CB-CA-AA") );
    UTEST( check_nxt('Y', C,C,"CC-CA-AA") );
    UTEST( check_nxt('Y', D,A,"DA-CA-AA") );

    // rnk 5
    UTEST( check_nxt('Y', A,E,"AE-AD-[AC-AC-AA-AC]") );
    UTEST( check_nxt('Y', B,D,"BD-[BC-BC-[BA-[1BA-[2BA-BA-AA-BA2]-BA1]-BA]-BC]") );
    UTEST( check_nxt('Y', C,D,"CD-CC-CA-AA") );
    UTEST( check_nxt('Y', D,B,"DB-DA-CA-AA") );
    UTEST( check_nxt('Y', D,C,"DC-DA-CA-AA") );
    UTEST( check_nxt('Y', E,A,"EA-DA-CA-AA") );

    // rnk 6
    UTEST( check_nxt('Y', B,E,"BE-BD-[BC-BC-[BA-[1BA-[2BA-BA-AA-BA2]-BA1]-BA]-BC]") );
    UTEST( check_nxt('Y', C,E,"CE-CD-CC-CA-AA") );
    UTEST( check_nxt('Y', D,D,"DD-DC-DA-CA-AA") );
    UTEST( check_nxt('Y', E,B,"EB-EA-DA-CA-AA") );
    UTEST( check_nxt('Y', E,C,"EC-EA-DA-CA-AA") );

    // rnk 7
    UTEST( check_nxt('Y', D,E,"DE-DD-DC-DA-CA-AA") );
    UTEST( check_nxt('Y', E,D,"ED-EC-EA-DA-CA-AA") );

    // rnk 8
    UTEST( check_nxt('Y', E,E,"EE-ED-EC-EA-DA-CA-AA") );

    // Z mode (25 cases)

    // rnk 2
    UTEST( check_nxt('Z', A,A,"AAZ") );

    // rnk 3
    UTEST( check_nxt('Z', A,B,"AAZ") );
    UTEST( check_nxt('Z', A,C,"AAZ") );
    UTEST( check_nxt('Z', B,A,"AAZ") );
    UTEST( check_nxt('Z', C,A,"AAZ") );

    // rnk 4
    UTEST( check_nxt('Z', A,D,"AAZ") );
    UTEST( check_nxt('Z', B,B,"BBZ-AAZ") );
    UTEST( check_nxt('Z', B,C,"AAZ") );
    UTEST( check_nxt('Z', C,B,"AAZ") );
    UTEST( check_nxt('Z', C,C,"CCZ-AAZ") );
    UTEST( check_nxt('Z', D,A,"AAZ") );

    // rnk 5
    UTEST( check_nxt('Z', A,E,"AAZ") );
    UTEST( check_nxt('Z', B,D,"AAZ") );
    UTEST( check_nxt('Z', C,D,"CCZ-AAZ") );
    UTEST( check_nxt('Z', D,B,"AAZ") );
    UTEST( check_nxt('Z', D,C,"CCZ-AAZ") );
    UTEST( check_nxt('Z', E,A,"AAZ") );

    // rnk 6
    UTEST( check_nxt('Z', B,E,"AAZ") );
    UTEST( check_nxt('Z', C,E,"CCZ-AAZ") );
    UTEST( check_nxt('Z', D,D,"DDZ-DC-DA-CA-AA") );
    UTEST( check_nxt('Z', E,B,"AAZ") );
    UTEST( check_nxt('Z', E,C,"CCZ-AAZ") );

    // rnk 7
    UTEST( check_nxt('Z', D,E,"DDZ-DC-DA-CA-AA") );
    UTEST( check_nxt('Z', E,D,"DDZ-DC-DA-CA-AA") );

    // rnk 8
    UTEST( check_nxt('Z', E,E,"EEZ-DDZ-DC-DA-CA-AA") );

    // X mode (25 cases)

    // rnk 2
    UTEST( check_nxt('X', A,A,"AAX") );

    // rnk 3
    UTEST( check_nxt('X', A,B,"AAX") );
    UTEST( check_nxt('X', A,C,"AAX") );
    UTEST( check_nxt('X', B,A,"AAX") );
    UTEST( check_nxt('X', C,A,"AAX") );

    // rnk 4
    UTEST( check_nxt('X', A,D,"AAX") );
    UTEST( check_nxt('X', B,B,"BBZ-AAZ") );
    UTEST( check_nxt('X', B,C,"AAX") );
    UTEST( check_nxt('X', C,B,"AAX") );
    UTEST( check_nxt('X', C,C,"CCZ-AAZ") );
    UTEST( check_nxt('X', D,A,"AAX") );

    // rnk 5
    UTEST( check_nxt('X', A,E,"AAX") );
    UTEST( check_nxt('X', B,D,"AAX") );
    UTEST( check_nxt('X', C,D,"CCZ-AAZ") );
    UTEST( check_nxt('X', D,B,"AAX") );
    UTEST( check_nxt('X', D,C,"CCZ-AAZ") );
    UTEST( check_nxt('X', E,A,"AAX") );

    // rnk 6
    UTEST( check_nxt('X', B,E,"AAX") );
    UTEST( check_nxt('X', C,E,"CCZ-AAZ") );
    UTEST( check_nxt('X', D,D,"DDX-CCZ-AAZ") );
    UTEST( check_nxt('X', E,B,"AAX") );
    UTEST( check_nxt('X', E,C,"CCZ-AAZ") );

    // rnk 7
    UTEST( check_nxt('X', D,E,"DDX-CCZ-AAZ") );
    UTEST( check_nxt('X', E,D,"DDX-CCZ-AAZ") );

    // rnk 8
    UTEST( check_nxt('X', E,E,"EEZ-DDZ-DC-DA-CA-AA") );

  UTEST_END
}
