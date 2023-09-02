/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_ProcessList
#define HEADER_ProcessList
/*
htop - ProcessList.h
(C) 2004,2005 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "Vector.h"
#include "Hashtable.h"
#include "UsersTable.h"
#include "Panel.h"
#include "Process.h"
#include "Settings.h"

#ifndef MAX_NAME
#define MAX_NAME 128
#endif

#ifndef MAX_READ
#define MAX_READ 2048
#endif

typedef struct ProcessList_ {
   Settings* settings;

   Vector* processes;
   Vector* processes2;
   Hashtable* processTable;
   UsersTable* usersTable;

   Panel* panel;
   int following;
   uid_t userId;
   const char* incFilter;
   Hashtable* pidWhiteList;

   #ifdef HAVE_LIBHWLOC
   hwloc_topology_t topology;
   bool topologyOk;
   #endif

   unsigned long long int totalMem;
   unsigned long long int usedMem;
   unsigned long long int freeMem;
   unsigned long long int sharedMem;
   unsigned long long int buffersMem;
   unsigned long long int cachedMem;
   unsigned long long int totalSwap;
   unsigned long long int usedSwap;
   unsigned long long int freeSwap;

   int cpuCount;

} ProcessList;

ProcessList* ProcessList_new(UsersTable* ut, Hashtable* pidWhiteList, uid_t userId);
void ProcessList_delete(ProcessList* pl);
void ProcessList_scan(ProcessList* pl);


ProcessList* ProcessList_init(ProcessList* this, UsersTable* usersTable, Hashtable* pidWhiteList, uid_t userId);

void ProcessList_done(ProcessList* this);

void ProcessList_setPanel(ProcessList* this, Panel* panel);

void ProcessList_printHeader(ProcessList* this, RichString* header);

void ProcessList_add(ProcessList* this, Process* p);

void ProcessList_remove(ProcessList* this, Process* p);

Process* ProcessList_get(ProcessList* this, int idx);

int ProcessList_size(ProcessList* this);

void ProcessList_sort(ProcessList* this);

ProcessField ProcessList_keyAt(ProcessList* this, int at);

void ProcessList_expandTree(ProcessList* this);

void ProcessList_rebuildPanel(ProcessList* this);


#endif
