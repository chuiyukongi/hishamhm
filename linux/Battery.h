/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_Battery
#define HEADER_Battery
/*
htop - linux/Battery.h
(C) 2004-2014 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.

Linux battery readings written by Ian P. Hands (iphands@gmail.com, ihands@redhat.com).
*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define SYS_POWERSUPPLY_DIR "/sys/class/power_supply"

// ----------------------------------------
// READ FROM /proc
// ----------------------------------------

// This implementation reading from from /proc/acpi is really inefficient,
// but I think this is on the way out so I did not rewrite it.
// The /sys implementation below does things the right way.

// ----------------------------------------
// READ FROM /sys
// ----------------------------------------

void Battery_getData(double* level, ACPresence* isOnAC);

#endif
