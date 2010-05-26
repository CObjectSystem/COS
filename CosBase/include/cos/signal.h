#ifndef COS_SIGNAL_H
#define COS_SIGNAL_H

/*
 o---------------------------------------------------------------------o
 |
 | COS signal handler
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
 | $Id: signal.h,v 1.3 2010/05/26 22:46:29 ldeniau Exp $
 |
*/

#include <signal.h>

/* NOTE-USER: signal handler
   - register signal to convert into exception ExSignal when raised
   - return the previous signal handler
   - use gint(ex) from cos/gen/value.h to retrieve the signal value
*/
void (*cos_signal(int sig))(int);

/* NOTE-USER: standard signals handler
   - register the signals specified in the standard plus the signals which
     may interrupt the process.
   - equivalent to call cos_signal() on the following signals:
     SIGABRT, SIGALRM, SIGBUS, SIGFPE, SIGILL, SIGINT, SIGQUIT, SIGSEGV,
     SIGTERM.
   - previous handlers are discarded.
 */
void cos_signal_std(void);

#endif // COS_SIGNAL_H
