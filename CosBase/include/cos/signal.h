#ifndef COS_SIGNAL_H
#define COS_SIGNAL_H

/**
 * C Object System
 * COS Signal Handler
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
