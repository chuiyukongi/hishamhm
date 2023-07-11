/*
htop - CategoriesPanel.c
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "CategoriesPanel.h"

#include "AvailableMetersPanel.h"
#include "MetersPanel.h"
#include "DisplayOptionsPanel.h"
#include "ColumnsPanel.h"
#include "ColorsPanel.h"
#include "AvailableColumnsPanel.h"

#include <assert.h>
#include <stdlib.h>

/*{
#include "Panel.h"
#include "Settings.h"
#include "ScreenManager.h"
#include "ProcessList.h"

typedef struct CategoriesPanel_ {
   Panel super;
   ScreenManager* scr;

   Settings* settings;
   Header* header;
   ProcessList* pl;
} CategoriesPanel;

}*/

static const char* MetersFunctions[] = {"      ", "      ", "      ", "Type  ", "      ", "      ", "MoveUp", "MoveDn", "Remove", "Done  ", NULL};

static const char* AvailableMetersFunctions[] = {"      ", "      ", "      ", "      ", "Add L ", "Add R ", "      ", "      ", "      ", "Done  ", NULL};

static const char* DisplayOptionsFunctions[] = {"      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "Done  ", NULL};

static const char* ColumnsFunctions[] = {"      ", "      ", "      ", "      ", "      ", "      ", "MoveUp", "MoveDn", "Remove", "Done  ", NULL};

static const char* ColorsFunctions[] = {"      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ", "Done  ", NULL};

static const char* AvailableColumnsFunctions[] = {"      ", "      ", "      ", "      ", "Add   ", "      ", "      ", "      ", "      ", "Done  ", NULL};

static void CategoriesPanel_delete(Object* object) {
   Panel* super = (Panel*) object;
   CategoriesPanel* this = (CategoriesPanel*) object;
   Panel_done(super);
   free(this);
}

void CategoriesPanel_makeMetersPage(CategoriesPanel* this) {
   Panel* leftMeters = (Panel*) MetersPanel_new(this->settings, "Left column", this->header->columns[0], this->scr);
   Panel* rightMeters = (Panel*) MetersPanel_new(this->settings, "Right column", this->header->columns[1], this->scr);
   Panel* availableMeters = (Panel*) AvailableMetersPanel_new(this->settings, this->header, leftMeters, rightMeters, this->scr, this->pl);
   ScreenManager_add(this->scr, leftMeters, FunctionBar_new(MetersFunctions, NULL, NULL), 20);
   ScreenManager_add(this->scr, rightMeters, FunctionBar_new(MetersFunctions, NULL, NULL), 20);
   ScreenManager_add(this->scr, availableMeters, FunctionBar_new(AvailableMetersFunctions, NULL, NULL), -1);
}

static void CategoriesPanel_makeDisplayOptionsPage(CategoriesPanel* this) {
   Panel* displayOptions = (Panel*) DisplayOptionsPanel_new(this->settings, this->scr);
   ScreenManager_add(this->scr, displayOptions, FunctionBar_new(DisplayOptionsFunctions, NULL, NULL), -1);
}

static void CategoriesPanel_makeColorsPage(CategoriesPanel* this) {
   Panel* colors = (Panel*) ColorsPanel_new(this->settings, this->scr);
   ScreenManager_add(this->scr, colors, FunctionBar_new(ColorsFunctions, NULL, NULL), -1);
}

static void CategoriesPanel_makeColumnsPage(CategoriesPanel* this) {
   Panel* columns = (Panel*) ColumnsPanel_new(this->settings);
   Panel* availableColumns = (Panel*) AvailableColumnsPanel_new(columns);
   ScreenManager_add(this->scr, columns, FunctionBar_new(ColumnsFunctions, NULL, NULL), 20);
   ScreenManager_add(this->scr, availableColumns, FunctionBar_new(AvailableColumnsFunctions, NULL, NULL), -1);
}

static HandlerResult CategoriesPanel_eventHandler(Panel* super, int ch) {
   CategoriesPanel* this = (CategoriesPanel*) super;

   HandlerResult result = IGNORED;

   int selected = Panel_getSelectedIndex(super);
   switch (ch) {
      case EVENT_SETSELECTED:
         result = HANDLED;
         break;
      case KEY_UP:
      case KEY_CTRLP:
      case KEY_DOWN:
      case KEY_CTRLN:
      case KEY_NPAGE:
      case KEY_PPAGE:
      case KEY_HOME:
      case KEY_END: {
         int previous = selected;
         Panel_onKey(super, ch);
         selected = Panel_getSelectedIndex(super);
         if (previous != selected)
            result = HANDLED;
         break;
      }
      default:
         if (isalpha(ch))
            result = Panel_selectByTyping(super, ch);
         if (result == BREAK_LOOP)
            result = IGNORED;
         break;
   }

   if (result == HANDLED) {
      int size = ScreenManager_size(this->scr);
      for (int i = 1; i < size; i++)
         ScreenManager_remove(this->scr, 1);
      switch (selected) {
         case 0:
            CategoriesPanel_makeMetersPage(this);
            break;
         case 1:
            CategoriesPanel_makeDisplayOptionsPage(this);
            break;
         case 2:
            CategoriesPanel_makeColorsPage(this);
            break;
         case 3:
            CategoriesPanel_makeColumnsPage(this);
            break;
      }
   }

   return result;
}

PanelClass CategoriesPanel_class = {
   .super = {
      .extends = Class(Panel),
      .delete = CategoriesPanel_delete
   },
   .eventHandler = CategoriesPanel_eventHandler
};

CategoriesPanel* CategoriesPanel_new(ScreenManager* scr, Settings* settings, Header* header, ProcessList* pl) {
   CategoriesPanel* this = AllocThis(CategoriesPanel);
   Panel* super = (Panel*) this;
   Panel_init(super, 1, 1, 1, 1, Class(ListItem), true);

   this->scr = scr;
   this->settings = settings;
   this->header = header;
   this->pl = pl;
   Panel_setHeader(super, "Setup");
   Panel_add(super, (Object*) ListItem_new("Meters", 0));
   Panel_add(super, (Object*) ListItem_new("Display options", 0));
   Panel_add(super, (Object*) ListItem_new("Colors", 0));
   Panel_add(super, (Object*) ListItem_new("Columns", 0));
   return this;
}
