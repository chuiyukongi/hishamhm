/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_Platform
#define HEADER_Platform
/*
htop - unsupported/Platform.h
(C) 2014 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "Action.h"

void Platform_setBindings(Htop_Action* keys);

extern MeterClass* Platform_meterTypes[];

int Platform_getUptime();

#endif
