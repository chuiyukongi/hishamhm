/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_Panel
#define HEADER_Panel
/*
htop - Panel.h
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

//#link curses

#include "Object.h"
#include "Vector.h"

typedef struct Panel_ Panel;

typedef enum HandlerResult_ {
   HANDLED     = 0x01,
   IGNORED     = 0x02,
   BREAK_LOOP  = 0x04,
   REDRAW      = 0x08,
   RESCAN      = 0x10,
   SYNTH_KEY   = 0x20,
} HandlerResult;

#define EVENT_SETSELECTED -1

typedef HandlerResult(*Panel_EventHandler)(Panel*, int);

typedef struct PanelClass_ {
   const ObjectClass super;
   const Panel_EventHandler eventHandler;
} PanelClass;

#define As_Panel(this_)                ((PanelClass*)((this_)->super.klass))
#define Panel_eventHandlerFn(this_)    As_Panel(this_)->eventHandler
#define Panel_eventHandler(this_, ev_) As_Panel(this_)->eventHandler((Panel*)(this_), ev_)

struct Panel_ {
   Object super;
   PanelClass* class;
   int x, y, w, h;
   WINDOW* window;
   Vector* items;
   int selected;
   int oldSelected;
   void* eventHandlerState;
   int scrollV;
   short scrollH;
   bool needsRedraw;
   RichString header;
};


#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#define KEY_CTRLN      0016            /* control-n key */
#define KEY_CTRLP      0020            /* control-p key */
#define KEY_CTRLF      0006            /* control-f key */
#define KEY_CTRLB      0002            /* control-b key */

extern PanelClass Panel_class;

Panel* Panel_new(int x, int y, int w, int h, bool owner, ObjectClass* type);

void Panel_delete(Object* cast);

void Panel_init(Panel* this, int x, int y, int w, int h, ObjectClass* type, bool owner);

void Panel_done(Panel* this);

RichString* Panel_getHeader(Panel* this);

extern void Panel_setHeader(Panel* this, const char* header);

void Panel_move(Panel* this, int x, int y);

void Panel_resize(Panel* this, int w, int h);

void Panel_prune(Panel* this);

void Panel_add(Panel* this, Object* o);

void Panel_insert(Panel* this, int i, Object* o);

void Panel_set(Panel* this, int i, Object* o);

Object* Panel_get(Panel* this, int i);

Object* Panel_remove(Panel* this, int i);

Object* Panel_getSelected(Panel* this);

void Panel_moveSelectedUp(Panel* this);

void Panel_moveSelectedDown(Panel* this);

int Panel_getSelectedIndex(Panel* this);

int Panel_size(Panel* this);

void Panel_setSelected(Panel* this, int selected);

void Panel_draw(Panel* this, bool focus);

bool Panel_onKey(Panel* this, int key);

HandlerResult Panel_selectByTyping(Panel* this, int ch);

#endif
