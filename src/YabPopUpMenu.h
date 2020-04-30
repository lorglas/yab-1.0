#ifndef YABPOPUPMENU_H
#define YABPOPUPMENU_H

#include <PopUpMenu.h>

class YabPopUpMenu : public BPopUpMenu
{
	public:
		YabPopUpMenu(const char *title,bool radioMode = true,bool autoRename = true,menu_layout layout = B_ITEMS_IN_COLUMN);
		virtual void MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
		virtual void MouseUp(BPoint pt);
		virtual void MouseDown(BPoint pt);
		int mouseMovedInfo;
		int mouseStateInfo;
		int mouseX;
		int mouseY;
		uint mouseLButton;
		uint mouseMButton;
		uint mouseRButton;
	private:
		int prevMouseStateInfo;
};

#endif
