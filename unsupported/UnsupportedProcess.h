/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_UnsupportedProcess
#define HEADER_UnsupportedProcess
/*
htop - UnsupportedProcess.h
(C) 2015 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/


typedef struct UnsupportedProcess_ {
   Process super;
   // add platform-specific fields here
} UnsupportedProcess;

#define Process_delete UnsupportedProcess_delete


void UnsupportedProcess_delete(Object* cast);


#endif
