/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - exceptions
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
 | $Id: ut_exception.c,v 1.2 2008/10/02 08:44:43 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/signal.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>

#include <string.h>

#include "utest.h"
#include "tests.h"
#include "generics.h"

static const int sig[] = {
  SIGABRT, SIGALRM, 
#if SIGBUS
  SIGBUS,
#elif SIG_BUS 
  SIG_BUS,
#endif
  SIGFPE, SIGILL, SIGINT,
  SIGQUIT, SIGSEGV, SIGTERM
};
static const int n_sig = sizeof sig / sizeof sig[0];

static BOOL
check_str(OBJ a, STR res)
{
  return !strcmp(gstr(a),res);
}

void
ut_exception(void)
{
  useclass(ExSignal);
  useclass(A,B,C,D);
  volatile STR file = 0;
  volatile int line = 0;
  volatile int i;
  volatile OBJ c = NIL;
  OBJ a = NIL;
  OBJ b = NIL;

  UTEST_START("exception & signal")

  // -----

  for (i = 0; i < 2; i++)
    TRY
      PRT(a,b);
      a = gnew(A); b = gnew(B); c = gnew(C);

      if(i == 0) {
				gcatStr(c," is not thrown");
				UNPRT(a); // unprotect 'a' and 'b'
      } else {
			  gcatStr(c," is thrown");
        file = __FILE__, line = __LINE__, THROW(c);
      }

    CATCH(D)
      UTEST( !"CATCH(D) should not be reached" );

    CATCH(B)
      UTEST( !"CATCH(B) should not be reached" );

    CATCH(A, ex)
      UTEST( check_str(ex, "C is thrown") );
      UTEST( ex_file == file && ex_line == line );
      gvputStr(ex, "%s has been caught as an A", gclassName(ex));

    CATCH_ANY()
      UTEST( !"CATCH_ANY() should not be reached" );

    FINALLY
      if (i == 0) {
        UTEST( check_str(c, "C is not thrown") );
			  grelease(c);
		  } else {
        UTEST( check_str(c, "C has been caught as an A") );
			}
    ENDTRY

  // -----

  TRY
      TRY
        file = __FILE__, line = __LINE__, THROW(gnew(A));
      CATCH(A, ex)
        UTEST( gisInstanceOf(ex,A) == True );
				UTEST( ex_file == file && ex_line == line );
        RETHROW();
      FINALLY
      ENDTRY // rethrow is now effective
  CATCH(A, ex)
    // catch the rethrow
    UTEST( gisInstanceOf(ex,A) == True );
		UTEST( ex_file == file && ex_line == line );
  FINALLY
  ENDTRY

  // -----
  cos_signal_std();
  
  for (i = 0; i < n_sig; i++)
    TRY
      raise(sig[i]);
    CATCH(ExSignal, ex)
      UTEST( gint(ex) == sig[i] );
    ENDTRY
    
  UTEST_END
}
